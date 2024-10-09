//
// Created by delbek on 10/9/24.
//

#ifndef CS419_VECTOR_H
#define CS419_VECTOR_H


class Vector 
{
public:
    Vector(unsigned size);
    Vector(const Vector& otherVector);
    Vector& operator=(const Vector& otherVector);
    Vector(Vector&& otherVector);
    Vector& operator=(Vector&& otherVector);
    void free();
    ~Vector();

    double operator[](unsigned index) const;
    double& operator[](unsigned index);
    __inline__ unsigned getSize() const {return m_Size;}
    __inline__ double* getVector() const {return m_Data;}

private:
    unsigned m_Size;
    double* m_Data;
};


#endif //CS419_VECTOR_H
