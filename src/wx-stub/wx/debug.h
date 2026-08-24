// Minimal wx/debug.h stub for kicad-wasm.
// Just enough for what libs/sexpr uses.
#pragma once
#include <cassert>
#define wxASSERT(cond)              assert(cond)
#define wxASSERT_MSG(cond, msg)     assert((cond) && (msg))
#define wxCHECK(cond, ret)          do { if(!(cond)) return (ret); } while(0)
#define wxCHECK_MSG(cond, ret, msg) do { if(!(cond)) return (ret); } while(0)
#define wxCHECK_RET(cond, msg)      do { if(!(cond)) return; } while(0)
#define wxFAIL_MSG(msg)             assert((0) && (msg))
