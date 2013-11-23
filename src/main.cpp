#include <iostream>
#include <thread>
#include "renderschuessel.hpp"

#ifndef MAXDEPTH
#define MAXDEPTH 16
#endif

#ifndef THREAD_COUNT
#define THREAD_COUNT 8
#endif

#ifndef IMAGESIZE
#define IMAGESIZE 800
#endif

#ifndef SAMPLES_PER_PIXEL
#define SAMPLES_PER_PIXEL 4096l
#endif

Scene s;

Buffer buffers[THREAD_COUNT];

std::function<double(void)> generator;

Color tracePath(Ray& r, int depth=0){

    if(depth >= MAXDEPTH)
        return {0,0,0};
    Intersection i;
    i.reset();
    if(!s.intersect(r,i))
        return {0,0,0};

    Ray newRay;

    newRay.origin = i.point+(i.normal*0.001);
    newRay.direction = i.normal.randomVectorInHemisphere();
  
    float cos_theta = newRay.direction * i.normal;

    Color reflected = tracePath(newRay, depth + 1) * cos_theta;
    Color emitted = {i.emittance,i.emittance,i.emittance};

    return  emitted + reflected;

}

void renderBuffer(int threadId){
    Ray r = {{0,0,10},{-1,0,0}};
    long sampleCount = 0;
    auto intgenerator = std::bind(std::uniform_int_distribution<int>(-(IMAGESIZE/2),(IMAGESIZE/2-1)), std::mt19937(std::random_device{}()));
    
    while(sampleCount < IMAGESIZE*IMAGESIZE*SAMPLES_PER_PIXEL){
        int x = intgenerator();
        int y = intgenerator();
        float _x = (15/(double)IMAGESIZE)*x;
        float _y = (15/(double)IMAGESIZE)*y;
        r.direction = (Vector3({_x, _y, 0.001})-r.origin).norm();
        buffers[threadId].padd(x+(IMAGESIZE/2),y+(IMAGESIZE/2), tracePath(r));
      
        sampleCount++;
    }
  
}


int main (int argc, char const *argv[])
{
    
    generator = std::bind(std::uniform_real_distribution<double> (0,1), std::mt19937(std::random_device{}()));
    s.addObject(new Sphere({-2.5,0,0},2));
    Sphere* sphere = new Sphere({2.5,0,0},2);
    sphere->setEmittance(1);
    s.addObject(sphere);
    
    s.addObject(new Triangle({-6,-10,-10},{-6,10,-10},{-6,10,10}));
    s.addObject(new Triangle({-6,-10,-10},{-6,-10,10},{-6,10,10}));

    std::vector<std::thread> threads;

    for(int i = 0; i < THREAD_COUNT; ++i){
        buffers[i] = Buffer(IMAGESIZE,IMAGESIZE);
        threads.push_back(std::thread(std::bind(renderBuffer,i)));
    }

    Buffer finalBuffer(IMAGESIZE,IMAGESIZE);
  
    for(int i = 0; i < THREAD_COUNT; ++i){
        threads[i].join();
        finalBuffer += buffers[i];
    }
  
    finalBuffer.writeEXR();
  

    return 0;
}

