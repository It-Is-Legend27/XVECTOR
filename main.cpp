#include <iostream>
#include "Xvector.hpp"
#include <vector>
using namespace std;

int main()
{
    Xvector<int> v;
    v.resize(100000000);
    for (auto &&i : v)
    {
        i = 1;
        cout << i << ' ';
    }
        
}