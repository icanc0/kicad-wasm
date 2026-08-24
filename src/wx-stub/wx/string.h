// Minimal wx/string.h stub for kicad-wasm.
// wxString → thin wrapper over std::string, char-only. Enough for the
// KiCad code that just formats / compares / concatenates messages;
// wxWidgets-Unicode features intentionally omitted (add as needed).
#pragma once
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <string_view>
#include <utility>

#include "wx/defs.h"

#undef wxASCII_STR
#define wxASCII_STR(x) wxString(x)

class wxString {
public:
    std::string m_s;

    wxString() = default;
    wxString(const char* s) : m_s(s ? s : "") {}
    wxString(const std::string& s) : m_s(s) {}
    wxString(std::string&& s) : m_s(std::move(s)) {}
    wxString(const wxString&) = default;
    wxString(wxString&&) noexcept = default;
    wxString& operator=(const wxString&) = default;
    wxString& operator=(wxString&&) noexcept = default;
    wxString& operator=(const char* s) { m_s = s ? s : ""; return *this; }

    // Construction from wide/unicode omitted; add when a caller needs it.

    // Static builders.
    static wxString FromAscii(const char* s) { return wxString(s); }
    static wxString FromUTF8(const char* s)  { return wxString(s); }
    static wxString FromUTF8(const std::string& s) { return wxString(s); }
    static wxString From8BitData(const char* s) { return wxString(s); }
    static wxString From8BitData(const char* s, size_t n) {
        return wxString(std::string(s, n));
    }

private:
    // Auto-convert wxString args to const char* for printf-family calls,
    // pass everything else through untouched.
    template<typename T>
    static auto _fmt_arg(const T& v) {
        if constexpr (std::is_same_v<std::decay_t<T>, wxString>)
            return v.m_s.c_str();
        else if constexpr (std::is_same_v<std::decay_t<T>, std::string>)
            return v.c_str();
        else
            return v;
    }

    static wxString _fmt_impl(const char* fmt, ...) {
        char buf[512];
        std::va_list ap;
        va_start(ap, fmt);
        int n = std::vsnprintf(buf, sizeof buf, fmt, ap);
        va_end(ap);
        if (n < 0) return wxString();
        if ((size_t)n < sizeof buf) return wxString(std::string(buf, n));
        std::string out;
        out.resize(n + 1);
        va_start(ap, fmt);
        std::vsnprintf(out.data(), out.size(), fmt, ap);
        va_end(ap);
        out.resize(n);
        return wxString(std::move(out));
    }

public:
    // Variadic-template Format: safe for wxString/std::string args
    // (unlike `...`, which is UB for non-trivial types).
    template<typename... Args>
    static wxString Format(const char* fmt, Args&&... args) {
        return _fmt_impl(fmt, _fmt_arg(std::forward<Args>(args))...);
    }
    // No-arg overload so plain literals still work.
    static wxString Format(const char* fmt) { return wxString(fmt); }

    // Basic queries.
    bool IsEmpty() const { return m_s.empty(); }
    bool empty()   const { return m_s.empty(); }
    size_t length() const { return m_s.length(); }
    size_t size()   const { return m_s.size(); }
    size_t Length() const { return m_s.length(); }
    size_t Len()    const { return m_s.length(); }

    // Access as C string / std::string.
    const char* c_str() const { return m_s.c_str(); }
    const char* mb_str() const { return m_s.c_str(); }
    const char* ToUTF8() const { return m_s.c_str(); }
    const char* utf8_str() const { return m_s.c_str(); }
    std::string ToStdString() const { return m_s; }
    operator const std::string&() const { return m_s; }
    // Convert to const char* implicitly — KiCad code passes wxString to
    // API expecting a plain C string.
    operator const char*() const { return m_s.c_str(); }
    // Real wxWidgets returns a wxScopedCharBuffer from utf8_string();
    // approximate with std::string. Used in KiCad's newer code paths.
    std::string utf8_string() const { return m_s; }

    // Trivial to-number.
    bool ToCDouble(double* out) const {
        char* end = nullptr;
        double v = std::strtod(m_s.c_str(), &end);
        if (end == m_s.c_str()) return false;
        if (out) *out = v;
        return true;
    }
    bool ToLong(long* out, int base = 10) const {
        char* end = nullptr;
        long v = std::strtol(m_s.c_str(), &end, base);
        if (end == m_s.c_str()) return false;
        if (out) *out = v;
        return true;
    }

    // Case ops.
    wxString Lower() const {
        std::string r = m_s;
        for (auto& c : r) c = (char)std::tolower((unsigned char)c);
        return wxString(std::move(r));
    }
    wxString Upper() const {
        std::string r = m_s;
        for (auto& c : r) c = (char)std::toupper((unsigned char)c);
        return wxString(std::move(r));
    }
    wxString MakeLower() { for (auto& c : m_s) c = (char)std::tolower((unsigned char)c); return *this; }
    wxString MakeUpper() { for (auto& c : m_s) c = (char)std::toupper((unsigned char)c); return *this; }

    int Cmp(const wxString& r) const { return m_s.compare(r.m_s); }
    int CmpNoCase(const wxString& r) const {
        return Lower().Cmp(r.Lower());
    }

    // Search + substring.
    size_t find(const wxString& s, size_t pos = 0) const { return m_s.find(s.m_s, pos); }
    size_t find(char c, size_t pos = 0) const { return m_s.find(c, pos); }
    static constexpr size_t npos = std::string::npos;
    wxString substr(size_t pos, size_t n = std::string::npos) const {
        return wxString(m_s.substr(pos, n));
    }
    wxString Mid(size_t pos, size_t n = std::string::npos) const { return substr(pos, n); }
    wxString Left(size_t n)  const { return substr(0, n); }
    wxString Right(size_t n) const { return n >= m_s.size() ? *this : wxString(m_s.substr(m_s.size() - n)); }

    bool StartsWith(const wxString& s) const {
        return m_s.rfind(s.m_s, 0) == 0;
    }
    bool EndsWith(const wxString& s) const {
        return m_s.size() >= s.m_s.size()
            && 0 == m_s.compare(m_s.size() - s.m_s.size(), s.m_s.size(), s.m_s);
    }
    bool Contains(const wxString& s) const { return m_s.find(s.m_s) != npos; }

    // Concat + append.
    wxString& operator+=(const wxString& r) { m_s += r.m_s; return *this; }
    wxString& operator+=(const char* r)     { m_s += r; return *this; }
    wxString& operator+=(char c)            { m_s += c; return *this; }
    wxString& Append(const wxString& r)     { m_s += r.m_s; return *this; }
    // Stream-style concatenation, as wxString supports natively.
    wxString& operator<<(const wxString& r) { m_s += r.m_s; return *this; }
    wxString& operator<<(const char* r)     { m_s += r; return *this; }
    wxString& operator<<(char c)            { m_s += c; return *this; }
    wxString& operator<<(int i)             { m_s += std::to_string(i); return *this; }
    wxString& operator<<(long i)            { m_s += std::to_string(i); return *this; }
    wxString& operator<<(double d)          { m_s += std::to_string(d); return *this; }

    char operator[](size_t i) const { return m_s[i]; }
    char Last() const { return m_s.empty() ? '\0' : m_s.back(); }
    wxString& RemoveLast(size_t n = 1) {
        if (n >= m_s.size()) m_s.clear();
        else                 m_s.resize(m_s.size() - n);
        return *this;
    }
    void clear() { m_s.clear(); }
    void Clear() { m_s.clear(); }

    // Equality.
    bool operator==(const wxString& r) const { return m_s == r.m_s; }
    bool operator!=(const wxString& r) const { return m_s != r.m_s; }
    bool operator<(const wxString& r)  const { return m_s <  r.m_s; }
    bool operator==(const char* r)     const { return m_s == std::string(r ? r : ""); }
    bool operator!=(const char* r)     const { return !(*this == r); }

    // Iteration.
    using const_iterator         = std::string::const_iterator;
    using iterator               = std::string::iterator;
    using const_reverse_iterator = std::string::const_reverse_iterator;
    using reverse_iterator       = std::string::reverse_iterator;
    using value_type             = char;
    const_iterator begin() const { return m_s.begin(); }
    const_iterator end()   const { return m_s.end(); }
    iterator       begin()       { return m_s.begin(); }
    iterator       end()         { return m_s.end();   }
    const_reverse_iterator rbegin() const { return m_s.rbegin(); }
    const_reverse_iterator rend()   const { return m_s.rend(); }
    reverse_iterator       rbegin()       { return m_s.rbegin(); }
    reverse_iterator       rend()         { return m_s.rend(); }

    // fn_str for older API — return the raw C string.
    const char* fn_str() const { return m_s.c_str(); }

    // More KiCad-common methods.
    const char* GetData() const { return m_s.c_str(); }

    // Real wxWidgets: enum stripType { leading = 1, trailing = 2, both = 3 };
    // Accept int (default 2 = trailing) so pre-C++11 KiCad callers work.
    enum stripType { leading = 1, trailing = 2, both = 3 };
    wxString Strip(int mode = trailing) const {
        std::string r = m_s;
        if (mode & leading)  r.erase(0, r.find_first_not_of(" \t\r\n"));
        if (mode & trailing) {
            auto p = r.find_last_not_of(" \t\r\n");
            r.erase(p == std::string::npos ? 0 : p + 1);
        }
        return wxString(std::move(r));
    }
    wxString Trim(bool fromRight = true) const {
        return fromRight ? Strip(1) : Strip(2);
    }

    template<typename... Args>
    int Printf(const char* fmt, Args&&... args) {
        *this = Format(fmt, std::forward<Args>(args)...);
        return static_cast<int>(m_s.size());
    }

    // wxString::Find returns int (wx_NPOS if not found) or size_t depending
    // on overload; give npos-compatible size_t for callers we've seen.
    size_t Find(char c) const {
        auto p = m_s.find(c);
        return p == std::string::npos ? npos : p;
    }
    size_t Find(const wxString& s) const { return m_s.find(s.m_s); }

    // Real wxWidgets Replace returns the number of replacements made.
    int Replace(const wxString& from, const wxString& to, bool all = true) {
        int count = 0;
        size_t pos = 0;
        while ((pos = m_s.find(from.m_s, pos)) != std::string::npos) {
            m_s.replace(pos, from.m_s.size(), to.m_s);
            pos += to.m_s.size();
            ++count;
            if (!all) break;
        }
        return count;
    }
};

inline wxString operator+(const wxString& a, const wxString& b) {
    wxString r = a; r += b; return r;
}
inline wxString operator+(const wxString& a, const char* b) {
    wxString r = a; r += b; return r;
}
inline wxString operator+(const char* a, const wxString& b) {
    wxString r(a); r += b; return r;
}

// A few free-function helpers common in KiCad code.
inline wxString wxEmptyString{};

// wxLogWarning etc. reference wxLogLevelValues via wxString::Format;
// nothing else required here.

// Real wxWidgets pulls wxArrayString in transitively from wx/string.h.
#include "wx/arrstr.h"
