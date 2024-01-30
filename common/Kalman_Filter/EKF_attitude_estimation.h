#include<Vector_Library/Quaternions.h>
#include<Kalman_Filter/Sensors_entrypoint.h>

Quaternion q_rot(1,0,0,0);
Quaternion q_rot_dot(1,0,0,0);

float Cov_acc[3][3] = {{0,0,0},
                       {0,0,0},
                       {0,0,0}}; //Covariance matrix acc
float Cov_gyro[3][3] = {{0,0,0},
                       {0,0,0},
                       {0,0,0}}; //Covariance matrix gyro
float Cov_magne[3][3] = {{0,0,0},
                        {0,0,0},
                        {0,0,0}}; // Covariance matrix magne

void Ukf_Attitude()
{
    
}

