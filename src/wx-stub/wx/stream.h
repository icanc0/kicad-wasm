// Minimal wx/stream.h stub — enough for KiCad's richio wrapper.
// Real wxWidgets streams are the wxInputStream/wxOutputStream hierarchy;
// KiCad wraps them via richio.h into UTF8 read/write. In the WASM build
// we replace those with std::istream/std::ostream at the KiCad wrapper
// layer, so the stream base classes only need to exist type-wise.
#pragma once
#include "wx/defs.h"
#include "wx/string.h"
#include <cstddef>

using wxFileOffset = long long;

enum wxStreamError {
    wxSTREAM_NO_ERROR = 0,
    wxSTREAM_EOF,
    wxSTREAM_WRITE_ERROR,
    wxSTREAM_READ_ERROR,
};

enum wxSeekMode { wxFromStart = 0, wxFromCurrent = 1, wxFromEnd = 2 };

class wxStreamBase {
public:
    virtual ~wxStreamBase() = default;
    virtual bool IsOk() const { return m_ok; }
    wxStreamError GetLastError() const { return m_err; }
    virtual wxFileOffset GetLength() const { return 0; }
    virtual size_t GetSize() const { return 0; }
protected:
    bool m_ok = true;
    wxStreamError m_err = wxSTREAM_NO_ERROR;
};

class wxInputStream : public wxStreamBase {
public:
    virtual size_t Read(void* /*buffer*/, size_t /*size*/) { return 0; }
    virtual size_t LastRead() const { return m_lastRead; }
    virtual bool Eof() const { return true; }
    virtual char Peek() { return 0; }
    virtual wxFileOffset SeekI(wxFileOffset, wxSeekMode = wxFromStart) { return -1; }
    virtual wxFileOffset TellI() const { return -1; }
protected:
    size_t m_lastRead = 0;
};

class wxOutputStream : public wxStreamBase {
public:
    virtual size_t Write(const void* /*buffer*/, size_t /*size*/) { return 0; }
    virtual size_t LastWrite() const { return m_lastWrite; }
    virtual wxFileOffset SeekO(wxFileOffset, wxSeekMode = wxFromStart) { return -1; }
    virtual wxFileOffset TellO() const { return -1; }
    virtual bool Close() { return true; }
protected:
    size_t m_lastWrite = 0;
};

class wxStreamBuffer {
public:
    wxStreamBuffer() = default;
    virtual ~wxStreamBuffer() = default;
    size_t GetBufferSize() const { return 0; }
    void SetBufferIO(size_t) {}
};
