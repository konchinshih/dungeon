CXX ?= g++

COMPILE_FLAGS += -std=c++23 -Wall -Wextra -Werror -O0 -MMD -MP -Wno-unused-parameter -fsanitize=address,undefined -g
LINK_FLAGS += -fsanitize=address,undefined -g
INCLUDE := -Iinclude

SRC_DIRS := ./source
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.d)

OUTPUT := dungeon.out

.PHONY: clean all

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CXX) -o $@ $^ $(LINK_FLAGS)

%.o: %.cpp
	$(CXX) $< -c -o $@ $(INCLUDE) $(COMPILE_FLAGS)

clean:
	rm -f $(OBJS) $(DEPS) $(OUTPUT) 

-include $(SRCS:%.cpp=%.d)