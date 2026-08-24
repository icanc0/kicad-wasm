// Minimal wx/gdicmn.h stub — GDI common types (point, rect, size, color).
// KiCad code that just uses these as data (not for actual rendering) is
// fine. Real drawing is done by KiCad's own GAL / plotter code paths.
#pragma once
#include "wx/defs.h"
#include "wx/string.h"

class wxPoint {
public:
    int x = 0, y = 0;
    wxPoint() = default;
    wxPoint(int px, int py) : x(px), y(py) {}
    wxPoint operator+(const wxPoint& r) const { return {x + r.x, y + r.y}; }
    wxPoint operator-(const wxPoint& r) const { return {x - r.x, y - r.y}; }
    bool operator==(const wxPoint& r) const { return x == r.x && y == r.y; }
    bool operator!=(const wxPoint& r) const { return !(*this == r); }
};

class wxSize {
public:
    int x = 0, y = 0;   // aka width, height
    wxSize() = default;
    wxSize(int w, int h) : x(w), y(h) {}
    int GetWidth()  const { return x; }
    int GetHeight() const { return y; }
    void SetWidth(int w)  { x = w; }
    void SetHeight(int h) { y = h; }
    bool operator==(const wxSize& r) const { return x == r.x && y == r.y; }
};

class wxRect {
public:
    int x = 0, y = 0, width = 0, height = 0;
    wxRect() = default;
    wxRect(int px, int py, int w, int h) : x(px), y(py), width(w), height(h) {}
    wxRect(const wxPoint& tl, const wxSize& sz)
        : x(tl.x), y(tl.y), width(sz.x), height(sz.y) {}
    int GetLeft()   const { return x; }
    int GetTop()    const { return y; }
    int GetRight()  const { return x + width - 1; }
    int GetBottom() const { return y + height - 1; }
    int GetWidth()  const { return width; }
    int GetHeight() const { return height; }
    wxPoint GetPosition() const { return {x, y}; }
    wxSize  GetSize() const { return {width, height}; }
    bool Contains(int px, int py) const {
        return px >= x && py >= y && px < x + width && py < y + height;
    }
    bool Contains(const wxPoint& p) const { return Contains(p.x, p.y); }
    bool IsEmpty() const { return width == 0 || height == 0; }
};

class wxColour {
    unsigned char m_r = 0, m_g = 0, m_b = 0, m_a = 255;
public:
    wxColour() = default;
    wxColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
        : m_r(r), m_g(g), m_b(b), m_a(a) {}
    wxColour(const wxString&) {}   // name lookup — ignored
    unsigned char Red()   const { return m_r; }
    unsigned char Green() const { return m_g; }
    unsigned char Blue()  const { return m_b; }
    unsigned char Alpha() const { return m_a; }
    bool IsOk() const { return true; }
    bool operator==(const wxColour& r) const {
        return m_r == r.m_r && m_g == r.m_g && m_b == r.m_b && m_a == r.m_a;
    }
    bool operator!=(const wxColour& r) const { return !(*this == r); }
};

using wxRealPoint = wxPoint;
