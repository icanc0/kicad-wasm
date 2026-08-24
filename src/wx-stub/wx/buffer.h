// Minimal wx/buffer.h stub — memory buffers.
#pragma once
#include "wx/defs.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <memory>

class wxMemoryBuffer {
    std::unique_ptr<char[]> m_data;
    size_t m_size = 0;
    size_t m_len  = 0;
public:
    wxMemoryBuffer(size_t initial_size = 1024) { SetBufSize(initial_size); }

    void SetBufSize(size_t n) {
        auto nd = std::make_unique<char[]>(n ? n : 1);
        if (m_len && m_data) std::memcpy(nd.get(), m_data.get(), std::min(m_len, n));
        m_data = std::move(nd);
        m_size = n;
        if (m_len > n) m_len = n;
    }

    void*  GetData() const { return m_data.get(); }
    size_t GetBufSize() const { return m_size; }
    size_t GetDataLen() const { return m_len; }
    void   SetDataLen(size_t n) { m_len = n < m_size ? n : m_size; }

    void AppendByte(char c) {
        if (m_len + 1 > m_size) SetBufSize(m_size ? m_size * 2 : 32);
        m_data[m_len++] = c;
    }
    void AppendData(const void* data, size_t n) {
        while (m_len + n > m_size) SetBufSize(m_size ? m_size * 2 : (n + 32));
        std::memcpy(m_data.get() + m_len, data, n);
        m_len += n;
    }
    void Clear() { m_len = 0; }
};

template<typename Char>
class wxScopedCharTypeBuffer {
    std::unique_ptr<Char[]> m_data;
    size_t m_len = 0;
public:
    wxScopedCharTypeBuffer() = default;
    wxScopedCharTypeBuffer(const Char* s) {
        if (s) {
            m_len = std::char_traits<Char>::length(s);
            m_data = std::make_unique<Char[]>(m_len + 1);
            std::copy(s, s + m_len + 1, m_data.get());
        }
    }
    const Char* data() const { return m_data.get(); }
    size_t      length() const { return m_len; }
    operator const Char*() const { return m_data.get(); }
};

using wxScopedCharBuffer = wxScopedCharTypeBuffer<char>;
