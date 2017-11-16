ifeq ($(CONFIG_SOC_EXYNOS8890_EVT1), y)
obj-$(CONFIG_ION_EXYNOS) += exynos_ion.o
else ifeq ($(CONFIG_SOC_EXYNOS7870), y)
obj-$(CONFIG_ION_EXYNOS) += exynos_ion.o
else
obj-$(CONFIG_ION_EXYNOS) += exynos_ion_v2.o
endif
