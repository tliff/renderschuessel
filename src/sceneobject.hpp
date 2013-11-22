#ifndef SCENEOBJECT_HPP_JMV54IIN
#define SCENEOBJECT_HPP_JMV54IIN

class SceneObject {
protected:
    double emittance = 0;
    Color color;
public:
    virtual bool intersect(Ray const& ray, Intersection& intersection)const =0;
    virtual bool intersect(Ray const& ray)const =0;
    
    virtual bool isLight() const {
        return emittance > 0;
    }
    
    virtual bool getEmittance() const {
        return emittance;
    }

    virtual void setEmittance(double e){
        emittance = e;
    }
    
};


#endif /* end of include guard: SCENEOBJECT_HPP_JMV54IIN */
