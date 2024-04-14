CC=g++

PE_NAME=advanced-memory

RELEASE_DIR=release
DEBUG_DIR=debug

CFLAGS=-Wall -Wextra -O2 -m32 -I./src -I./src/includes -I./src/dynamiclinker
LDFLAGS=-static-libgcc -static-libstdc++ -m32

SOURCES=./src/main.cpp ./src/dynamiclinker/dynamiclinker.cpp

RELEASE_OBJ=$(SOURCES:%.cpp=$(RELEASE_DIR)/obj/%.o)
DEBUG_OBJ=$(SOURCES:%.cpp=$(DEBUG_DIR)/obj/%.o)

.PHONY: all release debug clean_release clean_debug

all: release

release: CFLAGS += -O2
release: TARGET=$(RELEASE_DIR)/$(PE_NAME)
release: $(RELEASE_OBJ)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) -o $(TARGET) $(RELEASE_OBJ)

debug: CFLAGS += -g3 -O0
debug: TARGET=$(DEBUG_DIR)/$(PE_NAME)
debug: $(DEBUG_OBJ)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) -o $(TARGET) $(DEBUG_OBJ)

# Generic rule for object files
$(RELEASE_DIR)/obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUG_DIR)/obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean_release:
	@rm -rf $(RELEASE_DIR)

clean_debug:
	@rm -rf $(DEBUG_DIR)
