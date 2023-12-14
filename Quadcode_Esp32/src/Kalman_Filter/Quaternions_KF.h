/*
Quaternion based Euler angles rappresentation
To do initialization quaternion rappresentation
Calculation using Gyroscope entrypoints
Every vector has a quaternion representaton with real part equal to zero
*/
#pragma once
#include <Kalman_Filter/Vector3.h>

class Quaternion
{
public:
    float q0;
    Vector3 q_d;

    Quaternion (float p0,float p1,float p2,float p3) : q_d(p1, p2, p3)
    {
        q0 = p0;
    }

    float Norm()
    {
        float norm = q0*q0+q_d.x*q_d.x+q_d.y*q_d.y+q_d.z*q_d.z;
        return norm;
    }

    void normalize()
    {
        float norm = q0*q0+q_d.x*q_d.x+q_d.y*q_d.y+q_d.z*q_d.z;
        q0 = q0/norm;
        q_d.x = q_d.x/norm;
        q_d.y = q_d.y/norm;
        q_d.z = q_d.z/norm;
    }

    Quaternion add(Quaternion q_other)
    {
        Vector3 temp = q_d + q_other.q_d;
        return Quaternion(q0+q_other.q0, temp.x, temp.y, temp.z);
    }

    float dot(Quaternion q_other)
    {
        return (q_d.dot(q_other.q_d)+q0*q_other.q0);
    }

    Quaternion cross(Quaternion q_other)
    {
        float real_part = q0*q_other.q0-q_d.dot(q_other.q_d);
        Vector3 Imm_part = q_other.q_d.scalar_prod(q0) + q_d.scalar_prod(q_other.q0) + q_d*(q_other.q_d);
    }

    Quaternion operator*(Quaternion q_other)
    {
        return cross(q_other);
    }

    Vector3 rotation(Vector3 rot_vector)
    {
        normalize();
        Quaternion q_rot(q0, q_d.x, q_d.y, q_d.z);
        Quaternion q_rot_inv(q0, -q_d.x, -q_d.y, -q_d.z);
        Quaternion vec_rot_q( 0.0, rot_vector.x, rot_vector.y, rot_vector.z);
        Quaternion rot_result = q_rot*(vec_rot_q*q_rot_inv); 
        return rot_result.q_d;
    }
};
//Test this code