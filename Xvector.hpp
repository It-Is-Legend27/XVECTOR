/**
 * @file Xvector.hpp
 * @author Angel Badilo Hernandez (https://github.com/It-Is-Legend27)
 * @brief My own implementation of a vector. Serves the same purpose as a std::vector, it even has iterators.
 * @version 0.1
 * @date 2022-03-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstddef>   // for size_t
#include <stdexcept> // for basic exceptions
using namespace std;

template <typename T, typename Alloc = std::allocator<T>>
class Xvector
{
private:
    Alloc alloc;
    T *data{nullptr};           // Pointer to array
    size_t xvector_size{0};     // Number of elements in array
    size_t xvector_capacity{0}; // Number of elements array can hold before resizing.

public:
    using iterator = T *;
    using const_iterator = T const *;
    using allocator_type = Alloc;

    Xvector();

    ~Xvector();

    allocator_type get_allocator() const;

    bool empty() const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    size_t size() const;

    size_t capacity() const;

    void push_back(T &&x);
    void push_back(const T &x);

    void pop_back();

    void clear();

    void erase(size_t pos);

    void resize(size_t new_size);
    void resize(size_t new_size, const T &x);

    T &operator[](size_t pos);
    const T &operator[](size_t pos) const;

    T &at(size_t pos);
    const T &at(size_t pos) const;
};

/**
 * @brief 
 * 
 * @tparam T type of 
 * @tparam Alloc 
 * @return Xvector<T, Alloc>::allocator_type 
 */
template <typename T, typename Alloc>
inline typename Xvector<T, Alloc>::allocator_type Xvector<T, Alloc>::get_allocator() const { return alloc; }

template <typename T, typename Alloc>
inline Xvector<T, Alloc>::Xvector() {}

template <typename T, typename Alloc>
inline Xvector<T, Alloc>::~Xvector()
{
    if (data) // If allocated, deallocate
        alloc.deallocate(data, xvector_capacity);
}

template <typename T, typename Alloc>
inline bool Xvector<T, Alloc>::empty() const
{
    return !xvector_size;
}

template <typename T, typename Alloc>
inline typename Xvector<T, Alloc>::iterator Xvector<T, Alloc>::begin()
{
    return data;
}

template <typename T, typename Alloc>
inline typename Xvector<T, Alloc>::const_iterator Xvector<T, Alloc>::begin() const
{
    return data;
}

template <typename T, typename Alloc>
inline typename Xvector<T, Alloc>::iterator Xvector<T, Alloc>::end()
{
    return data + xvector_size;
}

template <typename T, typename Alloc>
inline typename Xvector<T, Alloc>::const_iterator Xvector<T, Alloc>::end() const
{
    return data + xvector_size;
}

template <typename T, typename Alloc>
inline size_t Xvector<T, Alloc>::size() const { return xvector_size; }

template <typename T, typename Alloc>
inline size_t Xvector<T, Alloc>::capacity() const { return xvector_capacity; }

template <typename T, typename Alloc>
inline void Xvector<T, Alloc>::push_back(T &&x) // r-values
{
    if (empty())
    {
        data = alloc.allocate(1);
        xvector_size++;     // Increment these
        xvector_capacity++; // Increment these
    }
    else if (xvector_size == xvector_capacity)
    {
        xvector_capacity *= 2;                   // New capacity is double the previous
        T *old_data = data;                      // Preserve old array for copy
        data = alloc.allocate(xvector_capacity); // Allocate larger array

        // copy values over
        for (size_t i = 0; i < xvector_size; i++)
        {
            data[i] = old_data[i];
        }

        alloc.deallocate(old_data, xvector_size); // Delete old array
        data[xvector_size] = x;                   // Insert value one element past the rear
        xvector_size++;                           // Increment size
    }
    else
    {
        data[xvector_size] = x; // Insert value one element past the rear
        xvector_size++;         // Increment size
    }
}

template <typename T, typename Alloc>
inline void Xvector<T, Alloc>::push_back(const T &x)
{
    if (empty())
    {
        data = alloc.allocate(1);
        data[xvector_size] = x;
        xvector_size++;     // Increment these
        xvector_capacity++; // Increment these
    }
    else if (xvector_size == xvector_capacity)
    {
        xvector_capacity *= 2;                   // New capacity is double the previous
        T *old_data = data;                      // Preserve old array for copy
        data = alloc.allocate(xvector_capacity); // Allocate larger array

        // copy values over
        for (size_t i = 0; i < xvector_size; i++)
        {
            data[i] = old_data[i];
        }

        alloc.deallocate(old_data, xvector_size); // Delete old array
        data[xvector_size] = x;                   // Insert value one element past the rear
        xvector_size++;                           // Increment size
    }
    else
    {
        data[xvector_size] = x; // Insert value one element past the rear
        xvector_size++;         // Increment size
    }
}

template <typename T, typename Alloc>
inline void Xvector<T, Alloc>::pop_back()
{
    if (!empty() && data)
        xvector_size--; // Reduce size by one
}

template <typename T, typename Alloc>
void Xvector<T, Alloc>::clear()
{
    xvector_size = 0; // Does not affect capacity, just affects size
}

template <typename T, typename Alloc>
void Xvector<T, Alloc>::erase(size_t pos)
{
    if (!empty() && (pos > xvector_size))
    {
        T *old_data = data;
        data = alloc.allocate(xvector_capacity);
        for (size_t i = 0; i < xvector_size; i++)
        {
            if (i != pos)
                data[i] = old_data[i];
        }
    }
}

template <typename T, typename Alloc>
void Xvector<T, Alloc>::resize(size_t new_size)
{
    if (!data) // not allocated
    {
        data = alloc.allocate(new_size);
        xvector_size = new_size;
        xvector_capacity = new_size;
        for (size_t i = 0; i < xvector_size; i++)
        {
            data[i] = T();
        }
    }
    else if (new_size == xvector_size) // equal size
    {
        return;
    }
    else if (new_size < xvector_size) // smaller size
    {
        xvector_size = new_size;
    }
    else // larger size
    {
        if (new_size <= xvector_capacity) // smaller than capacity
        {
            for (size_t i = xvector_size; i < new_size; i++)
            {
                data[i] = T();
            }
            xvector_size = new_size;
        }
        else
        {
            T *old_data = data;              // preserve old array
            data = alloc.allocate(new_size); // allocate larger array
            for (size_t i = 0; i < xvector_size; i++)
            {
                data[i] = old_data[i];
            }
            alloc.deallocate(old_data,xvector_size);
            for (size_t i = xvector_size; i < new_size; i++)
            {
                data[i] = T();
            }
            xvector_size = new_size;
            xvector_capacity = new_size;
        }
    }
}

template <typename T, typename Alloc>
void Xvector<T, Alloc>::resize(size_t new_size, const T &x)
{
    if (!data) // not allocated
    {
        data = alloc.allocate(new_size);
        xvector_size = new_size;
        xvector_capacity = new_size;
        for (size_t i = 0; i < xvector_size; i++)
        {
            data[i] = x;
        }
    }
    else if (new_size == xvector_size) // equal size
    {
        return;
    }
    else if (new_size < xvector_size) // smaller size
    {
        xvector_size = new_size;
    }
    else // larger size
    {
        if (new_size <= xvector_capacity) // smaller than capacity
        {
            for (size_t i = xvector_size; i < new_size; i++)
            {
                data[i] = x;
            }
            xvector_size = new_size;
        }
        else
        {
            T *old_data = data;              // preserve old array
            data = alloc.allocate(new_size); // allocate larger array
            for (size_t i = 0; i < xvector_size; i++)
            {
                data[i] = old_data[i];
            }
            alloc.deallocate(old_data,xvector_size);
            for (size_t i = xvector_size; i < new_size; i++)
            {
                data[i] = x;
            }
            xvector_size = new_size;
            xvector_capacity = new_size;
        }
    }
}

template <typename T, typename Alloc>
T &Xvector<T, Alloc>::operator[](size_t pos)
{
    return data[pos];
}

template <typename T, typename Alloc>
const T &Xvector<T, Alloc>::operator[](size_t pos) const
{
    return data[pos];
}

template <typename T, typename Alloc>
T &Xvector<T, Alloc>::at(size_t pos)
{
    if (pos > 0 || pos <= xvector_size)
        std::__throw_out_of_range("Out of bounds.");

    return data[pos];
}

template <typename T, typename Alloc>
const T &Xvector<T, Alloc>::at(size_t pos) const
{
    if (pos > 0 || pos <= xvector_size)
        std::__throw_out_of_range("Out of bounds.");

    return data[pos];
}