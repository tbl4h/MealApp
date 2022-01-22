#include <memory_resource>
#include <iostream>
#include <bitset>
#include <array>
#include <memory>

template <class T>
class allocator
{
public:
    using value_type = T;

    allocator() noexcept
    {
        std::cout << "m_data_pointer value: " << this->m_data_pointer << '\n';
        std::cout << "m_data_alignment_size value: " << this->m_alignment_size << '\n';
        m_data_pointer = const_cast<T*>(m_data);
        offset = 0;
    } // not required, unless used
    template <class U>
    allocator(allocator<U> const &) noexcept {}

    inline bool is_aligned(T *ptr, std::size_t alignment = alignof(T)) noexcept
    {
        auto iptr = reinterpret_cast<size_t>(ptr);
        return !(iptr % alignment);
    }

    value_type * // Use pointer if pointer is not a value_type*
    allocate(std::size_t size, std::size_t aligned = m_alignment_size)
    {
        // bool is_aligned_val = is_aligned(m_data_pointer);
        // if (is_aligned_val){
        //     T *result = reinterpret_cast<T *>(m_data_pointer);
        //     m_data_pointer = (T*)m_data_pointer + sizeof(T);
        //     return result;
        // }
        // Check to see if the backing memory has space left
	    if (offset + size <= m_data_length) {
		void *ptr = &m_data[offset];
		offset += size;
		// Zero new memory by default
		memset(ptr, 0, size);
		return ptr;
    }

    void
    deallocate(value_type *p, std::size_t) noexcept // Use pointer if pointer is not a value_type*
    {
        // m_data_pointer = m_data.begin();
    }

public:
    static constexpr T m_data[8]{0};
    static T *m_data_pointer;
    static constexpr std::size_t m_data_length{8};
    static constexpr std::size_t m_alignment_size{alignof(T)};
    std::size_t offset;
};

// template <class U>
// char* allocator<U>::m_data;
template <class U>
U* allocator<U>::m_data_pointer;
template<class U>
constexpr std::size_t allocator<U>::m_data_length;
template <class U>
constexpr std::size_t allocator<U>::m_alignment_size;

template <class T, class U>
bool operator==(allocator<T> const &, allocator<U> const &) noexcept
{
    return true;
}

template <class T, class U>
bool operator!=(allocator<T> const &x, allocator<U> const &y) noexcept
{
    return !(x == y);
}
