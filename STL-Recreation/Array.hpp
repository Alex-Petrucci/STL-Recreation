#include <initializer_list>
#include <cassert>
#include "Iterators.hpp"

namespace stlr {

    template<typename T, size_t Size>
    class Array
    {
    public:
        template<typename ValueType>
        class BaseIterator
        {
        public:
            // typedefs below required for stl compatability
            using iterator_category = std::random_access_iterator_tag;
            using value_type = ValueType;
            using difference_type = ptrdiff_t;
            using reference = ValueType&;
            using pointer = ValueType*;

            constexpr BaseIterator() : m_ptr{nullptr} {}
            constexpr BaseIterator(pointer ptr) : m_ptr{ptr} {}

            [[nodiscard]] constexpr reference operator*() const
            {
                return *m_ptr;
            }

            [[nodiscard]] constexpr pointer operator->() const
            {
                return m_ptr;
            }

            constexpr BaseIterator& operator++()
            {
                ++m_ptr; return *this;
            }

            constexpr BaseIterator& operator--()
            {
                --m_ptr; return *this;
            }

            constexpr BaseIterator operator++(int)
            {
                BaseIterator copy = *this;
                ++(*this);
                return copy;
            }

            constexpr BaseIterator operator--(int)
            {
                BaseIterator copy = *this;
                --(*this);
                return copy;
            }

            [[nodiscard]] constexpr BaseIterator operator+(difference_type n) const
            {
                return BaseIterator{m_ptr + n};
            }

            [[nodiscard]] constexpr BaseIterator operator-(difference_type n) const
            {
                return BaseIterator{m_ptr - n};
            }

            constexpr BaseIterator& operator+=(difference_type n)
            {
                m_ptr += n; return *this;
            }

            constexpr BaseIterator& operator-=(difference_type n)
            {
                m_ptr -= n; return *this;
            }

            constexpr reference operator[](difference_type n) const
            {
                return m_ptr[n];
            }

            [[nodiscard]] constexpr difference_type operator-(const BaseIterator& other) const
            {
                return m_ptr - other.m_ptr;
            }

            [[nodiscard]] constexpr auto operator<=>(const BaseIterator& other) const = default;
            [[nodiscard]] constexpr bool operator==(const BaseIterator& other) const = default;

        private:
            pointer m_ptr;
        };

        using Iterator = BaseIterator<T>;
        using ConstIterator = BaseIterator<const T>;
        using ReverseIterator = stlr::ReverseIterator<Iterator>;
        using ConstReverseIterator = stlr::ReverseIterator<ConstIterator>;

        constexpr Array()
            : m_data{}
        {

        }

        constexpr Array(std::initializer_list<T> list)
            : m_data{}
        {
            assert(list.size() <= Size && "Initializer list too large.");

            size_t index = 0;
            for (const T& element : list)
            {
                m_data[index++] = element;
            }
        }

        [[nodiscard]] constexpr size_t size() const noexcept
        {
            return Size;
        }

        [[nodiscard]] constexpr  T& operator[](size_t index) noexcept
        {
            return m_data[index];
        }

        [[nodiscard]] constexpr const T& operator[](size_t index) const noexcept
        {
            return m_data[index];
        }

        [[nodiscard]] constexpr T& at(size_t index)
        {
            if (index >= Size)
                throw std::runtime_error("Index out of bounds.");

            return m_data[index];
        }

        [[nodiscard]] constexpr const T& at(size_t index) const
        {
            if (index >= Size)
                throw std::runtime_error("Index out of bounds.");

            return m_data[index];
        }

        [[nodiscard]] constexpr Iterator             begin()         { return Iterator{m_data}; }
        [[nodiscard]] constexpr Iterator             end()           { return Iterator{m_data + Size}; }
        [[nodiscard]] constexpr ConstIterator        cbegin()  const { return ConstIterator{m_data}; }
        [[nodiscard]] constexpr ConstIterator	     cend()    const { return ConstIterator{m_data + Size}; }
        [[nodiscard]] constexpr ReverseIterator      rbegin()        { return ReverseIterator{end()}; }
        [[nodiscard]] constexpr ReverseIterator      rend()          { return ReverseIterator{begin()}; }
        [[nodiscard]] constexpr ConstReverseIterator crbegin() const { return ConstReverseIterator{cend()}; }
        [[nodiscard]] constexpr ConstReverseIterator crend()   const { return ConstReverseIterator{cbegin()}; }
        [[nodiscard]] constexpr ConstIterator        begin()   const { return cbegin(); }
        [[nodiscard]] constexpr ConstIterator        end()     const { return cend(); }
        [[nodiscard]] constexpr ConstReverseIterator rbegin()  const { return crbegin(); }
        [[nodiscard]] constexpr ConstReverseIterator rend()    const { return crend(); }

    private:
        T m_data[Size];
    };
}
