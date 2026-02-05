#include <cstddef>
#include <utility>
#include <type_traits>

namespace stlr
{
    template<typename Iterator>
    class ReverseIterator
    {
    public:
        // typedefs below required for stl compatability
        using iterator_category = Iterator::iterator_category;
        using value_type = Iterator::value_type;
        using difference_type = Iterator::difference_type;
        // pointer and reference types required to be different in reverse iterators
        // as they represent dereferencing the base pointer positions one spot earlier
        using reference = decltype(*std::declval<Iterator>());
        using pointer = std::add_pointer_t<reference>;

        constexpr ReverseIterator(Iterator iterator) : m_iterator{iterator} {}

        [[nodiscard]] constexpr auto operator*() const
        {
            Iterator copy = m_iterator;
            --copy;
            return *copy;
        }

        [[nodiscard]] constexpr auto operator->() const
        {
            Iterator copy = m_iterator;
            --copy;
            return copy.operator->();
        }

        [[nodiscard]] constexpr auto operator<=>(ReverseIterator other) const
        {
            return other.m_iterator <=> m_iterator;
        }

        [[nodiscard]] constexpr bool operator==(ReverseIterator other) const
        {
            return m_iterator == other.m_iterator;
        }

        constexpr ReverseIterator& operator++()
        {
            --m_iterator;
            return *this;
        }

        constexpr ReverseIterator& operator--()
        {
            ++m_iterator;
            return *this;
        }

        constexpr ReverseIterator operator++(int)
        {
            ReverseIterator copy = *this;
            ++(*this);
            return copy;
        }

        constexpr ReverseIterator operator--(int)
        {
            ReverseIterator copy = *this;
            --(*this);
            return copy;
        }

        [[nodiscard]] constexpr ReverseIterator operator+(difference_type n) const
        {
            return ReverseIterator{m_iterator - n};
        }

        [[nodiscard]] constexpr ReverseIterator operator-(difference_type n) const
        {
            return ReverseIterator{m_iterator + n};
        }

        constexpr ReverseIterator& operator+=(difference_type n)
        {
            return *this = *this + n;
        }
        constexpr ReverseIterator& operator-=(difference_type n) {
            return *this = *this - n;
        }

        constexpr reference operator[](difference_type n) const {
            return *(*this + n);
        }

        [[nodiscard]] constexpr difference_type operator-(const ReverseIterator& other) const
        {
            return other.m_iterator - m_iterator;
        }

        [[nodiscard]] constexpr Iterator base() const
        {
            return m_iterator;
        }

    private:
        Iterator m_iterator;
    };
}
