#include <type_traits>

namespace stlr
{
    template<typename T>
    class UniquePtr
    {
    public:
        constexpr UniquePtr() noexcept : m_ptr{nullptr} {}
        constexpr explicit UniquePtr(T* ptr) : m_ptr{ptr} {}

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        UniquePtr(UniquePtr&& other) : m_ptr(other.m_ptr)
        {
            other.m_ptr = nullptr;
        }

        UniquePtr& operator=(UniquePtr&& other)
        {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
            return *this;
        }

        ~UniquePtr()
        {
            delete m_ptr;
        }

        void reset(T* ptr = nullptr) 
        {
            delete m_ptr;
            m_ptr = ptr;
        }

        T* release()
        {
            T* temp = m_ptr;
            m_ptr = nullptr;
            return temp;
        }

        void swap(UniquePtr& other) 
        {
            std::swap(m_ptr, other.m_ptr);
        }

        T* get() const { return m_ptr; }

        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }

        explicit operator bool() { return m_ptr != nullptr; }

    private:
        T* m_ptr;
    };

    template<typename T>
    class UniquePtr<T[]>
    {
    public:
        constexpr UniquePtr() noexcept : m_ptr{nullptr} {}
        constexpr explicit UniquePtr(T* ptr) : m_ptr{ptr} {}

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        UniquePtr(UniquePtr&& other) : m_ptr(other.m_ptr)
        {
            other.m_ptr = nullptr;
        }

        UniquePtr& operator=(UniquePtr&& other)
        {
            delete[] m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
            return *this;
        }

        ~UniquePtr()
        {
            delete[] m_ptr;
        }

        void reset(T* ptr = nullptr)
        {
            delete[] m_ptr;
            m_ptr = ptr;
        }

        T* release()
        {
            T* temp = m_ptr;
            m_ptr = nullptr;
            return temp;
        }

        void swap(UniquePtr& other)
        {
            std::swap(m_ptr, other.m_ptr);
        }

        T* get() const { return m_ptr; }

        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }

        explicit operator bool() { return m_ptr != nullptr; }

        T& operator[](size_t i) { return m_ptr[i]; }
        const T& operator[](size_t i) const { return m_ptr[i]; }

    private:
        T* m_ptr;
    };
}