#ifndef MATRIX_HPP_EB7NHHFW
#define MATRIX_HPP_EB7NHHFW


class Matrix44 {
public:
    double x[16];
    
    operator std::string(){
        std::string s;
        s += "Matrix{";
        for(int i=0; i < 16; i++){
            s+= std::to_string(x[i]);
            if(i != 15)
                s+=",";
        }
        s += "}";
        return s;
    };
    
    Matrix44& operator*=(Matrix44 const& other){
        *this = *this * other;
        return *this;
    }
    
    
    Matrix44 operator*(Matrix44 const& other) const {
        Matrix44 r;
        for(int k = 0; k < 4; k++){
            for(int i = 0; i < 4; i++){
                double val = 0;
                for(int j = 0; j < 4; j++){
                    val+=x[i*4+j]*other.x[j*4+k];
                }
                r.x[i*4+k]=val;
            }
        }
        return r;
    }
    

};

#endif /* end of include guard: MATRIX_HPP_EB7NHHFW */
