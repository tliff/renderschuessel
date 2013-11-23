#ifndef SCENEOBJECT_HPP_JMV54IIN
#define SCENEOBJECT_HPP_JMV54IIN

class SceneObject {
protected:
    double emittance = 0;
    Color color;
public:
    
    SceneObject(){
        color = {1,1,1};
    }
    
    virtual bool intersect(Ray const& ray, Intersection& intersection)const =0;
    virtual bool intersect(Ray const& ray)const =0;
    
    virtual bool isLight() const {
        return emittance > 0;
    }
    
    virtual bool getEmittance() const {
        return emittance;
    }
    
    virtual const Color& getColor() const {
        return color;
    }

    virtual void setEmittance(double e){
        emittance = e;
    }

    virtual void setColor(Color c){
        color = c;
    }
    
};


#endif /* end of include guard: SCENEOBJECT_HPP_JMV54IIN */
