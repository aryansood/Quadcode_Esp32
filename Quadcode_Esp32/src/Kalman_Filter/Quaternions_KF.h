/*
Quaternion based Euler angles rappresentation
To do initialization quaternion rappresentation
Calculation using Gyroscope entrypoints
Every vector has a quaternion representaton with real part equal to zero
*/
#include <Kalman_Filter/Sensor_para_def.h>

class Quaternion
{
public:
    float q0;
    float q1;
    float q2;
    float q3;
    float q0_dot;
    float q1_dot;
    float q2_dot;
    float q3_dot;

    Quaternion (float p0,float p1,float p2,float p3)
    {
        q0 = p0;
        q1 = p1;
        q2 = p2;
        q3 = p3;
    }

    Quaternion Rotation(Quaternion v_rot)
    {
        
    };

    void Quaternion_update () //Pass gyroscope values
    {

    };
};

Quaternion Quaternion_sum(Quaternion v1, Quaternion v2)
{
    Quaternion v3(v1.q0+v2.q0,v1.q1+v2.q1,v1.q2+v2.q2,v1.q3+v2.q3);
    return v3;
};

Quaternion Quaternion_multi(Quaternion v1, Quaternion v2)
{
    Quaternion v3(0,0,0,0);
    v3.q0 = (v1.q0*v2.q0)-(v1.q1*v2.q1+v1.q2*v2.q2+v1.q3*v2.q3);
    v3.q1 = (v1.q0*v2.q1)+(v2.q0*v1.q1)+(v1.q2*v2.q3-v1.q3*v2.q2);
    v3.q2 = (v1.q0*v2.q2)+(v2.q0*v1.q2)+(v1.q3*v2.q1-v1.q1*v2.q3);
    v3.q3 = (v1.q0*v2.q3)+(v2.q0*v1.q3)+(v1.q1*v2.q2-v1.q2*v2.q1);
};