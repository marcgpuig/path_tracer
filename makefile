BUILD_FOLDER=$(CURDIR)/build
BIN_FOLDER=$(CURDIR)/bin
INSTALL_FOLDER=$(CURDIR)/install
LIB_FOLDER=$(CURDIR)/lib
CMAKE_FOLDER=$(CURDIR)
PROGRAM_NAME=ray_trace.exe

BUILD_TYPE=Visual Studio 15 2017 Win64

ifeq ($(OS),Windows_NT)
BUILD_RULE=build_windows
CLEAN_RULE=clean_windows
DEFAULT_RULE=nmake
else
BUILD_RULE=build_linux
CLEAN_RULE=clean_linux
endif

default: help

help:
	@echo Options:
	@echo  - run:   Run the program
	@echo  - nmake: Compiles the program using nmake
	@echo  - clean: Clean the project builds and bins

run: nmake
	@echo OFF & echo.
	@echo Compilation successful!
	@echo Running "$(BIN_FOLDER)/$(PROGRAM_NAME)"...
	@"$(BIN_FOLDER)/$(PROGRAM_NAME)"
	@echo Program terminated.

nmake: BUILD_FOLDER:=$(BUILD_FOLDER)/nmake
nmake: CMAKE_FLAGS+=-G"NMake Makefiles"
nmake: CMAKE_FLAGS+=-B"$(BUILD_FOLDER)"
nmake: call_cmake
	@cd "$(BUILD_FOLDER)" & nmake

call_cmake:
	@if not exist "$(BUILD_FOLDER)" mkdir "$(BUILD_FOLDER)"
	@cd "$(BUILD_FOLDER)" & cmake $(CMAKE_FLAGS) "$(CMAKE_FOLDER)"

### Clean #########################################################

clean: $(CLEAN_RULE)

clean_linux:
	@rm -Rf $(INSTALL_FOLDER)
	@rm -Rf $(BUILD_FOLDER)
	@rm -Rf $(BUILD_FOLDER)

clean_windows:
	@echo deleting "$(INSTALL_FOLDER)"...
	@if exist "$(INSTALL_FOLDER)" (rmdir /s/q "$(INSTALL_FOLDER)")
	@echo deleting "$(BUILD_FOLDER)"...
	@if exist "$(BUILD_FOLDER)" (rmdir /s/q "$(BUILD_FOLDER)")
	@echo deleting "$(BIN_FOLDER)"...
	@if exist "$(BIN_FOLDER)" (rmdir /s/q "$(BIN_FOLDER)")
