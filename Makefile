CXX ?= g++

COMPILE_FLAGS += -std=c++23 -O2 -MMD -MP 
INCLUDE := -Iinclude

SRC_DIRS := ./source
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.d)

OUTPUT := dungeon.out

.PHONY: clean all

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $< -c -o $@ $(INCLUDE) $(COMPILE_FLAGS)

clean:
	rm -f $(OBJS) $(DEPS) $(OUTPUT) 

-include $(SRCS:%.cpp=%.d)