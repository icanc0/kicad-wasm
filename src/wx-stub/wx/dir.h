// Minimal wx/dir.h stub — directory traversal, backed by std::filesystem.
#pragma once
#include "wx/string.h"
#include <filesystem>
#include <string>

enum {
    wxDIR_FILES     = 0x0001,
    wxDIR_DIRS      = 0x0002,
    wxDIR_HIDDEN    = 0x0004,
    wxDIR_DOTDOT    = 0x0008,
    wxDIR_NO_FOLLOW = 0x0010,
    wxDIR_DEFAULT   = wxDIR_FILES | wxDIR_DIRS,
};

class wxDir {
    std::filesystem::path m_root;
    bool m_ok = false;
public:
    wxDir() = default;
    wxDir(const wxString& path) : m_root(path.ToStdString()) {
        std::error_code ec;
        m_ok = std::filesystem::is_directory(m_root, ec);
    }
    bool Open(const wxString& path) {
        m_root = path.ToStdString();
        std::error_code ec;
        m_ok = std::filesystem::is_directory(m_root, ec);
        return m_ok;
    }
    bool IsOpened() const { return m_ok; }

    // No-op traversal iface — real wx has GetFirst/GetNext but that's
    // used only in UI code paths. KiCad common uses HasSubDirs/Exists.
    static bool Exists(const wxString& p) {
        std::error_code ec;
        return std::filesystem::exists(p.ToStdString(), ec);
    }
    bool HasFiles(const wxString& = wxString()) const { return false; }
    bool HasSubDirs(const wxString& = wxString()) const { return false; }
};
