COLOR_RED := $(shell echo "\033[1;31m")
COLOR_END := $(shell echo "\033[0m")

ifeq ($(wildcard .config),)
$(warning $(COLOR_RED)Warning: .config does not exist!$(COLOR_END))
$(warning $(COLOR_RED)To build the project, first run 'make menuconfig'.$(COLOR_END))
endif

Q            := @
# 复用 npc/ 里已经建好的 kconfig 工具链(conf / mconf), 不重复拷贝
NPC_HOME     ?= ..
NPC_SOC_HOME ?= .

KCONFIG_PATH := $(NPC_HOME)/tools/kconfig
Kconfig      := $(NPC_SOC_HOME)/Kconfig
rm-distclean += include/generated include/config .config .config.old
silent := -s

CONF  := $(KCONFIG_PATH)/build/conf
MCONF := $(KCONFIG_PATH)/build/mconf

$(CONF):
	$(Q)$(MAKE) $(silent) -C $(KCONFIG_PATH) NAME=conf

$(MCONF):
	$(Q)$(MAKE) $(silent) -C $(KCONFIG_PATH) NAME=mconf

menuconfig: $(MCONF) $(CONF)
	$(Q)$(MCONF) $(Kconfig)
	$(Q)$(CONF) $(silent) --syncconfig $(Kconfig)

savedefconfig: $(CONF)
	$(Q)$< $(silent) --$@=configs/defconfig $(Kconfig)

.PHONY: menuconfig savedefconfig

distclean: clean
	-@rm -rf $(rm-distclean)

.PHONY: distclean
