#ifndef SPHERE_HPP_3Y096I6
#define SPHERE_HPP_3Y096I6
#include "math.hpp"


class Sphere{ 
public:
    Vector3 origin;
    double radius;
    
    bool intersect(Ray const& ray, Intersection& intersection){
        Vector3 v = ray.origin - this->origin;
  
        double desc = pow ( ray.direction * v,2 ) - ((ray.direction * ray.direction)  * ( v * v - radius * radius ));
        
        if ( desc < 0 )  
                return false;
        desc = sqrt ( desc );
        Vector3 tmp = (ray.direction*(-1.0));
        double dista = ( tmp * v  + desc ) / (ray.direction * ray.direction);
        double distb = ( tmp * v  - desc ) / (ray.direction * ray.direction);

        double swapvar;
        if ( dista > distb )
        {
                swapvar = dista;
                dista = distb;
                distb = swapvar;
        }
        if ( dista < 0 )
        {
                swapvar = dista;
                dista = distb;
                distb = swapvar;
        }
        if ( dista < 0 )
        {
                return false;
        }
        
        intersection.point = ray.origin + ray.direction*dista;
        intersection.distance = dista;
        intersection.normal = (intersection.point-origin).norm();

        return true;
    }
};

#endif /* end of include guard: SPHERE_HPP_3Y096I6 */