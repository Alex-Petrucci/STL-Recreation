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

			constexpr const ValueType& operator*() const { return *m_ptr; }
			constexpr const ValueType* operator->() const { return m_ptr; }

			constexpr ConstIterator& operator++() { ++m_ptr; return *this; }
			constexpr ConstIterator& operator--() { --m_ptr; return *this; }
			constexpr ConstIterator operator+(size_t n) const { return ConstIterator{ m_ptr + n }; }
			constexpr ConstIterator operator-(size_t n) const { return ConstIterator{ m_ptr - n }; }

			constexpr ptrdiff_t operator-(ConstIterator other) { return (m_ptr - other.m_ptr) / sizeof(ValueType); }

			constexpr auto operator<=>(const ConstIterator& other) const = default;
			constexpr bool operator==(const ConstIterator& other) const = default;

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

		constexpr size_t size() const noexcept { return Size; }

		constexpr  T& operator[](size_t index) noexcept
		{
			return m_data[index];
		}

		constexpr const T& operator[](size_t index) const noexcept
		{
			return m_data[index];
		}

		constexpr T& at(size_t index)
		{
			if (index >= Size)
				throw std::runtime_error("Index out of bounds.");

			return m_data[index];
		}

		constexpr const T& at(size_t index) const
		{
			if (index >= Size)
				throw std::runtime_error("Index out of bounds.");

			return m_data[index];
		}

		constexpr Iterator begin() { return Iterator{ m_data }; }
		constexpr Iterator end() { return Iterator{ m_data + Size }; }
		constexpr ConstIterator cbegin() const { return ConstIterator{ m_data }; }
		constexpr ConstIterator cend() const { return ConstIterator{ m_data + Size }; }
		constexpr ReverseIterator rbegin() { return ReverseIterator{ end() }; }
		constexpr ReverseIterator rend() { return ReverseIterator{ begin()}; }
		constexpr ConstReverseIterator crbegin() const { return ConstReverseIterator{ cend() }; }
		constexpr ConstReverseIterator crend() const { return ConstReverseIterator{ cbegin() }; }
		constexpr ConstIterator begin() const { return cbegin(); }
		constexpr ConstIterator end() const { return cend(); }
		constexpr ConstReverseIterator rbegin() const { return crbegin(); }
		constexpr ConstReverseIterator rend() const { return crend(); }

	private:
		T m_data[Size];
	};
}