#include <iostream>
#include "renderschuessel.hpp"

int main (int argc, char const *argv[])
{
    Vector3 v = {0,1,2};
    std::cout << (std::string)v << " " << v.length() << std::endl;
    v.normalize();
    v = v+ Vector3({1,1,1});
    std::cout << (std::string)v << " " << v.length() << std::endl;
    return 0;
}