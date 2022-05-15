# SECTION: Imports.
-include config.mk

# SECTION: Variables.
GCC := gcc
PLUGINS_DIR := plugins
ENTRYPOINT_PLUGINS_FILE := $(PLUGINS_DIR)/plugins.cpp
BUILD_DIR := build
BUILD_PLUGINS_FILE := $(BUILD_DIR)/plugins.exe
HOUDINI_FLAGS := -I"$(HOUDINI_BASE_DIR)/toolkit/include" -L"$(HOUDINI_BASE_DIR)/custom/houdini/dsolib" -llibHAPIL -llibHARC

# SECTION: Misc.
.PHONY: help build
.DEFAULT_GOAL := help

# SECTION: Commands.
help: ## Show this help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z0-9_-]+:.*?## / {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

build: ## Build plugins project.
	$(GCC) $(ENTRYPOINT_PLUGINS_FILE) -Wall -Wextra -w $(HOUDINI_FLAGS) -o $(BUILD_PLUGINS_FILE)