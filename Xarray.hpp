#include <cstddef>   // for size_t
#include <stdexcept> // for basic exceptions
using namespace std;

template <typename T, size_t sz>
class Xarray
{
public:
    T arr[sz];
    size_t array_size{sz};

public:
    using iterator = T *;
    using const_iterator = const T *;

    constexpr Xarray() {}

    constexpr bool empty() const { return !array_size; }

    constexpr size_t size() const { return array_size; }

    constexpr T &front(){return arr[0];}
    constexpr const T &front()const {return arr[0];}

    constexpr T &back(){return arr[array_size-1];}
    constexpr const T &back()const {return arr[array_size-1];}

    constexpr iterator begin() { return arr; }
    constexpr const_iterator begin() const { return arr; }
    constexpr const_iterator cbegin() const { return arr; }

    constexpr iterator end() { return arr + array_size; }
    constexpr const_iterator end() const { return arr + array_size; }
    constexpr const_iterator cend() const { return arr + array_size; }

    constexpr T &operator[](size_t pos) { return arr[pos]; }
    constexpr const T &operator[](size_t pos) const { return arr[pos]; }
};
