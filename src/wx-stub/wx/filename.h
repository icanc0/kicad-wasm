// Minimal wx/filename.h stub — enough for headless KiCad code.
// Real wxFileName does path decomposition + fs queries; we implement
// just what the compiled KiCad WASM subset actually calls.
#pragma once
#include "wx/string.h"
#include "wx/filefn.h"     // real wxWidgets pulls this in transitively
#include <filesystem>

class wxFileName {
    std::filesystem::path m_path;
public:
    wxFileName() = default;
    wxFileName(const wxString& s) : m_path(s.ToStdString()) {}
    wxFileName(const wxString& dir, const wxString& name)
        : m_path((std::filesystem::path)dir.ToStdString() / name.ToStdString()) {}
    wxFileName(const wxString& dir, const wxString& name, const wxString& ext)
        : m_path((std::filesystem::path)dir.ToStdString() / (name.ToStdString() + "." + ext.ToStdString())) {}

    wxString GetFullPath() const   { return wxString(m_path.string()); }
    wxString GetPath()     const   { return wxString(m_path.parent_path().string()); }
    wxString GetFullName() const   { return wxString(m_path.filename().string()); }
    wxString GetName()     const   { return wxString(m_path.stem().string()); }
    wxString GetExt()      const   { return wxString(m_path.has_extension()
                                       ? m_path.extension().string().substr(1)
                                       : std::string()); }

    void SetPath(const wxString& p) {
        m_path = (std::filesystem::path)p.ToStdString() / m_path.filename();
    }
    void SetName(const wxString& n) {
        m_path.replace_filename(n.ToStdString());
        // keep extension separately if present — this matches wxFileName semantics.
    }
    void SetExt(const wxString& e) {
        m_path.replace_extension("." + e.ToStdString());
    }
    void AppendDir(const wxString& d) { m_path /= d.ToStdString(); }
    void RemoveLastDir()              { m_path = m_path.parent_path(); }

    bool FileExists() const {
        std::error_code ec;
        return std::filesystem::exists(m_path, ec) &&
               std::filesystem::is_regular_file(m_path, ec);
    }
    static bool FileExists(const wxString& p) {
        std::error_code ec;
        return std::filesystem::is_regular_file(p.ToStdString(), ec);
    }
    bool DirExists() const {
        std::error_code ec;
        return std::filesystem::exists(m_path, ec) &&
               std::filesystem::is_directory(m_path, ec);
    }
    static bool DirExists(const wxString& p) {
        std::error_code ec;
        return std::filesystem::is_directory(p.ToStdString(), ec);
    }
    bool Mkdir(int = 0777, int = 0) const {
        std::error_code ec;
        return std::filesystem::create_directories(m_path, ec);
    }

    size_t GetSize() const {
        std::error_code ec;
        return std::filesystem::file_size(m_path, ec);
    }

    bool IsAbsolute() const   { return m_path.is_absolute(); }
    bool IsOk() const         { return !m_path.empty(); }
    bool HasName() const      { return m_path.has_filename(); }
    bool HasExt() const       { return m_path.has_extension(); }

    static wxFileName FileName(const wxString& s) { return wxFileName(s); }
    static wxFileName DirName(const wxString& s)  { wxFileName f; f.SetPath(s); return f; }

    // Comparison / equality.
    bool operator==(const wxFileName& r) const { return m_path == r.m_path; }
    bool operator!=(const wxFileName& r) const { return m_path != r.m_path; }
};

// wxPATH_MKDIR_FULL etc.  (wxS_DIR_DEFAULT is defined in wx/filefn.h)
enum { wxPATH_MKDIR_FULL = 1 };
