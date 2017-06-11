#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <initializer_list> // initializer_list
#include <memory> // unique_ptr
#include <iterator>

#include "vec_iterator.h"

namespace mystl {

//template <typename T, typename Allocator>
//struct VectorBase {
//	using allocator_type = Allocator;
//	using size_type = size_t;
//	using difference_type = ptrdiff_t;
//
//	static const size_type npos = -1; // npos means non-valid position or simply non-position
//	static const size_type maxsize = -2; // maxsize < npos
//public:
//	VectorBase();
//	VectorBase(const allocator_type& alloc_);
//	VectorBase(size_type n, const allocator_type& alloc_);
//	~VectorBase();
//protected:
//	T* start;
//	T* finish;
//protected:
//	T* doAllocate(size_type n);
//	void doFree();
//	void doReallocate();
//	void checkAndAlloc();
//};

const size_t VEC_MIN_SIZE = 4;

template <typename T, typename Allocator = std::allocator<T>>
class Vector : private Allocator {
public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = typename std::allocator_traits<Allocator>::pointer; // since C++11
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer; // since C++11
	using iterator = VecIterator<T>; // RandomAccessIterator
	using const_iterator = VecIterator<const T>; // const RandomAccessIterator
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
protected:
	typename Allocator::pointer elements;
	typename Allocator::pointer first_free;
	typename Allocator::pointer end_of_storage;
//	pointer elements;
//	pointer first_free;
//	pointer end_of_storage;
public:
	explicit Vector(const Allocator& alloc_ = Allocator()) noexcept;
	Vector(size_type count, const T& value, const Allocator& alloc_ = Allocator());
	explicit Vector(size_t count, const Allocator& alloc_);

//	template <typename InputIt>
//	Vector(InputIt first, InputIt last, const Allocator& alloc_ = Allocator());

	Vector(const Vector<T>& rhs);
	Vector(const Vector<T>& rhs, const Allocator& alloc_);
	Vector(Vector<T>&& rhs) noexcept;
	Vector(std::initializer_list<T> init, const Allocator& alloc_ = Allocator());
	~Vector();
	
	Vector& operator=(const Vector& rhs);
	Vector& operator=(Vector&& other);
	Vector& operator=(std::initializer_list<T> ilist);
	
	void assign(size_type count, const T& value);
	
	template <typename InputIt>
	void assign(InputIt first, InputIt last);
	
	void assign(std::initializer_list<T> ilist);
	
	allocator_type get_allocator() const
	{
		return static_cast<const Allocator&>(*this);
	}
	
	reference at(size_type pos);
	const_reference at(size_type pos) const;
	
	reference operator[](size_type pos);
	const_reference operator[](size_type pos) const;
	
	reference front();
	const_reference front() const;
	
	reference back();
	const_reference back() const;
	
	pointer data() noexcept;
	const_pointer data() const noexcept;
	
	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;
	
	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;

	reverse_iterator rbegin() noexcept;
	const_reverse_iterator rbegin() const noexcept;
	const_reverse_iterator crbegin() const noexcept;
	
	reverse_iterator rend() noexcept;
	const_reverse_iterator rend() const noexcept;
	const_reverse_iterator crend() const noexcept;
	
	bool empty() const noexcept;
	size_type size() const noexcept;
	size_type max_size() const noexcept;
	size_type capacity() const noexcept;

	void reserve(size_type new_cap);
	void shrink_to_fit();
	void clear() noexcept;
	
	void push_back(const T& value);
	void push_back(T&& value);

	template <typename... Args>
	void emplace_back(Args&&...args);
	
	void pop_back();
	void resize(size_type count);
	void resize(size_type count, const value_type& value);
	
	void swap(Vector& rhs);
};

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Allocator& alloc_) noexcept:
	elements(nullptr), first_free(nullptr), end_of_storage(nullptr)
{
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_type count, const T& value, const Allocator& alloc_):
	Allocator(alloc_), elements(0)
{
	if (count != 0) {
		elements = Allocator::allocate(count);
		size_type i = 0;
		try {
			for ( ; i < count; ++i)
				Allocator::construct(elements+i, value);
			first_free = elements + count;
			end_of_storage = elements + count;
		} catch (...) {
			for (size_type j = 0; j < i; ++j) 
				Allocator::destroy(elements+j);
			Allocator::deallocate(elements, count);
			throw;
		}
	}
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t count, const Allocator& alloc_):
	Vector(count, T(), alloc_)
{
}

//template <typename T, typename Allocator>
//template <typename InputIt>
//Vector<T, Allocator>::Vector(InputIt first, InputIt last, const Allocator& alloc_)
//{
//}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector<T>& rhs)
{
	
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector<T>& rhs, const Allocator& alloc_)
{
	
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector<T>&& rhs) noexcept
{
	
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> init, const Allocator& alloc_)
{
	
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector()
{
	if (elements != first_free) {
		for (auto i = elements; i < first_free; ++i)
			Allocator::destroy(i);
		
		Allocator::deallocate(elements, end_of_storage-elements);
	}
	elements = first_free = end_of_storage = nullptr;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::begin() noexcept
{
	return elements;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::begin() const noexcept
{
	return elements;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::cbegin() const noexcept
{
	return elements;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::end() noexcept
{
	return first_free;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::end() const noexcept
{
	return first_free;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::cend() const noexcept
{
	return first_free;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::rbegin() noexcept
{
	return reverse_iterator(first_free);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::rbegin() const noexcept
{
	return const_reverse_iterator(first_free);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::crbegin() const noexcept
{
	return const_reverse_iterator(first_free);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::rend() noexcept
{
	return reverse_iterator(elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::rend() const noexcept
{
	return const_reverse_iterator(elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::crend() const noexcept
{
	return const_reverse_iterator(elements);
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const noexcept
{
	return elements == first_free;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::size() const noexcept
{
	return static_cast<size_type>(first_free - elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::max_size() const noexcept
{
	return 0xffffffffUL / sizeof(T);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::capacity() const noexcept
{
	return static_cast<size_type>(end_of_storage - elements);
}





template <typename T, typename Alloc>
void swap(Vector<T, Alloc>& lhs, Vector<T, Alloc>& rhs)
{
	lhs.swap(rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
	return out;
}

template <typename T, typename Alloc>
bool operator==(const Vector<T,Alloc>& lhs,
                const Vector<T,Alloc>& rhs)
{
	
}

template <typename T, typename Alloc>
bool operator!=(const Vector<T,Alloc>& lhs,
                const Vector<T,Alloc>& rhs)
{
	
}

template <typename T, typename Alloc>
bool operator<(const Vector<T,Alloc>& lhs,
               const Vector<T,Alloc>& rhs)
{
	
}

template <typename T, typename Alloc>
bool operator<=(const Vector<T,Alloc>& lhs,
                const Vector<T,Alloc>& rhs)
{
	
}

template <typename T, typename Alloc>
bool operator>(const Vector<T,Alloc>& lhs,
               const Vector<T,Alloc>& rhs)
{
	
}

template <typename T, typename Alloc>
bool operator>=(const Vector<T,Alloc>& lhs,
                const Vector<T,Alloc>& rhs)
{
	
}
}
#endif
