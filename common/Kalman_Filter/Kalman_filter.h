#include<Vector_Library/Quaternions.h>
#include<Kalman_Filter/Sensors_entrypoint.h>
#include<Vector_Library/Matrix.h>


class Linear_Kalman_Filter{
public:
    Matrix x, A, B, C, P, Q, R;

    Linear_Kalman_Filter(int size_x, int size_y, int size_u) : x(size_x), A(size_x), B(size_x, size_u),C(size_y, size_x), Q(size_x), R(size_y), P(size_y){

    }

    void set_next_parameters(Matrix A, Matrix B, Matrix C, Matrix Q, Matrix R){
        this->A = A;
        this->B = B;
        this->C = C;
        this->Q = Q;
        this->R = R;
    }

    void update_x(Matrix y, Matrix u){
        Matrix P_priori = (A*P*A.Tran())+Q;
        Matrix K = P_priori*C.Tran()*((C*P_priori*C.Tran())+R);
        Matrix x_priori = (A*x)+(B*u);
        this->x = x_priori+K*(y-C*x_priori);
        Matrix Iden(P.num_row);
        this->P = (Iden-K*C)*P_priori;
    }
};

