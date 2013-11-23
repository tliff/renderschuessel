#ifndef INTERSECTION_HPP_XODHISPF
#define INTERSECTION_HPP_XODHISPF

class SceneObject;

class Intersection {
public:
    double distance;
    Vector3 point;
    Vector3 normal;
    float emittance;
    bool light;
    Color color;
    
    void reset(){
        distance = std::numeric_limits<double>::max();
        light = false;
        emittance = 0;
        color = {0,0,0};
    }
};

#endif /* end of include guard: INTERSECTION_HPP_XODHISPF */
