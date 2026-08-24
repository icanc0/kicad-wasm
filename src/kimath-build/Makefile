# Build KiCad's libs/kimath to WASM.
# Usage:  source ../../build/emsdk-env.sh; make -j
KICAD    := $(HOME)/not-my-projects/kicad
KIMATH   := $(KICAD)/libs/kimath
FMT      := $(KICAD)/thirdparty/fmt/include
CLIPPER  := $(KICAD)/thirdparty/clipper2/Clipper2Lib/include
CORE_INC := $(KICAD)/libs/core/include
WX_STUB  := ../wx-stub
CONFIG_H_DIR := $(KICAD)/build-mini
BOOST_INC := $(HOME)/local/kicad-root/usr/include

CXX      := em++
CXXFLAGS := -O2 -std=c++20 \
            -I$(KIMATH)/include -I$(WX_STUB) -I$(FMT) -I$(CLIPPER) \
            -I$(CORE_INC) -I$(KICAD)/include -I$(CONFIG_H_DIR) \
            -I$(KICAD)/thirdparty -I$(BOOST_INC) \
            -DFMT_HEADER_ONLY=1

# All src files under kimath.
SRC_FILES := $(wildcard $(KIMATH)/src/*.cpp) \
             $(wildcard $(KIMATH)/src/geometry/*.cpp) \
             $(wildcard $(KIMATH)/src/math/*.cpp)

# Object files under obj/, flat.
OBJ_DIR := obj
OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))

# The map: object → source (needed because we flatten). Use a rule per src.
define COMPILE_TEMPLATE
$(OBJ_DIR)/$(notdir $(1:.cpp=.o)): $(1)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $$@ $$<
endef

$(foreach s,$(SRC_FILES),$(eval $(call COMPILE_TEMPLATE,$s)))

libkimath-partial.a: $(OBJ_FILES)
	emar rcs $@ $^

all: libkimath-partial.a

clean:
	rm -rf $(OBJ_DIR) libkimath-partial.a

list-sources:
	@echo $(SRC_FILES) | tr ' ' '\n'

.PHONY: all clean list-sources
