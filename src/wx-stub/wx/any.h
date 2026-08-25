// Minimal wx/any.h stub — wxAny with the extras KiCad's property system
// depends on (CheckType/RawAs/GetAs).
#pragma once
#include <any>
#include <typeinfo>
#include <utility>

class wxAny {
    std::any m_val;
public:
    wxAny() = default;
    template<typename T>
    wxAny(T&& v) : m_val(std::forward<T>(v)) {}

    template<typename T>
    wxAny& operator=(T&& v) { m_val = std::forward<T>(v); return *this; }

    // Real wxAny::CheckType<T>() — is the stored value of type T?
    template<typename T>
    bool CheckType() const {
        if (!m_val.has_value()) return false;
        return m_val.type() == typeid(T);
    }

    // Real wxAny::RawAs<T>() — extract without conversion; UB if wrong type.
    template<typename T>
    T RawAs() const {
        return std::any_cast<T>(m_val);
    }

    // Real wxAny::As<T>() — same as RawAs for our purposes.
    template<typename T>
    T As() const { return std::any_cast<T>(m_val); }

    // Real wxAny::GetAs<T>(T* out) — safe extract; false if wrong type.
    template<typename T>
    bool GetAs(T* out) const {
        try {
            if (out) *out = std::any_cast<T>(m_val);
            return true;
        } catch (const std::bad_any_cast&) {
            return false;
        }
    }

    bool IsNull() const { return !m_val.has_value(); }

    const std::type_info& GetType() const {
        return m_val.has_value() ? m_val.type() : typeid(void);
    }
};

using wxAnyValueBuffer = void*;

// Real wxWidgets: wxAnyValueType is a full class hierarchy. For KiCad's
// property-macro chain we need CheckType<T>() on it.
class wxAnyValueType {
public:
    virtual ~wxAnyValueType() = default;
    template<typename T>
    bool CheckType() const {
        // Type identity is checked via typeid comparison in derived classes;
        // this base returns false so KiCad's cascade of "else if" branches
        // safely falls to the default handler.
        return false;
    }
};

// wxWidgets internal — KiCad's DECLARE_ENUM_TO_WXANY macro specialises
// wxAnyValueTypeImpl<Enum> to inherit from wxAnyValueTypeImplBase<int>.
template<typename T>
class wxAnyValueTypeImplBase : public wxAnyValueType {
public:
    virtual ~wxAnyValueTypeImplBase() = default;
    virtual bool ConvertValue(const wxAnyValueBuffer&, wxAnyValueType*, wxAnyValueBuffer&) const override { return false; }
    static bool IsSameClass(const wxAnyValueType&) { return false; }
    static wxAnyValueType* GetInstance() { static wxAnyValueTypeImplBase<T> inst; return &inst; }
    static T    GetValue(const wxAnyValueBuffer&) { return T{}; }
    static void SetValue(const T&, wxAnyValueBuffer&) {}
    // Some KiCad code uses these two-arg forms with wxAny too.
    static bool GetValue(const wxAny&, T&) { return false; }
    static void SetValue(const T&, wxAny&) {}
};

template<typename T>
class wxAnyValueTypeImpl : public wxAnyValueTypeImplBase<T> {};

// Real wxWidgets provides these macros; KiCad's property.h uses them.
#define wxANY_AS(any, T)  ((any).As<T>())
#define WX_DECLARE_ANY_VALUE_TYPE(cls)  /* real wx: adds boilerplate methods */
#define WX_IMPLEMENT_ANY_VALUE_TYPE(cls) /* real wx: emits static instance */
