CC=g++
CFLAGS=-Wall -Wextra -Wno-unused-parameter -O2 -m32
LDFLAGS=-static-libgcc -static-libstdc++ -m32

PE_NAME=advanced-memory
DLL_NAME=advanced-library
DEBUG_NAME_SUFFIX=_debug

# --- DIRECTORIES

BUILD_DIR=build
RELEASE_DIR=$(BUILD_DIR)/release
DEBUG_DIR=$(BUILD_DIR)/debug
RELEASE_DLL_DIR=$(BUILD_DIR)/release_dll
DEBUG_DLL_DIR=$(BUILD_DIR)/debug_dll
RELEASE_SHARED_OBJ_DIR=$(BUILD_DIR)/release_shared_obj
DEBUG_SHARED_OBJ_DIR=$(BUILD_DIR)/debug_shared_obj

# --- SOURCE FILES

SHARED=$(wildcard src/shared/*.cpp)
SOURCES=$(wildcard src/loader/*.cpp)
DLL_SOURCES=$(wildcard src/dll/*.cpp)

# --- OBJECT FILES

RELEASE_SHARED_OBJ=$(SHARED:%.cpp=$(RELEASE_SHARED_OBJ_DIR)/%.o)
DEBUG_SHARED_OBJ=$(SHARED:%.cpp=$(DEBUG_SHARED_OBJ_DIR)/%.o)
RELEASE_OBJ=$(SOURCES:%.cpp=$(RELEASE_DIR)/obj/%.o)
DEBUG_OBJ=$(SOURCES:%.cpp=$(DEBUG_DIR)/obj/%.o)
DLL_RELEASE_OBJ=$(DLL_SOURCES:%.cpp=$(RELEASE_DLL_DIR)/obj/%.o)
DLL_DEBUG_OBJ=$(DLL_SOURCES:%.cpp=$(DEBUG_DLL_DIR)/obj/%.o)

# --- HEADER FILES

# todo

# -----------------------------

# --- COMMON part

.PHONY: all release debug release_dll debug_dll clean

all: release debug release_dll debug_dll

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR) $(RELEASE_DLL_DIR) $(DEBUG_DLL_DIR) $(RELEASE_SHARED_OBJ_DIR) $(DEBUG_SHARED_OBJ_DIR)

# --- SHARED part

$(RELEASE_SHARED_OBJ_DIR)/%.o: %.cpp
	@echo "[RELEASE][SHARED] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(DEBUG_SHARED_OBJ_DIR)/%.o: %.cpp
	@echo "[DEBUG][SHARED] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O0 -g -DDEBUG -c $< -o $@

# --- LOADER part

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

$(RELEASE_DIR)/$(PE_NAME): $(RELEASE_OBJ) $(RELEASE_SHARED_OBJ)
	@echo "[RELEASE][LOADER] Linking: $^ into $@"
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(LDFLAGS) -o $(RELEASE_DIR)/$(PE_NAME) $^

$(DEBUG_DIR)/$(PE_NAME)$(DEBUG_NAME_SUFFIX): $(DEBUG_OBJ) $(DEBUG_SHARED_OBJ)
	@echo "[DEBUG][LOADER] Linking: $^ into $@"
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(LDFLAGS) -g -o $(DEBUG_DIR)/$(PE_NAME)$(DEBUG_NAME_SUFFIX) $^

# --- DLL part

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

$(RELEASE_DLL_DIR)/$(DLL_NAME).dll: $(DLL_RELEASE_OBJ) $(RELEASE_SHARED_OBJ)
	@echo "[RELEASE][DLL] Linking: $^ into $@"
	@mkdir -p $(RELEASE_DLL_DIR)
	$(CC) $(LDFLAGS) -shared -o $(RELEASE_DLL_DIR)/$(DLL_NAME).dll $^

$(DEBUG_DLL_DIR)/$(DLL_NAME)$(DEBUG_NAME_SUFFIX).dll: $(DLL_DEBUG_OBJ) $(DEBUG_SHARED_OBJ)
	@echo "[DEBUG][DLL] Linking: $^ into $@"
	@mkdir -p $(DEBUG_DLL_DIR)
	$(CC) $(LDFLAGS) -shared -g -o $(DEBUG_DLL_DIR)/$(DLL_NAME)$(DEBUG_NAME_SUFFIX).dll $^
