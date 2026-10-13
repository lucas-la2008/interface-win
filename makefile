CXX ?= g++
CC ?= gcc

MODE ?= debug

TARGET = build/bin/libinterface.dll

LDFLAGS = -shared
LDLIBS = -lglfw3 -L deps/glfw -lgdi32 -lopengl32

CXXFLAGS = -std=c++20 -fPIC -Iinclude 
CFLAGS = -fPIC -Iinclude

ifeq ($(MODE),debug)
	CXXFLAGS += -g -O0
else ifeq ($(MODE),release)
	CXXFLAGS += -O3
	CFLAGS += -O3
else ifeq ($(MODE),relwithdebuginfo)
	CXXFLAGS += -O2 -g
endif

SRCS_C = $(shell powershell -Command "Get-ChildItem -Path ./src -Filter '*.c' -Recurse | Resolve-Path -Relative | ForEach-Object { $$_ -replace '\\','/' }")
SRCS_CPP = $(shell powershell -Command "Get-ChildItem -Path .\src -Filter '*.cpp' -Recurse | Resolve-Path -Relative | ForEach-Object { $$_ -Replace '\\','/' }")

OBJS = $(patsubst ./src/%.c, ./build/obj/%.o, $(SRCS_C))
OBJS += $(patsubst ./src/%.cpp, ./build/obj/%.o, $(SRCS_CPP))

PYTHON := python3

SHADER_HEADER := build/bin/generated/shaders.hpp
SHADER_SOURCES := shaders/shader.vert shaders/shader.frag
SHADER_SCRIPT := scripts/embed_shaders.py

all: $(TARGET)

$(TARGET): $(OBJS)
	powershell -Command "mkdir $(dir $@) -Force"
	$(CXX) $^ $(LDFLAGS) -o $@ $(LDLIBS)

build/obj/%.o: src/%.cpp
	powershell -Command "mkdir $(dir $@) -Force"
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/obj/renderer.o: src/renderer.cpp $(SHADER_HEADER)

build/obj/%.o: src/%.c
	powershell -Command "mkdir $(dir $@) -Force"
	$(CC) $(CFLAGS) -c $< -o $@

$(SHADER_HEADER): $(SHADER_SOURCES) $(SHADER_SCRIPT)
	powershell -Command "mkdir $(dir $@) -Force"
	$(PYTHON) $(SHADER_SCRIPT) $(SHADER_SOURCES) $@

clean:
	powershell -Command "rm .\build\* -Recurse -Force"