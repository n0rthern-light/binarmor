CFLAGS=-Wall -Wextra -Wno-unused-parameter -O2 -m32
LDFLAGS=-static-libgcc -static-libstdc++ -m32

CC=g++
PE_NAME=advanced-memory
DLL_NAME=advanced-library
DEBUG_NAME_SUFFIX=_debug

BUILD_DIR=build

RELEASE_DIR=$(BUILD_DIR)/release
DEBUG_DIR=$(BUILD_DIR)/debug
RELEASE_DLL_DIR=$(BUILD_DIR)/release_dll
DEBUG_DLL_DIR=$(BUILD_DIR)/debug_dll

SHARED=$(wildcard ./src/shared/*.cpp)
SOURCES=$(SHARED) $(wildcard src/loader/*.cpp)
DLL_SOURCES=$(SHARED) $(wildcard src/dll/*.cpp)

RELEASE_OBJ=$(SOURCES:%.cpp=$(RELEASE_DIR)/obj/%.o)
DEBUG_OBJ=$(SOURCES:%.cpp=$(DEBUG_DIR)/obj/%.o)
DLL_RELEASE_OBJ=$(DLL_SOURCES:%.cpp=$(RELEASE_DLL_DIR)/obj/%.o)
DLL_DEBUG_OBJ=$(DLL_SOURCES:%.cpp=$(DEBUG_DLL_DIR)/obj/%.o)

# --- COMMON part

.PHONY: all release debug release_dll debug_dll clean

all: release debug release_dll debug_dll

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR) $(RELEASE_DLL_DIR) $(DEBUG_DLL_DIR)

# --- LOADER part

# alias

release: $(RELEASE_DIR)/$(PE_NAME)

debug: $(DEBUG_DIR)/$(PE_NAME)$(DEBUG_NAME_SUFFIX)

# compiling

$(RELEASE_DIR)/obj/%.o: %.cpp
	@echo "[RELEASE][LOADER] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(DEBUG_DIR)/obj/%.o: %.cpp
	@echo "[DEBUG][LOADER] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O0 -g -DDEBUG -c $< -o $@

# linking

$(RELEASE_DIR)/$(PE_NAME): $(RELEASE_OBJ)
	@echo "[RELEASE][LOADER] Linking: $< into $@"
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(LDFLAGS) -o $(RELEASE_DIR)/$(PE_NAME) $(RELEASE_OBJ)

$(DEBUG_DIR)/$(PE_NAME)$(DEBUG_NAME_SUFFIX): $(DEBUG_OBJ)
	@echo "[DEBUG][LOADER] Linking: $< into $@"
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(LDFLAGS) -g -o $(DEBUG_DIR)/$(PE_NAME)$(DEBUG_NAME_SUFFIX) $(DEBUG_OBJ)

# --- DLL part

# alias

release_dll: $(RELEASE_DLL_DIR)/$(DLL_NAME).dll

debug_dll: $(DEBUG_DLL_DIR)/$(DLL_NAME)$(DEBUG_NAME_SUFFIX).dll

# compiling

$(RELEASE_DLL_DIR)/obj/%.o: %.cpp
	@echo "[RELEASE][DLL] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(DEBUG_DLL_DIR)/obj/%.o: %.cpp
	@echo "[DEBUG][DLL] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O0 -g -DDEBUG -c $< -o $@

# linking

$(RELEASE_DLL_DIR)/$(DLL_NAME).dll: $(DLL_RELEASE_OBJ)
	@echo "[RELEASE][DLL] Linking: $< into $@"
	@mkdir -p $(RELEASE_DLL_DIR)
	$(CC) $(LDFLAGS) -shared -o $(RELEASE_DLL_DIR)/$(DLL_NAME).dll $(DLL_RELEASE_OBJ)

$(DEBUG_DLL_DIR)/$(DLL_NAME)$(DEBUG_NAME_SUFFIX).dll: $(DLL_DEBUG_OBJ)
	@echo "[DEBUG][DLL] Linking: $< into $@"
	@mkdir -p $(DEBUG_DLL_DIR)
	$(CC) $(LDFLAGS) -shared -g -o $(DEBUG_DLL_DIR)/$(DLL_NAME)$(DEBUG_NAME_SUFFIX).dll $(DLL_DEBUG_OBJ)
