# Build the sexpr POC to WASM.
# Usage:   source ../../build/emsdk-env.sh; make
KICAD_SRC := $(HOME)/not-my-projects/kicad
FMT_INC   := $(KICAD_SRC)/thirdparty/fmt/include
WX_STUB   := ../wx-stub

CXX       := em++
CXXFLAGS  := -O2 -std=c++20 \
             -I. -I$(WX_STUB) -I$(FMT_INC) \
             -DFMT_HEADER_ONLY=1
EMFLAGS   := --bind \
             -sMODULARIZE=1 -sEXPORT_ES6=0 \
             -sENVIRONMENT=node,web,worker \
             -sALLOW_MEMORY_GROWTH=1 \
             -sSTACK_SIZE=1048576

SRCS := main.cpp sexpr.cpp sexpr_parser.cpp

all: sexpr.js

sexpr.js: $(SRCS)
	$(CXX) $(CXXFLAGS) $(EMFLAGS) -o $@ $(SRCS)

test: sexpr.js
	node test-node.js

clean:
	rm -f sexpr.js sexpr.wasm

.PHONY: all test clean
