#ifndef BUFFER_HPP_8R7ZSI
#define BUFFER_HPP_8R7ZSI

#include "color.hpp"
#include <sstream>
#include <vector>
#include <OpenEXR/half.h>
#include <OpenEXR/ImfRgbaFile.h>

class Buffer {
    int width;
    int height;
    
    std::vector<Color> data;
public:
    Buffer(){
        
    }
    
    Buffer(int x, int y) : width(x),height(y) {
        data = std::vector<Color>(width*height);
    };
    
    void pset(int x, int y, Color const& c){
        data[y*width+x]=c;
    }

    void padd(int x, int y, Color const& c){
        data[y*width+x] +=c;
    }
    
    const Color& pget(int x, int y) const {
        return data[y*width+x]; 
    }
    
    void writeEXR() const{
        double max = 0;
        for(auto& c : data){
            max = std::max(max, c.c[0]);
            max = std::max(max, c.c[1]);
            max = std::max(max, c.c[2]);
        }
        
        Imf::Rgba* pixelData = (Imf::Rgba*) malloc(sizeof(Imf::Rgba)*data.size());
        for(int i = 0; i < data.size(); i++){
            pixelData[i] = {data[i].c[0]/max,data[i].c[1]/max,data[i].c[2]/max,1};
        }
        Imf::RgbaOutputFile file ("test.exr", width, height, Imf::WRITE_RGBA);
        file.setFrameBuffer (pixelData, 1, width);
        file.writePixels (height);
    }
    
    Buffer& operator+=(Buffer const& other){
        for(int i = 0; i < data.size(); i++)
            data[i]+=other.data[i];
        return *this;
    }
    
    Buffer operator+(Buffer const& other){
        Buffer b = Buffer(width, height);
        b += other;
        return b;
    }
    
    
};

#endif /* end of include guard: BUFFER_HPP_8R7ZSI */
