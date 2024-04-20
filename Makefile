CCx86=i686-w64-mingw32-g++
CCx64=x86_64-w64-mingw32-g++

CFLAGS=-Wall -Wextra -Wno-unused-parameter -fpermissive -O2
LDFLAGS=-static-libgcc -static-libstdc++ --static

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
X86_RELEASE_SHARED_OBJ_DIR=$(RELEASE_SHARED_OBJ_DIR)/x86
X86_DEBUG_SHARED_OBJ_DIR=$(DEBUG_SHARED_OBJ_DIR)/x86
X64_RELEASE_SHARED_OBJ_DIR=$(RELEASE_SHARED_OBJ_DIR)/x64
X64_DEBUG_SHARED_OBJ_DIR=$(DEBUG_SHARED_OBJ_DIR)/x64

# --- SOURCE FILES

SHARED=$(wildcard src/shared/*.cpp)
SOURCES=$(wildcard src/loader/*.cpp)
DLL_SOURCES=$(wildcard src/dll/*.cpp)

# --- OBJECT FILES

X86_RELEASE_SHARED_OBJ=$(SHARED:%.cpp=$(X86_RELEASE_SHARED_OBJ_DIR)/%.o)
X86_DEBUG_SHARED_OBJ=$(SHARED:%.cpp=$(X86_DEBUG_SHARED_OBJ_DIR)/%.o)
X64_RELEASE_SHARED_OBJ=$(SHARED:%.cpp=$(X64_RELEASE_SHARED_OBJ_DIR)/%.o)
X64_DEBUG_SHARED_OBJ=$(SHARED:%.cpp=$(X64_DEBUG_SHARED_OBJ_DIR)/%.o)

RELEASE_OBJ=$(SOURCES:%.cpp=$(RELEASE_DIR)/obj/%.o)
DEBUG_OBJ=$(SOURCES:%.cpp=$(DEBUG_DIR)/obj/%.o)

DLL_RELEASE_OBJ=$(DLL_SOURCES:%.cpp=$(RELEASE_DLL_DIR)/obj/%.o)
DLL_DEBUG_OBJ=$(DLL_SOURCES:%.cpp=$(DEBUG_DLL_DIR)/obj/%.o)

# --- HEADER FILES

# todo

# -----------------------------

# --- LIBRARIES

# - empty

# --- COMMON part

.PHONY: all release debug release_dll debug_dll clean

all: release debug release_dll debug_dll

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR) $(RELEASE_DLL_DIR) $(DEBUG_DLL_DIR) $(RELEASE_SHARED_OBJ_DIR) $(DEBUG_SHARED_OBJ_DIR)


# --- SHARED part

$(X86_RELEASE_SHARED_OBJ_DIR)/%.o: %.cpp
	@echo "[x86][RELEASE][SHARED] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CCx86) $(CFLAGS) -O3 -c $< -o $@

$(X86_DEBUG_SHARED_OBJ_DIR)/%.o: %.cpp
	@echo "[x86][DEBUG][SHARED] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CCx86) $(CFLAGS) -O0 -g -DDEBUG -c $< -o $@

$(X64_RELEASE_SHARED_OBJ_DIR)/%.o: %.cpp
	@echo "[x64][RELEASE][SHARED] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CCx64) $(CFLAGS) -O3 -c $< -o $@

$(X64_DEBUG_SHARED_OBJ_DIR)/%.o: %.cpp
	@echo "[x64][DEBUG][SHARED] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CCx64) $(CFLAGS) -O0 -g -DDEBUG -c $< -o $@

# --- LOADER part

release: $(RELEASE_DIR)/$(PE_NAME)

debug: $(DEBUG_DIR)/$(PE_NAME)$(DEBUG_NAME_SUFFIX)

# compiling

$(RELEASE_DIR)/obj/%.o: %.cpp
	@echo "[x64][RELEASE][LOADER] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CCx64) $(CFLAGS) -m64 -O3 -c $< -o $@

$(DEBUG_DIR)/obj/%.o: %.cpp
	@echo "[x64][DEBUG][LOADER] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CCx64) $(CFLAGS) -m64 -O0 -g -DDEBUG -c $< -o $@

# linking

$(RELEASE_DIR)/$(PE_NAME): $(RELEASE_OBJ) $(X64_RELEASE_SHARED_OBJ)
	@echo "[x64][RELEASE][LOADER] Linking: $^ into $@"
	@mkdir -p $(RELEASE_DIR)
	$(CCx64) $(LDFLAGS) -m64 -o $(RELEASE_DIR)/$(PE_NAME) $^

$(DEBUG_DIR)/$(PE_NAME)$(DEBUG_NAME_SUFFIX): $(DEBUG_OBJ) $(X64_DEBUG_SHARED_OBJ)
	@echo "[x64][DEBUG][LOADER] Linking: $^ into $@"
	@mkdir -p $(DEBUG_DIR)
	$(CCx64) $(LDFLAGS) -m64 -g -o $(DEBUG_DIR)/$(PE_NAME)$(DEBUG_NAME_SUFFIX) $^

# --- DLL part

release_dll: $(RELEASE_DLL_DIR)/$(DLL_NAME).dll

debug_dll: $(DEBUG_DLL_DIR)/$(DLL_NAME)$(DEBUG_NAME_SUFFIX).dll

# compiling

$(RELEASE_DLL_DIR)/obj/%.o: %.cpp
	@echo "[x86][RELEASE][DLL] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CCx86) $(CFLAGS) -m32 -O3 -c $< -o $@

$(DEBUG_DLL_DIR)/obj/%.o: %.cpp
	@echo "[x86][DEBUG][DLL] Compiling: $< into $@"
	@mkdir -p $(dir $@)
	$(CCx86) $(CFLAGS) -m32 -O0 -g -DDEBUG -c $< -o $@

# linking

$(RELEASE_DLL_DIR)/$(DLL_NAME).dll: $(DLL_RELEASE_OBJ) $(X86_RELEASE_SHARED_OBJ)
	@echo "[x86][RELEASE][DLL] Linking: $^ into $@"
	@mkdir -p $(RELEASE_DLL_DIR)
	$(CCx86) $(LDFLAGS) -m32 -shared -o $(RELEASE_DLL_DIR)/$(DLL_NAME).dll $^

$(DEBUG_DLL_DIR)/$(DLL_NAME)$(DEBUG_NAME_SUFFIX).dll: $(DLL_DEBUG_OBJ) $(X86_DEBUG_SHARED_OBJ)
	@echo "[x86][DEBUG][DLL] Linking: $^ into $@"
	@mkdir -p $(DEBUG_DLL_DIR)
	$(CCx86) $(LDFLAGS) -m32 -shared -g -o $(DEBUG_DLL_DIR)/$(DLL_NAME)$(DEBUG_NAME_SUFFIX).dll $^
