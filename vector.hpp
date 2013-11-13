#ifndef VECTOR_HPP_Q9NYBVZ7
#define VECTOR_HPP_Q9NYBVZ7


template<class T> class Vector3Base {
public:
    T x[3];
    
    operator std::string(){
        return "Vector{"+std::to_string(x[0])+","+std::to_string(x[1])+","+std::to_string(x[2])+"}";
    }
    
    const T length(){
        return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
    }
    
    void normalize(){
        T l = length();
        x[0]/=l;
        x[1]/=l;
        x[2]/=l;
    }
    
    const Vector3Base<T> operator+(const Vector3Base<T>& other){
        return {x[0]+other.x[0], x[1]+other.x[1], x[2]+other.x[2]};
    }
    
    const Vector3Base<T> operator*(const Vector3Base<T>& other){
        return x[0]*other.x[0] + x[1]*other.x[1] + x[2]*other.x[2];
    }

    const Vector3Base<T> operator%(const Vector3Base<T>& other){
        return Vector3Base<T>({x[1]*other.x[2]-x[2]*other.x[1],x[2]*other.x[0]-x[0]*other.x[2],x[0]*other.x[1]-x[1]*other.x[0]});
    }

};

typedef Vector3Base<double> Vector3;



#endif /* end of include guard: VECTOR_HPP_Q9NYBVZ7 */
