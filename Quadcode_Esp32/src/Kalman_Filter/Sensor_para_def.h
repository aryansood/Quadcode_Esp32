#include<Kalman_Filter/Sensors_entrypoint.h>

#define Num_acc 2
#define Num_gyro 2
#define Num_compass 1
#define Num_alt 1

struct Acc Acc_state[Num_acc];
struct Gyro Gyro_state[Num_gyro];
struct Altitude Alt_state[Num_alt];
struct Compass Heading_state[Num_compass];