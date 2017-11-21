/*
 * aes-ce-cipher.c - core AES cipher using ARMv8 Crypto Extensions
 *
 * Copyright (C) 2013 - 2014 Linaro Ltd <ard.biesheuvel@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <asm/neon.h>
#include <crypto/aes.h>
#include <linux/cpufeature.h>
#include <linux/crypto.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Synchronous AES cipher using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

struct aes_block {
	u8 b[AES_BLOCK_SIZE];
};

asmlinkage void __aes_ce_encrypt(u32 *rk, u8 *out, const u8 *in, int rounds);
asmlinkage void __aes_ce_decrypt(u32 *rk, u8 *out, const u8 *in, int rounds);

asmlinkage u32 __aes_ce_sub(u32 l);
asmlinkage void __aes_ce_invert(struct aes_block *out,
				const struct aes_block *in);

static int num_rounds(struct crypto_aes_ctx *ctx)
{
	/*
	 * # of rounds specified by AES:
	 * 128 bit key		10 rounds
	 * 192 bit key		12 rounds
	 * 256 bit key		14 rounds
	 * => n byte key	=> 6 + (n/4) rounds
	 */
	return 6 + ctx->key_length / 4;
}

static void aes_cipher_encrypt(struct crypto_tfm *tfm, u8 dst[], u8 const src[])
{
	struct crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	kernel_neon_begin();

	__aes_ce_encrypt(ctx->key_enc, dst, src, num_rounds(ctx));

	kernel_neon_end();
}

static void aes_cipher_decrypt(struct crypto_tfm *tfm, u8 dst[], u8 const src[])
{
	struct crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	kernel_neon_begin();

	__aes_ce_decrypt(ctx->key_dec, dst, src, num_rounds(ctx));

	kernel_neon_end();
}

static struct crypto_alg aes_alg = {
	.cra_name		= "aes",
	.cra_driver_name	= "aes-ce",
	.cra_priority		= 250,
	.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		= AES_BLOCK_SIZE,
	.cra_ctxsize		= sizeof(struct crypto_aes_ctx),
	.cra_module		= THIS_MODULE,
	.cra_cipher = {
		.cia_min_keysize	= AES_MIN_KEY_SIZE,
		.cia_max_keysize	= AES_MAX_KEY_SIZE,
		.cia_setkey		= crypto_aes_set_key,
		.cia_encrypt		= aes_cipher_encrypt,
		.cia_decrypt		= aes_cipher_decrypt
	}
};

static int __init aes_mod_init(void)
{
	return crypto_register_alg(&aes_alg);
}

static void __exit aes_mod_exit(void)
{
	crypto_unregister_alg(&aes_alg);
}

module_cpu_feature_match(AES, aes_mod_init);
module_exit(aes_mod_exit);
