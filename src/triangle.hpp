#ifndef TRIANGLE_HPP_QD0FQVYO
#define TRIANGLE_HPP_QD0FQVYO
#include "sceneobject.hpp"
#include "math.hpp"


class Triangle : public SceneObject {
public:
    Vector3 p0, p1, p2;
    Vector3 normal;
    
    Triangle(Vector3 _p0, Vector3 _p1, Vector3 _p2) : p0(_p0), p1(_p1), p2(_p2) {
        normal = (p0-p1)%(p2-p1);
        normal.normalize();
    };
    
    bool intersect(Ray const& ray) const {
        return false;
    }
    
    bool intersect(Ray const& ray, Intersection& intersection) const {
        Vector3 tvec, pvec, qvec;
        double det,inv_det;
        double t, u, v, w;

        // find vectors for two edges sharing vert0
        const Vector3 edge1 = p1 - p0;
        const Vector3 edge2 = p2 - p0;

        // begin calculating determinant - also used to calculate U parameter
        pvec = ray.direction%edge2;

        // if determinant is near zero, ray lies in plane of triangle
        det = edge1*pvec;

       /* if (det > -EPSILON && det < EPSILON)
          return false;*/
        inv_det = 1.0 / det;

        // calculate distance from vert0 to ray origin
        tvec = ray.origin - p0;

        // calculate U parameter and test bounds

        u = (tvec*pvec) * inv_det;
        if (u < 0.0 || u > (1.0 + EPSILON))
          return false;

        // prepare to test V parameter
        qvec = tvec%edge1;
        // calculate V parameter and test bounds
        v = (ray.direction * qvec) * inv_det;
        if (v < 0.0 || u + v > (1.0+EPSILON))
          return false;
  
        w = (1.0 +EPSILON) - ( u + v);
  
        // calculate t, ray intersects triangle
        t = (edge2 *qvec) * inv_det;
        if(t < 0) 
      	  return false;
        //std::cout << "Tri intersected" << std::endl;
        if(t > intersection.distance)
      	  return false;
 
        intersection.point = ray.origin + ray.direction*t;
        intersection.distance = t;
        intersection.light = isLight();
        if(normal * ray.direction > 0)
          	intersection.normal = normal * -1;
        else
            intersection.normal = normal;

      return true;
    }
};

#endif /* end of include guard: TRIANGLE_HPP_QD0FQVYO */
