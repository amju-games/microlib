# microlib - minimal game utilty library
# Copyright (C) 2024 Juliet Colman 

# Source files directory
SRCDIR := source
TESTDIR := unit_tests
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep

# Target executable name
TARGET := libmicro.a
TEST_EXE := microlib_tests_exe
TEST_TARGET := $(TESTDIR)/$(TEST_EXE)

# Include dir for unit tests
TESTS_INCLUDE := -I$(SRCDIR)

# Flags for compiling
CXXFLAGS := -std=c++20 -Wall $(TESTS_INCLUDE)

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
TEST_SRCS := $(wildcard $(TESTDIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TEST_OBJS := $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SRCS))

# Dependencies
DEPS := $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)


# Platform detection
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin) # macOS
    # Add Mac-specific flags or configurations if needed
    LDFLAGS=-framework Carbon
    CXXFLAGS += -DMACOSX
    CXX := clang++
else ifeq ($(OS), Windows_NT) # Windows
    # Add Windows-specific flags or configurations if needed
else ifneq ("$(wildcard /proc/device-tree/model)","") # Raspberry Pi
    # Add Raspberry Pi-specific flags or configurations if needed
    CXXFLAGS += -DRASPBERRY_PI
    CXX := g++
endif

# Default rule
all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(filter-out $(OBJDIR)/main.o,$(OBJS))
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

clean:
	@rm -rf $(TARGET) $(TEST_TARGET) $(BUILDDIR)

runtests:
	cd $(TESTDIR); ./$(TEST_EXE); cd ..

-include $(DEPS)

.PHONY: all clean

