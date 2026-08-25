// Minimal wx/ffile.h stub — buffered FILE* wrapper (differs from wx/file.h
// in the real wx where wxFFile uses FILE* and wxFile uses fd).
#pragma once
#include "wx/file.h"

class wxFFile {
    FILE* m_fp = nullptr;
public:
    wxFFile() = default;
    wxFFile(const wxString& path, const char* mode = "rb") { Open(path, mode); }
    ~wxFFile() { Close(); }
    bool Open(const wxString& path, const char* mode = "rb") {
        Close(); m_fp = std::fopen(path.c_str(), mode); return m_fp != nullptr;
    }
    bool IsOpened() const { return m_fp != nullptr; }
    bool Close() { if (!m_fp) return true; int r = std::fclose(m_fp); m_fp = nullptr; return r == 0; }
    size_t Read(void* buf, size_t n)              { return m_fp ? std::fread(buf, 1, n, m_fp) : 0; }
    size_t Write(const void* buf, size_t n)       { return m_fp ? std::fwrite(buf, 1, n, m_fp) : 0; }
    long   Length() const {
        if (!m_fp) return 0;
        long cur = std::ftell(m_fp);
        std::fseek(m_fp, 0, SEEK_END);
        long len = std::ftell(m_fp);
        std::fseek(m_fp, cur, SEEK_SET);
        return len;
    }
    bool Eof() const { return m_fp && std::feof(m_fp); }
    FILE* fp() const { return m_fp; }
};
