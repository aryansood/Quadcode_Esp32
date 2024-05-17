#include<Vector_Library/Quaternions.h>
#include<Kalman_Filter/Sensors_entrypoint.h>
#include<Vector_Library/Matrix.h>

Quaternion q_rot(1,0,0,0);
Quaternion q_rot_dot(1,0,0,0);

class Linear_Kalman_Filter{
public:
    Matrix x;
    Matrix A;
    Matrix B;
    Matrix C;
    Matrix P;
    Matrix Q;
    Matrix R;
    Linear_Kalman_Filter(int size_x, int size_y, int size_u) : x(size_x), A(size_x), B(size_x, size_u),C(size_y, size_x), Q(size_x), R(size_y), P(size_y){

    }

    void set_next_parameters(Matrix A, Matrix B, Matrix C, Matrix Q, Matrix R){
        this->A = A;
        this->B = B;
        this->C = C;
        this->Q = Q;
        this->R = R;
    }

    void update_x(){
        
    }
};

