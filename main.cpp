#include "Xvector.hpp"
#include <iostream>
using namespace std;

int main()
{
    Xvector<string> V;
    V.resize(2,"Jojo");
    //V.resize(4);
    for (auto &&i : V)
    {
        cout << i << ' ';
    }
    
    // ERROR WITH RESIZE!!!
    
}