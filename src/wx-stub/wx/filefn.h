// Minimal wx/filefn.h stub — file system helpers KiCad uses.
#pragma once
#include "wx/string.h"
#include <filesystem>

// The most commonly used constants and functions from wxWidgets file
// helpers. All backed by std::filesystem, char-only.

inline bool wxFileExists(const wxString& p) {
    std::error_code ec;
    return std::filesystem::exists(p.ToStdString(), ec) &&
           std::filesystem::is_regular_file(p.ToStdString(), ec);
}
inline bool wxDirExists(const wxString& p) {
    std::error_code ec;
    return std::filesystem::exists(p.ToStdString(), ec) &&
           std::filesystem::is_directory(p.ToStdString(), ec);
}
inline bool wxRemoveFile(const wxString& p) {
    std::error_code ec;
    return std::filesystem::remove(p.ToStdString(), ec);
}
inline bool wxRenameFile(const wxString& src, const wxString& dst,
                         bool overwrite = true) {
    std::error_code ec;
    if (overwrite) std::filesystem::rename(src.ToStdString(), dst.ToStdString(), ec);
    else if (!std::filesystem::exists(dst.ToStdString(), ec))
        std::filesystem::rename(src.ToStdString(), dst.ToStdString(), ec);
    return !ec;
}
inline bool wxCopyFile(const wxString& src, const wxString& dst, bool = true) {
    std::error_code ec;
    return std::filesystem::copy_file(src.ToStdString(), dst.ToStdString(),
              std::filesystem::copy_options::overwrite_existing, ec);
}
inline bool wxMkdir(const wxString& p, int = 0755) {
    std::error_code ec;
    return std::filesystem::create_directories(p.ToStdString(), ec);
}
inline bool wxRmdir(const wxString& p, int = 0) {
    std::error_code ec;
    return std::filesystem::remove_all(p.ToStdString(), ec) > 0;
}
inline wxString wxGetCwd() {
    std::error_code ec;
    return wxString(std::filesystem::current_path(ec).string());
}
inline bool wxSetWorkingDirectory(const wxString& p) {
    std::error_code ec;
    std::filesystem::current_path(p.ToStdString(), ec);
    return !ec;
}
inline wxString wxPathOnly(const wxString& p) {
    return wxString(std::filesystem::path(p.ToStdString()).parent_path().string());
}
inline bool wxIsAbsolutePath(const wxString& p) {
    return std::filesystem::path(p.ToStdString()).is_absolute();
}

enum {
    wxFileExists_FILE = 1,
    wxFileExists_DIR  = 2,
    wxS_DIR_DEFAULT   = 0755,
};
