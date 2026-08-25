// Minimal wx/file.h stub — buffered file I/O over std::fstream.
#pragma once
#include "wx/string.h"
#include <cstddef>
#include <cstdio>
#include <sys/stat.h>

enum wxSeekMode_ { wxFromStart = 0, wxFromCurrent = 1, wxFromEnd = 2 };

class wxFile {
    FILE* m_fp = nullptr;
public:
    enum OpenMode { read = 0, write = 1, read_write = 2, write_append = 3, write_excl = 4 };
    wxFile() = default;
    wxFile(const wxString& path, OpenMode m = read) { Open(path, m); }
    ~wxFile() { Close(); }
    bool Open(const wxString& path, OpenMode m = read) {
        const char* mode = "rb";
        switch (m) {
            case read:         mode = "rb"; break;
            case write:        mode = "wb"; break;
            case read_write:   mode = "rb+"; break;
            case write_append: mode = "ab"; break;
            case write_excl:   mode = "wbx"; break;
        }
        Close();
        m_fp = std::fopen(path.c_str(), mode);
        return m_fp != nullptr;
    }
    bool IsOpened() const { return m_fp != nullptr; }
    bool Close()          { if (!m_fp) return true; int r = std::fclose(m_fp); m_fp = nullptr; return r == 0; }
    size_t Read(void* buf, size_t n)              { return m_fp ? std::fread(buf, 1, n, m_fp) : 0; }
    size_t Write(const void* buf, size_t n)       { return m_fp ? std::fwrite(buf, 1, n, m_fp) : 0; }
    bool   Flush()                                 { return m_fp ? std::fflush(m_fp) == 0 : false; }
    long   Length() const {
        if (!m_fp) return 0;
        long cur = std::ftell(m_fp);
        std::fseek(m_fp, 0, SEEK_END);
        long len = std::ftell(m_fp);
        std::fseek(m_fp, cur, SEEK_SET);
        return len;
    }
    long   Seek(long off, int m = wxFromStart) {
        if (!m_fp) return -1;
        int w = (m == wxFromCurrent) ? SEEK_CUR : (m == wxFromEnd) ? SEEK_END : SEEK_SET;
        return std::fseek(m_fp, off, w) == 0 ? std::ftell(m_fp) : -1;
    }
    bool Eof() const { return m_fp && std::feof(m_fp); }
    static bool Exists(const wxString& p) {
        struct stat st;
        return ::stat(p.c_str(), &st) == 0;
    }
    static bool Access(const wxString&, int) { return true; }
};
