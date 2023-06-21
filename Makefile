# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  Banana_config = debug
  Sandbox_config = debug

else ifeq ($(config),release)
  Banana_config = release
  Sandbox_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := Banana Sandbox

.PHONY: all clean help $(PROJECTS) engine game

all: $(PROJECTS)

engine: Banana

game: Sandbox

Banana:
ifneq (,$(Banana_config))
	@echo "==== Building Banana ($(Banana_config)) ===="
	@${MAKE} --no-print-directory -C Banana -f Makefile config=$(Banana_config)
endif

Sandbox: Banana
ifneq (,$(Sandbox_config))
	@echo "==== Building Sandbox ($(Sandbox_config)) ===="
	@${MAKE} --no-print-directory -C Sandbox -f Makefile config=$(Sandbox_config)
endif

clean:
	@${MAKE} --no-print-directory -C Banana -f Makefile clean
	@${MAKE} --no-print-directory -C Sandbox -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Banana"
	@echo "   Sandbox"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"