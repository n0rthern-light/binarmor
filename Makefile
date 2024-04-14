CC=g++
PE_NAME=advanced-memory
DLL_NAME=advanced-library

RELEASE_DIR=release
DEBUG_DIR=debug
RELEASE_DLL_DIR=release_dll
DEBUG_DLL_DIR=debug_dll

SOURCES=$(wildcard ./src/*.cpp ./src/**/*.cpp)
DLL_SOURCES=$(wildcard ./src_dll/*.cpp ./src_dll/**/*.cpp)

RELEASE_OBJ=$(SOURCES:%.cpp=$(RELEASE_DIR)/obj/%.o)
DEBUG_OBJ=$(SOURCES:%.cpp=$(DEBUG_DIR)/obj/%.o)
DLL_RELEASE_OBJ=$(DLL_SOURCES:%.cpp=$(RELEASE_DLL_DIR)/obj/%.o)
DLL_DEBUG_OBJ=$(DLL_SOURCES:%.cpp=$(DEBUG_DLL_DIR)/obj/%.o)

HEADER_DIRS = $(shell find ./src ./src_dll -type d \( -name '*.h' -o -name '*.hpp' \) -exec dirname {} \; | sort -u)

CFLAGS=-Wall -Wextra -O2 -m32 $(foreach dir,$(HEADER_DIRS),-I$(dir))
LDFLAGS=-static-libgcc -static-libstdc++ -m32

.PHONY: all release debug release_dll debug_dll clean

all: release debug release_dll debug_dll

release: $(RELEASE_OBJ)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(LDFLAGS) -o $(RELEASE_DIR)/$(PE_NAME) $(RELEASE_OBJ)

debug: $(DEBUG_OBJ)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(LDFLAGS) -g -o $(DEBUG_DIR)/$(PE_NAME) $(DEBUG_OBJ)

release_dll: $(DLL_RELEASE_OBJ)
	@mkdir -p $(RELEASE_DLL_DIR)
	$(CC) $(LDFLAGS) -shared -o $(RELEASE_DLL_DIR)/$(DLL_NAME).dll $(DLL_RELEASE_OBJ)

debug_dll: $(DLL_DEBUG_OBJ)
	@mkdir -p $(DEBUG_DLL_DIR)
	$(CC) $(LDFLAGS) -shared -g -o $(DEBUG_DLL_DIR)/$(DLL_NAME).dll $(DLL_DEBUG_OBJ)

# Rule to compile .cpp to .o
$(RELEASE_DIR)/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(DEBUG_DIR)/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O0 -g -c $< -o $@

$(RELEASE_DLL_DIR)/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(DEBUG_DLL_DIR)/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O0 -g -c $< -o $@

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR) $(RELEASE_DLL_DIR) $(DEBUG_DLL_DIR)
