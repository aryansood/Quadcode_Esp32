/*
Quaternion based Euler angles rappresentation
To do initialization quaternion rappresentation
Calculation using Gyroscope entrypoints
Every vector has a quaternion representaton with real part equal to zero
*/
class Quaternion
{
public:
    float q0;
    float q1;
    float q2;
    float q3;
    float norm = 1;

    Quaternion (float p0,float p1,float p2,float p3)
    {
        q0 = p0;
        q1 = p1;
        q2 = p2;
        q3 = p3;
        norm = q0*q0+q1*q1+q2*q2+q3*q3;
    }

    int Norm()
    {
        norm = q0*q0+q1*q1+q2*q2+q3*q3;
        return norm;
    }

    void normalize()
    {
        norm = q0*q0+q1*q1+q2*q2+q3*q3;
        q0 = q0/norm;
        q1 = q1/norm;
        q2 = q2/norm;
        q3 = q3/norm;
    }
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

Quaternion Quaternion_rotation(Quaternion q, Quaternion v)
{
    Quaternion l(0,0,0,0);
    Quaternion q_conj(q.q0,-q.q1,-q.q2,-q.q3);
    q.normalize();
    l = Quaternion_multi(v,q_conj);
    l = Quaternion_multi(q,l);
}

//Test this code