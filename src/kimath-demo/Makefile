KICAD    := $(HOME)/not-my-projects/kicad
KIMATH   := $(KICAD)/libs/kimath
FMT      := $(KICAD)/thirdparty/fmt/include
CLIPPER  := $(KICAD)/thirdparty/clipper2/Clipper2Lib/include
WX_STUB  := ../wx-stub
KLIB     := ../kimath-build/libkimath.a
CLIPLIB  := ../clipper2-build/libclipper2.a
BOOST_INC := $(HOME)/local/kicad-root/usr/include

CXXFLAGS := -O2 -std=c++20 \
            -I$(KIMATH)/include -I$(WX_STUB) -I$(FMT) -I$(CLIPPER) \
            -I$(KICAD)/libs/core/include -I$(KICAD)/include \
            -I$(KICAD)/build-mini -I$(KICAD)/thirdparty \
            -I$(BOOST_INC) \
            -DFMT_HEADER_ONLY=1 -DUSINGZ=1
EMFLAGS  := --bind \
            -sMODULARIZE=1 -sEXPORT_ES6=0 \
            -sENVIRONMENT=node,web,worker \
            -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=1048576

kimath-demo.js: main.cpp $(KLIB) $(CLIPLIB) $(WX_STUB)/stub_advanced_config.cpp
	em++ $(CXXFLAGS) $(EMFLAGS) -o $@ main.cpp \
	     $(WX_STUB)/stub_advanced_config.cpp \
	     $(KLIB) $(CLIPLIB)

test: kimath-demo.js
	node test-node.js

clean:
	rm -f kimath-demo.js kimath-demo.wasm

.PHONY: test clean
