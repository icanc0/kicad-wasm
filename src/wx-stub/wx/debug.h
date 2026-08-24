// Minimal wx/debug.h stub for kicad-wasm.
// Just enough for what libs/sexpr + libs/kimath use.
#pragma once
#include <cassert>

#define wxASSERT(cond)              assert(cond)
#define wxASSERT_MSG(cond, msg)     assert((cond) && (msg))
#define wxASSERT_MIN_BITSIZE(t, n)  static_assert(sizeof(t)*8 >= (n))
#define wxCHECK(cond, ret)          do { if(!(cond)) return (ret); } while(0)
#define wxCHECK2(cond, x)           do { if(!(cond)) { x; } } while(0)
#define wxCHECK2_MSG(cond, x, msg)  do { if(!(cond)) { x; } } while(0)
#define wxCHECK_MSG(cond, ret, msg) do { if(!(cond)) return (ret); } while(0)
#define wxCHECK_RET(cond, msg)      do { if(!(cond)) return; } while(0)
#define wxFAIL_MSG(msg)             assert((0) && "wxFAIL_MSG")
#define wxFAIL()                    assert((0) && "wxFAIL")
#define wxCOMPILE_TIME_ASSERT(cond, msg)  static_assert(cond, #msg)
#define wxDEBUG_LEVEL 0
