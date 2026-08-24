#!/bin/bash
# Source this to get emscripten on PATH.
# Assumes emsdk is at ~/local/emsdk (see ROADMAP M0.2).
export EMSDK="$HOME/local/emsdk"
export PATH="$EMSDK:$EMSDK/upstream/emscripten:$EMSDK/upstream/bin:$PATH"
export EMSDK_NODE="$EMSDK/node/24.19.0_64bit/bin/node"
