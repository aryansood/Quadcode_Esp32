# Esp32 Quadcopter firmware
## Sensor board schematic
You can find the sensor board schematics in the folder Sensor_Schematic_Pcb \
Sensor used:
- LSM6DSM (Acc-Gyro)
- LIS2MDL (Magnetometer)
- BMP388  (Acc-Gyro)
- BMI088  (Barometer)
## Details
- [Dshot Protocol](#dshot-esc-protocol)
- [Kalman filter estimation](#kalman-filter-attitude-estimation)
- [Images](#images)

## Kalman Filter Attitude Estimation
A quaternion based rotation rapresentation is used, for easier implementation of the kalman filter. For understanding quaternions refer to [this](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjhxsfv96-CAxXcVPEDHbDWA_kQFnoECA8QAQ&url=https%3A%2F%2Fgraphics.stanford.edu%2Fcourses%2Fcs348a-17-winter%2FPapers%2Fquaternion.pdf&usg=AOvVaw3PvGFRNUboT5pRiKrHrWJZ&opi=89978449).
\
For understanding Kalman filter refer to appendix E of [[1]](#1) and to [[2]](#2).
 \
 In general we have the following: 

```math
\begin{align}
 x_{t} = Ax_{t-1}+Bu_{t-1}+w_{t-1}
 \\
 z_{t} = Cx_{t-1}+v_{t-1}
 \end{align}
```
Where $w_t$ and $v_t$ are gaussian random noise.
\
In the case of the quadcopter, quaternions are used the equations are:
```math
\begin{align}
\mathbf{\dot{q}} = \frac{1}{2}\mathbf{\Omega q}
\end{align}
```
Before putting the accelerometers and the gyro into the kalman filter, we do a wheithed average repsective to the number of sensors.

## Dshot Esc Protocol

For understanding Dshot protocol go to [[3]](#3)
Esp32 Rmt is used to send Dshot commands to the 4 Esc.
Unfortunately setting the high and low level signal timing, by simple calculation was not working, so the use of a digital analyzer was needed to see the data packet. The correct value of the DSHOT_MODE struct field duration was tuned by trial and error. As the Esc used for the Quadcopter is cheap, only the Dshot up to 300 works.
The code should work in theory with each Dshot esc.

Use DSHOT_MOTOR_SETUP to setup the motors, 
```
#define RMT_TX_GPIO_NUM_1 GPIO_NUM_16
#define RMT_TX_GPIO_NUM_2 GPIO_NUM_17
#define RMT_TX_GPIO_NUM_3 GPIO_NUM_18
#define RMT_TX_GPIO_NUM_4 GPIO_NUM_19
```
Modify the GPIO numbers according to connection of the pins. 
```
enum DSHOT_VALUES {DSHOT_150, DSHOT_300, DSHOT_600};
```
In DSHOT_MOTOR_INITIALIZATION and DSHOT_MOTOR_SEND_THROTTLE change every instance of DSHOT_300, if there is need to use different speed for sending data. 

## References
<a id="1">[1]</a> 
 Dimitri P. Bertsekas,
Dynamic Programming and Optimal Control, 
Vol. I, 3rd Edition, ISBN-13978-1886529267

<a id="2">[2]</a>
 Dan Simon,Optimal State Estimation, ISBN-13 978-0-471-70858-2

<a id="3">[3]</a> 
 https://brushlesswhoop.com/dshot-and-bidirectional-dshot/

## Images

![alt text](/Images/sensor_board.jpg | width=100)
![alt text](/Images/Quadcopter_esp32.jpg | width=100)





