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
        auto ss = std::stringstream();
        ss << "P3" << std::endl;
        ss << width << " " << height << std::endl;
        ss << 255 << std::endl;
        for(int x = 0; x < height; x++){
            for(int y = 0; y < width; y++){
                ss << std::get<0>(pget(x,y)) << " " << std::get<1>(pget(x,y)) << " " << std::get<2>(pget(x,y)) << " ";
            }
            ss << std::endl;
        }
        return ss.str();
    }
    
};

#endif /* end of include guard: BUFFER_HPP_8R7ZSI */
