#include <initializer_list>
#include <cassert>
#include "Iterators.hpp"

namespace stlr {

	template<typename T, size_t Size>
	class Array
	{
	public:
		class ConstIterator
		{
		public:
			using ValueType = T;

			constexpr ConstIterator() : m_ptr{ nullptr } {}
			constexpr ConstIterator(const ValueType* ptr) : m_ptr{ ptr } {}

			[[nodiscard]] constexpr const ValueType& operator*() const { return *m_ptr; }
			[[nodiscard]] constexpr const ValueType* operator->() const { return m_ptr; }

			constexpr ConstIterator& operator++() { ++m_ptr; return *this; }
			constexpr ConstIterator& operator--() { --m_ptr; return *this; }
			[[nodiscard]] constexpr ConstIterator operator+(size_t n) const { return ConstIterator{ m_ptr + n }; }
			[[nodiscard]] constexpr ConstIterator operator-(size_t n) const { return ConstIterator{ m_ptr - n }; }

			[[nodiscard]] constexpr ptrdiff_t operator-(ConstIterator other) { return (m_ptr - other.m_ptr) / sizeof(ValueType); }

			[[nodiscard]] constexpr auto operator<=>(const ConstIterator& other) const = default;
			[[nodiscard]] constexpr bool operator==(const ConstIterator& other) const = default;

		private:
			const ValueType* m_ptr;
		};

		using Iterator = MutableIteratorType<ConstIterator>;
		using ReverseIterator = ReverseIteratorType<Iterator>;
		using ConstReverseIterator = ReverseIteratorType<ConstIterator>;

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

		[[nodiscard]] constexpr size_t size() const noexcept { return Size; }

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

		[[nodiscard]] constexpr Iterator begin() { return Iterator{ m_data }; }
		[[nodiscard]] constexpr Iterator end() { return Iterator{ m_data + Size }; }
		[[nodiscard]] constexpr ConstIterator cbegin() const { return ConstIterator{ m_data }; }
		[[nodiscard]] constexpr ConstIterator cend() const { return ConstIterator{ m_data + Size }; }
		[[nodiscard]] constexpr ReverseIterator rbegin() { return ReverseIterator{ end() }; }
		[[nodiscard]] constexpr ReverseIterator rend() { return ReverseIterator{ begin()}; }
		[[nodiscard]] constexpr ConstReverseIterator crbegin() const { return ConstReverseIterator{ cend() }; }
		[[nodiscard]] constexpr ConstReverseIterator crend() const { return ConstReverseIterator{ cbegin() }; }
		[[nodiscard]] constexpr ConstIterator begin() const { return cbegin(); }
		[[nodiscard]] constexpr ConstIterator end() const { return cend(); }
		[[nodiscard]] constexpr ConstReverseIterator rbegin() const { return crbegin(); }
		[[nodiscard]] constexpr ConstReverseIterator rend() const { return crend(); }

	private:
		T m_data[Size];
	};
}
