COMPILER := g++
COMPILER_FLAG := -g -lstdc++ -std=c++20

BUILD_DIR := build

ALL_SRCS:=$(wildcard **/*.cpp)
SRCS:= $(filter-out Tests/, $(ALL_SRCS))
OBJS:=$(foreach src, $(SRCS), $(BUILD_DIR)/$(subst .cpp,.o,$(src)))

.PHONY: all
all: prepare nbodysimapp 

.PHONY: clean
clean:
	rm -rf build/**/*.o

prepare:
	./scripts/createBuildFolder.sh

nbodysimapp: $(OBJS)
	$(COMPILER) $(COMPILER_FLAG) $(OBJS) -o $(BUILD_DIR)/nbodysimapp

$(OBJS): $(BUILD_DIR)/%.o : %.cpp
	$(COMPILER) $(COMPILER_FLAG) -c $< -o $@
