CC=g++

PE_NAME=advanced-memory

RELEASE_DIR=release
DEBUG_DIR=debug

CFLAGS=-Wall -Wextra -O2 -m32
LDFLAGS=-static-libgcc -static-libstdc++ -m32

SOURCES=main.cpp

# Defining the object directories and setting targets
RELEASE_OBJ=$(SOURCES:%.cpp=$(RELEASE_DIR)/obj/%.o)
DEBUG_OBJ=$(SOURCES:%.cpp=$(DEBUG_DIR)/obj/%.o)

# Default target
.PHONY: all
all: release

# Release build
release: CFLAGS += -O2
release: TARGET=$(RELEASE_DIR)/$(PE_NAME)
release: $(RELEASE_OBJ)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(LDFLAGS) -o $(TARGET) $(RELEASE_OBJ)

# Debug build
debug: CFLAGS += -g3 -O0
debug: TARGET=$(DEBUG_DIR)/$(PE_NAME)
debug: $(DEBUG_OBJ)
	@mkdir -p $(DEBUG_DIR)
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

.PHONY: all release debug clean_release clean_debug
