#ifndef MATRIX_HPP_EB7NHHFW
#define MATRIX_HPP_EB7NHHFW


class Matrix {
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
    
};

#endif /* end of include guard: MATRIX_HPP_EB7NHHFW */
