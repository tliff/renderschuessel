#ifndef COLOR_HPP_TA2T4DU5
#define COLOR_HPP_TA2T4DU5


class Color {
public:
    double c[3];

    Color(double r,double g,double b){
      c[0] = r;
      c[1] = g;
      c[2] = b;
    }
    
    
    Color(){
      c[0]=0;
      c[1]=0;
      c[2]=0;
    };
    
    inline double operator[](int i) const {
        return c[i];
    }
    
    inline Color& operator+=(Color const& other){
      c[0] += other.c[0];
      c[1] += other.c[1];
      c[2] += other.c[2];
      return *this;
    }
    
    inline Color& operator*=(Color const& other){
      c[0] *= other.c[0];
      c[1] *= other.c[1];
      c[2] *= other.c[2];
      return *this;
    }
    
    inline Color operator+(Color const&  other) const {
      Color c = *this;
      c+= other;
      return c;
    }
    
    inline Color operator*(Color const&  other) const {
      Color c = *this;
      c*= other;
      return c;
    }
    
    
    inline Color operator*(float scale) const {
      return {c[0]*scale,c[1]*scale,c[2]*scale};
    }
};
  
#endif /* end of include guard: COLOR_HPP_TA2T4DU5 */
 