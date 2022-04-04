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
#include <memory>    // for allocators
using namespace std;

/**
 * @brief A container that allows constant time access to any element in the 
 *        container. Dynamically resizes as needed so the user does not need
 *        to worry about allocation.
 * 
 * @tparam T type of element.
 * @tparam Alloc type of allocator, default is std::allocator<T> 
 */
template <typename T, typename Alloc = std::allocator<T>>
class Xvector
{
private:
    Alloc alloc;                // Allocator for array
    T *data{nullptr};           // Pointer to array
    size_t xvector_size{0};     // Number of elements in array
    size_t xvector_capacity{0}; // Number of elements array can hold before resizing.

    /**
     * @brief Destroys each element in the array.
     * 
     * @param _data Pointer to array.
     * @param _capacity Size of the array.
     */
    void destroy_elems(T *_data, size_t _capacity) const;

public:
    using iterator = T *;
    using const_iterator = T const *;
    using allocator_type = Alloc;

    /**
     * @brief Construct a new Xvector object.
     * 
     */
    Xvector();

    /**
     * @brief Destroy the Xvector object.
     * 
     */
    ~Xvector();

    /**
     * @brief Get the allocator object.
     * 
     * @return allocator_type 
     */
    allocator_type get_allocator() const;

    /**
     * @brief Tests if the vector is empty.
     * 
     * @return true if empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Returns an iterator to the first element in the vector.
     * 
     * @return iterator 
     */
    iterator begin();

    /**
     * @brief Returns a constant iterator to the first element in the vector.
     * 
     * @return const_iterator 
     */
    const_iterator begin() const;

    /**
     * @brief Returns an iterator to the element one past the last element in 
     *        the vector.
     * 
     * @return iterator 
     */
    iterator end();

    /**
     * @brief Returns a constant iterator to the element one past the last 
     *        element in the vector.
     * 
     * @return const_iterator 
     */
    const_iterator end() const;

    /**
     * @brief Returns the current number of elements in the vector.
     * 
     * @return size_t 
     */
    size_t size() const;

    /**
     * @brief Returns the maximum number of elements that can be stored in the 
     *        vector before it must be resized.
     * 
     * @return size_t 
     */
    size_t capacity() const;

    /**
     * @brief Inserts an element at the end of the vector.
     * 
     * @param x The value to be inserted.
     */
    void push_back(T &&x);

    /**
     * @brief Inserts an element at the end of the vector.
     * 
     * @param x  The element to be inserted.
     */
    void push_back(const T &x);

    /**
     * @brief Decreases the size of the vector by 1.
     * 
     */
    void pop_back();

    /**
     * @brief Erases all elements in the vector.
     * 
     */
    void clear();

    /**
     * @brief Erases an element at a given position
     *  !!! NEEDS REWORKING & ITERATOR FUNCTIONALITY !!!
     * 
     * @param pos 
     */
    void erase(size_t pos);

    /**
     * @brief Resizes the vector. Inserts default values if vector increases 
     *        in size.
     * 
     * @param new_size New size of the vector.
     */
    void resize(size_t new_size);

    /**
     * @brief Resizes the vector.
     * 
     * @param new_size New size of the vector. Inserts the value specified if 
     *        vector increases in size.
     * @param x Value to be inserted.
     */
    void resize(size_t new_size, const T &x);

    /**
     * @brief Subscript access to an element in a vector, similar to C-style
     *        arrays.
     * 
     * @param pos Index of the element to be accessed.
     * @return T& 
     */
    T &operator[](size_t pos);

    /**
     * @brief Subscript access to an element in a vector, similar to C-style
     *        arrays.
     * 
     * @param pos Index of the element to be accessed.
     * @return T& 
     */
    const T &operator[](size_t pos) const;

    /**
     * @brief Returns a reference to a specified element in the vector. Throws
     *        std::out_of_range if index is not within the range of the vector.
     * 
     * @param pos Index of element to be accessed.
     * @return T& 
     */
    T &at(size_t pos);

    /**
     * @brief Returns a reference to a specified element in the vector. Throws
     *        std::out_of_range if index is not within the range of the vector.
     * 
     * @param pos Index of element to be accessed.
     * @return T& 
     */
    const T &at(size_t pos) const;
};

template <typename T, typename Alloc>
inline void Xvector<T, Alloc>::destroy_elems(T *_data, size_t _capacity) const
{
    for (size_t i = 0; i < _capacity; i++)
        _data[i].~T();
}

template <typename T, typename Alloc>
inline typename Xvector<T, Alloc>::allocator_type Xvector<T, Alloc>::get_allocator() const { return alloc; }

template <typename T, typename Alloc>
inline Xvector<T, Alloc>::Xvector() {}

template <typename T, typename Alloc>
inline Xvector<T, Alloc>::~Xvector()
{
    if (data) // If allocated, destroy objects and deallocate
    {
        destroy_elems(data, xvector_capacity);
        alloc.deallocate(data, xvector_capacity);
    }
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

        destroy_elems(old_data, xvector_size);
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

        destroy_elems(old_data, xvector_size);
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
    destroy_elems(data,xvector_capacity);
    alloc.deallocate(data,xvector_capacity);
    data = nullptr;
    xvector_size = xvector_capacity = 0;
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

            destroy_elems(old_data, xvector_size);
            alloc.deallocate(old_data, xvector_size);
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
            
            destroy_elems(old_data, xvector_size);
            alloc.deallocate(old_data, xvector_size);
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