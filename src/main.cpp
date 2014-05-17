#include <iostream>
#include <thread>
#include <unistd.h>
#include "renderschuessel.hpp"

#ifndef MAXDEPTH
#define MAXDEPTH 5
#endif

#ifndef THREAD_COUNT
#define THREAD_COUNT 8
#endif

#ifndef IMAGESIZE
#define IMAGESIZE 1600
#endif

#ifndef SAMPLES_PER_PIXEL
#define SAMPLES_PER_PIXEL 2048l
#endif

Scene s;

Buffer buffers[THREAD_COUNT];

long threadProgress[THREAD_COUNT];

std::function<double(void)> generator;

Color tracePath(Ray& r, int depth=0){

    if(depth >= MAXDEPTH)
        return {0,0,0};
    Intersection i;
    i.reset();
    if(!s.intersect(r,i))
        return {0,0,0};

    Ray newRay;
    Color emitted = {i.emittance,i.emittance,i.emittance};
        
    newRay.origin = i.point+(i.normal*0.001);
    newRay.direction = i.normal.randomVectorInHemisphere();
  
    float cos_theta = newRay.direction * i.normal;
    
    Color reflected = tracePath(newRay, depth + 1) * i.color * cos_theta;

    return  emitted + reflected;

}

void renderBuffer(int threadId){
    std::cout << "Thread " << threadId << " running" << std::endl;
    Ray r = {{0,0,10},{-1,0,0}};
    auto intgenerator = std::bind(std::uniform_int_distribution<int>(-(IMAGESIZE/2),(IMAGESIZE/2-1)), std::mt19937(std::random_device{}()));
    
    while(threadProgress[threadId] < IMAGESIZE*IMAGESIZE*SAMPLES_PER_PIXEL){
        int x = intgenerator();
        int y = intgenerator();
        float _x = (15/(double)IMAGESIZE)*x;
        float _y = (15/(double)IMAGESIZE)*y;
        r.direction = (Vector3({_x, _y, 0.001})-r.origin).norm();
        buffers[threadId].padd(x+(IMAGESIZE/2),y+(IMAGESIZE/2), tracePath(r));
      
        threadProgress[threadId]++;
    }
    std::cout << "Thread " << threadId << " done" << std::endl;
}

void buildTestScene(){
    s.addObject(new Sphere({-2.5,0,0},2));
    Sphere* sphere = new Sphere({2.5,0,0},1);
    sphere->setEmittance(1);
    s.addObject(sphere);
    
    //bottom wall
    Triangle* t;
    t = new Triangle({-6,-10,-10},{-6,10,-10},{-6,10,10});
    s.addObject(t);
    t = new Triangle({-6,-10,-10},{-6,-10,10},{-6,10,10});
    s.addObject(t);
       
    //top wall
    t = new Triangle({6,-10,-10},{6,10,-10},{6,10,10});
    s.addObject(t);
    t = new Triangle({6,-10,-10},{6,-10,10},{6,10,10});
    s.addObject(t);
        
    //right wall
    t = new Triangle({-6,10,-10},{6,10,-10},{6,10,10});
    t->setColor({1,0,0}); 
    s.addObject(t);
    t = new Triangle({6,10,10},{-6,10,10},{-6,10,-10});
    t->setColor({1,0,0}); 
    s.addObject(t);

    //left wall
    t = new Triangle({-6,-10,-10},{6,-10,-10},{6,-10,10});
    t->setColor({0,1,0}); 
    s.addObject(t);
    t = new Triangle({6,-10,10},{-6,-10,10},{-6,-10,-10});
    t->setColor({0,1,0}); 
    s.addObject(t);
        
    //back wall
    s.addObject(new Triangle({-6,10,-10},{6,10,-10},{6,-10,-10}));
    s.addObject(new Triangle({6,-10,-10},{-6,-10,-10},{-6,10,-10}));
    
    
}

void readSceneFromSTDIN(){
    std::cout << "Reading" << std::endl;
    SceneObject* object = NULL;
    std::string command;
    while((std::cin >> command) && (command != "commit") ){
        std::cout << command << std::endl;
    }
    std::cout << "done" << std::endl;
}

int main (int argc, char const *argv[])
{
    std::cout << "." << std::flush << std::endl;
    generator = std::bind(std::uniform_real_distribution<double> (-1,1), std::mt19937(std::random_device{}()));
    
    if(argc == 2 && strcmp(argv[1],"--pipe") == 0){
        
        readSceneFromSTDIN();
    }

    buildTestScene();
    std::vector<std::thread> threads;

    for(int i = 0; i < THREAD_COUNT; ++i){
        buffers[i] = Buffer(IMAGESIZE,IMAGESIZE);
        threads.push_back(std::thread(std::bind(renderBuffer,i)));
    }
    std::thread test([](){
        long lastAmount = 0;
        while(true){
            long currentAmount = 0;
            for(long l : threadProgress){
                currentAmount += l;
            }
            float percent = currentAmount/(float)(THREAD_COUNT*IMAGESIZE*IMAGESIZE*SAMPLES_PER_PIXEL);
            std::cout << "Samples/second: " << (currentAmount - lastAmount) << " " << percent*100 << "%" << std::endl;
            lastAmount = currentAmount;
            sleep(1);
        } 
    });

    Buffer finalBuffer(IMAGESIZE,IMAGESIZE);
  
    for(int i = 0; i < THREAD_COUNT; ++i){
        threads[i].join();
        finalBuffer += buffers[i];
    }
  
    finalBuffer.writeEXR();
  

    return 0;
}

