#ifndef RAY_HPP_TPU3JSEO
#define RAY_HPP_TPU3JSEO

#include <string>

class Ray {
public:
    Vector3 origin;
    Vector3 direction;
    
    operator std::string(){
        return "Ray{"+(std::string)origin+","+(std::string)direction+"}";
    }
    
};

#endif /* end of include guard: RAY_HPP_TPU3JSEO */
