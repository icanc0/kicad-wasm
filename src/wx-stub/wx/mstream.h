// Minimal wx/mstream.h stub — in-memory streams.
#pragma once
#include "wx/stream.h"
#include <string>
#include <vector>

class wxMemoryOutputStream : public wxOutputStream {
    std::vector<char> m_buf;
public:
    wxMemoryOutputStream(void* buffer = nullptr, size_t = 0) { (void)buffer; }
    size_t Write(const void* buf, size_t n) override {
        const char* p = static_cast<const char*>(buf);
        m_buf.insert(m_buf.end(), p, p + n);
        return n;
    }
    size_t GetSize() const override { return m_buf.size(); }
    size_t CopyTo(void* dst, size_t n) const {
        size_t copy = n < m_buf.size() ? n : m_buf.size();
        std::memcpy(dst, m_buf.data(), copy);
        return copy;
    }
    const char* GetOutputStreamBuffer() const { return m_buf.data(); }
};

class wxMemoryInputStream : public wxInputStream {
    const char* m_data = nullptr;
    size_t      m_size = 0;
    size_t      m_pos  = 0;
public:
    wxMemoryInputStream(const void* data, size_t size) : m_data(static_cast<const char*>(data)), m_size(size) {}
    size_t Read(void* buf, size_t n) override {
        size_t avail = m_size - m_pos;
        size_t copy = n < avail ? n : avail;
        std::memcpy(buf, m_data + m_pos, copy);
        m_pos += copy;
        m_lastRead = copy;
        return copy;
    }
    bool Eof() const override { return m_pos >= m_size; }
    size_t GetSize() const override { return m_size; }
};
