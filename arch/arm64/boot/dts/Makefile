dtb-y += exynos7870-gtaxllte_eur_open_00.dtb
dtb-y += exynos7870-gtaxllte_eur_open_01.dtb
dtb-y += exynos7870-gtaxllte_eur_open_04.dtb
dtb-y += exynos7870-gtaxllte_eur_open_05.dtb
dtb-y += exynos7870-gtaxlwifi_eur_open_00.dtb
dtb-y += exynos7870-gtaxlwifi_eur_open_04.dtb
dtb-y += exynos7870-gtaxlwifi_eur_open_05.dtb

targets += dtbs
DTB_LIST  := $(dtb-y) $(dtbo-y)

dtbs: $(addprefix $(obj)/, $(DTB_LIST))

clean-files := *.dtb*
