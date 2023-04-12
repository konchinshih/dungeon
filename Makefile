CXX ?= g++

COMPILE_FLAGS += -std=c++23 -W -Wall -Wextra -Werror -O0 -Wno-unused-parameter -fsanitize=address,undefined -g
LINK_FLAGS += -fsanitize=address,undefined -g

SRC_DIRS := ./source
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

OBJS :=$(SRCS:%.cpp=%.o)

DUNGEON := dungeon.out

.PHONY: clean all

all: $(DUNGEON)

$(DUNGEON): $(OBJS)
	$(CXX) -o $@ $^ $(LINK_FLAGS)

%.o: %.cpp
	$(CXX) $< -c -o $@ $(COMPILE_FLAGS)

clean:
	rm -f $(OBJS) $(DUNGEON)