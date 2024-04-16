CFLAGS=-Wall -Wextra -Wno-unused-parameter -O2 -m32
LDFLAGS=-static-libgcc -static-libstdc++ -m32

CC=g++
PE_NAME=advanced-memory
DLL_NAME=advanced-library

RELEASE_DIR=build/release
DEBUG_DIR=build/debug
RELEASE_DLL_DIR=build/release_dll
DEBUG_DLL_DIR=build/debug_dll

SHARED=$(wildcard ./src/shared/*.cpp)
SOURCES=$(SHARED) $(wildcard src/loader/*.cpp)
DLL_SOURCES=$(SHARED) $(wildcard src/dll/*.cpp)

RELEASE_OBJ=$(SOURCES:%.cpp=$(RELEASE_DIR)/obj/%.o)
DEBUG_OBJ=$(SOURCES:%.cpp=$(DEBUG_DIR)/obj/%.o)
DLL_RELEASE_OBJ=$(DLL_SOURCES:%.cpp=$(RELEASE_DLL_DIR)/obj/%.o)
DLL_DEBUG_OBJ=$(DLL_SOURCES:%.cpp=$(DEBUG_DLL_DIR)/obj/%.o)

.PHONY: all release debug release_dll debug_dll clean

all: release debug release_dll debug_dll

release: $(RELEASE_OBJ)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(LDFLAGS) -o $(RELEASE_DIR)/$(PE_NAME) $(RELEASE_OBJ)

debug: $(DEBUG_OBJ)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(LDFLAGS) -g -o $(DEBUG_DIR)/$(PE_NAME)_debug $(DEBUG_OBJ)

release_dll: $(DLL_RELEASE_OBJ)
	@mkdir -p $(RELEASE_DLL_DIR)
	$(CC) $(LDFLAGS) -shared -o $(RELEASE_DLL_DIR)/$(DLL_NAME).dll $(DLL_RELEASE_OBJ)

debug_dll: $(DLL_DEBUG_OBJ)
	@mkdir -p $(DEBUG_DLL_DIR)
	$(CC) $(LDFLAGS) -shared -g -o $(DEBUG_DLL_DIR)/$(DLL_NAME)_debug.dll $(DLL_DEBUG_OBJ)

$(RELEASE_DIR)/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(DEBUG_DIR)/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O0 -g -DDEBUG -c $< -o $@

$(RELEASE_DLL_DIR)/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(DEBUG_DLL_DIR)/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O0 -g -DDEBUG -c $< -o $@

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR) $(RELEASE_DLL_DIR) $(DEBUG_DLL_DIR)
