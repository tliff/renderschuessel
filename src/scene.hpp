#ifndef SCENE_HPP_W9RCL71
#define SCENE_HPP_W9RCL71

#include "sceneobject.hpp"
#include <list>

class Scene : public SceneObject {
  std::list<SceneObject*> sceneObjects;
public:    
  bool intersect(Ray const& ray, Intersection& intersection) const {
    bool hit = false;
    for(auto &o : sceneObjects){
      hit = o->intersect(ray, intersection) || hit;
    }
    return hit;
  }
    
  bool intersect(Ray const& ray) const {
    for(auto &o : sceneObjects){
      if(o->intersect(ray))
        return true;
    }
    return false;
  }
    
  void addObject(SceneObject*s) {
    sceneObjects.push_back(s);
  }
    
};

#endif /* end of include guard: SCENE_HPP_W9RCL71 */
