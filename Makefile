# SECTION: Variables.
BASE_DIR :=$(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
BUILD_DIR := $(BASE_DIR)/build
CVEX_DUMP_FILE := $(BUILD_DIR)/cvex_dump.out

VCC := vcc
CMAKE := cmake

# SECTION: Misc.
.PHONY: help build dump_cvex
.DEFAULT_GOAL := help

# SECTION: Commands.
help: ## Show this help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z0-9_-]+:.*?## / {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

build: ## Build plugins project using CMake.
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CMAKE) -B$(BUILD_DIR) -S$(BASE_DIR)

dump_cvex: ## Dumps all VEX functions into file.
	$(VCC) -X cvex > $(CVEX_DUMP_FILE)