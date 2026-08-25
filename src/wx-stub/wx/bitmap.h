// Minimal wx/bitmap.h stub — image data only, no rendering.
// KiCad code names wxBitmap in property-editor headers and similar
// data-carrying contexts; actual raster ops are in UI code paths
// we don't compile.
#pragma once
#include "wx/defs.h"
#include "wx/string.h"
#include "wx/gdicmn.h"

class wxImage {
    int m_w = 0, m_h = 0;
public:
    wxImage() = default;
    wxImage(int w, int h) : m_w(w), m_h(h) {}
    int  GetWidth()  const { return m_w; }
    int  GetHeight() const { return m_h; }
    bool IsOk()      const { return m_w > 0 && m_h > 0; }
    bool SaveFile(const wxString&, int = 0) const { return false; }
    bool LoadFile(const wxString&, int = 0) { return false; }
};

enum wxBitmapType {
    wxBITMAP_TYPE_INVALID = 0,
    wxBITMAP_TYPE_BMP     = 1,
    wxBITMAP_TYPE_PNG     = 2,
    wxBITMAP_TYPE_JPEG    = 3,
    wxBITMAP_TYPE_GIF     = 4,
    wxBITMAP_TYPE_ANY     = 50,
};

class wxBitmap {
    int m_w = 0, m_h = 0;
public:
    wxBitmap() = default;
    wxBitmap(int w, int h, int = -1) : m_w(w), m_h(h) {}
    wxBitmap(const wxImage& img) : m_w(img.GetWidth()), m_h(img.GetHeight()) {}
    wxBitmap(const char* const*) {}                          // xpm data
    int  GetWidth()  const { return m_w; }
    int  GetHeight() const { return m_h; }
    bool IsOk()      const { return m_w > 0 && m_h > 0; }
    wxImage ConvertToImage() const { return wxImage(m_w, m_h); }
    bool SaveFile(const wxString&, wxBitmapType = wxBITMAP_TYPE_PNG) const { return false; }
    bool LoadFile(const wxString&, wxBitmapType = wxBITMAP_TYPE_ANY) { return false; }
};

// wxBitmapBundle — carries scaled variants in real wx; here it's a shim.
class wxBitmapBundle {
public:
    wxBitmapBundle() = default;
    wxBitmapBundle(const wxBitmap&) {}
    static wxBitmapBundle FromBitmap(const wxBitmap& b) { return wxBitmapBundle(b); }
    static wxBitmapBundle FromImpl(void*) { return {}; }
    bool IsOk() const { return true; }
    wxBitmap GetBitmap(const wxSize&) const { return {}; }
};

// Real wx provides wxNullBitmap sentinel.
inline const wxBitmap wxNullBitmap;
