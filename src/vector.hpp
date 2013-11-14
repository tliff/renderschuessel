#ifndef VECTOR_HPP_Q9NYBVZ7
#define VECTOR_HPP_Q9NYBVZ7

#include <cmath>

template<class T> class Vector3Base {
public:
    T x[3];
    
    operator std::string(){
        return "Vector{"+std::to_string(x[0])+","+std::to_string(x[1])+","+std::to_string(x[2])+"}";
    }
    
    const T length(){
        return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
    }
    
    Vector3Base<T> norm()const{
        Vector3Base<T> v = *this;
        v.normalize();
        return v;
    }
    
    Vector3Base<T>& normalize(){
        T l = length();
        x[0]/=l;
        x[1]/=l;
        x[2]/=l;
        return *this;
    }
    
    Vector3Base<T>& operator+=(Vector3Base<T>const& other){
        x[0]+=other.x[0];
        x[1]+=other.x[1];
        x[2]+=other.x[2];
        return *this;
    }
    
    Vector3Base<T>& operator-=(Vector3Base<T>const& other){
        x[0]-=other.x[0];
        x[1]-=other.x[1];
        x[2]-=other.x[2];
        return *this;
    }


    Vector3Base<T>& operator*=(const double other){
        x[0]*=other;
        x[1]*=other;
        x[2]*=other;
        return *this;
    }

    Vector3Base<T> operator+(Vector3Base<T> const& other)const{
        auto v = *this;
        v+= other;
        return v;
    }

    Vector3Base<T> operator-(Vector3Base<T>const& other)const{
        auto v = *this;
        v-= other;
        return v;
    }
    
    T operator*(Vector3Base<T>const& other)const{
        return x[0]*other.x[0] + x[1]*other.x[1] + x[2]*other.x[2];
    }

    Vector3Base<T> operator*(double other)const{
        auto v = *this;
        v*= other;
        return v;
    }

    Vector3Base<T>& operator%=(Vector3Base<T>const& other){
        T a = x[1]*other.x[2]-x[2]*other.x[1];
        T b = x[2]*other.x[0]-x[0]*other.x[2];
        T c = x[0]*other.x[1]-x[1]*other.x[0];
        x[0] = a;
        x[1] = b;
        x[2] = c;
        return *this;
    }

    Vector3Base<T> operator%(Vector3Base<T>const& other)const{
        auto v = *this;
        v%= other;
        return v;
    }

    bool operator==(Vector3Base<T>const& other) const {
        return x[0]==other.x[0]&&x[1]==other.x[1]&&x[2]==other.x[2];
    }

    bool operator!=(Vector3Base<T>const& other) const {
        return !(*this==other);
    }
    
    bool about(Vector3Base<T>const& other) const{
        return abs(x[0]-other.x[0] < EPSILON && x[1]-other.x[1] < EPSILON && x[2]-other.x[2] < EPSILON);
    }

};

typedef Vector3Base<double> Vector3;



#endif /* end of include guard: VECTOR_HPP_Q9NYBVZ7 */
