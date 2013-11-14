#include <iostream>
#include "renderschuessel.hpp"

int main (int argc, char const *argv[])
{
    Sphere s = {{0,0,0},2};
    
    Buffer b(1024,1024);
    
    Intersection i;
    
    Ray r = {{0,0,10},{-1,0,0}};
    
    for(int x = -512; x < 512; x++){
        for(int y = -512; y < 512; y++){
            float _x = (10/1024.0)*x;
            float _y = (10/1024.0)*y;
            r.direction = (Vector3({_x,_y,0})-r.origin).norm();
            if(s.intersect(r,i)){
                b.pset(x+512,y+512, {255,255,255});
            }

        }
    }
    //std::cout << b.ppm() << std::endl;

    return 0;
}