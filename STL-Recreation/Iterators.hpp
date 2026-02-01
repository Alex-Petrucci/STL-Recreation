namespace stlr
{
	template<typename Iterator>
	class MutableIteratorType : public Iterator
	{
	public:
		using ValueType = Iterator::ValueType;

		using Iterator::Iterator; // inherit constructor

		constexpr ValueType& operator*() const { return const_cast<ValueType&>(Iterator::operator*()); }
		constexpr ValueType* operator->() const { return const_cast<ValueType*>(Iterator::operator->()); }
	};

	template<typename Iterator>
	class ReverseIteratorType : public Iterator
	{
	public:
		using ValueType = Iterator::ValueType;

		constexpr ReverseIteratorType(Iterator iterator) : m_iterator{ iterator } {}

		constexpr auto operator*() const
		{
			Iterator copy = m_iterator;
			--copy;
			return *copy;
		}

		constexpr auto operator->() const
		{
			Iterator copy = m_iterator;
			--copy;
			return copy.operator->();
		}

		constexpr auto operator<=>(ReverseIteratorType other) const
		{
			return m_iterator <=> other.m_iterator;
		}

		constexpr bool operator==(ReverseIteratorType other) const
		{
			return m_iterator == other.m_iterator;
		}

		constexpr ReverseIteratorType& operator++() { --m_iterator; return *this; }
		constexpr ReverseIteratorType& operator--() { ++m_iterator; return *this; }
		constexpr ReverseIteratorType operator+(size_t n) { return ReverseIteratorType{ m_iterator - n }; }
		constexpr ReverseIteratorType operator-(size_t n) { return ReverseIteratorType{ m_iterator - n }; }

		constexpr ptrdiff_t operator-(ReverseIteratorType other) { return other - *this; }

		constexpr Iterator base() const { return m_iterator; }

	private:
		Iterator m_iterator;
	};
}