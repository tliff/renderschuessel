#ifndef BUFFER_HPP_8R7ZSI
#define BUFFER_HPP_8R7ZSI

#include "color.hpp"
#include <sstream>
#include <vector>

class Buffer {
    int width;
    int height;
    
    std::vector<Color> data;
public:
    Buffer(int x, int y) : width(x),height(y) {
        data = std::vector<Color>(width*height);
    };
    
    void pset(int x, int y, Color const& c){
        data[y*width+x]=c;
    }
    
    const Color& pget(int x, int y) const {
        return data[y*width+x]; 
    }
    
    std::string ppm() const{
        std::stringstream ss;
        ss << "P3" << std::endl;
        ss << width << " " << height << std::endl;
        ss << 255 << std::endl;
        for(int x = 0; x < height; x++){
            for(int y = 0; y < width; y++){
                ss << pget(x,y)[0] << " " << pget(x,y)[1] << " " << pget(x,y)[2] << " ";
            }
            ss << std::endl;
        }
        return ss.str();
    }
    
};

#endif /* end of include guard: BUFFER_HPP_8R7ZSI */
