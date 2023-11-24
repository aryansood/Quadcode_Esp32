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
I use Esp32 Rmt to send Dshot commands to the 4 Esc.
Unfortunately setting the high and low level signal timing, by simple calculation was not working, so I had to use a digital analyzer, to see the data packet, and tuning by trial and error the correct value of the DSHOT_MODE struct field duration. As my esc is cheap, only the Dshot up to 300 works, and the inverse command does not. 

## References
<a id="1">[1]</a> 
 Dimitri P. Bertsekas,
Dynamic Programming and Optimal Control, 
Vol. I, 3rd Edition, ISBN-13978-1886529267

<a id="2">[2]</a>
 Dan Simon,Optimal State Estimation, ISBN-13 978-0-471-70858-2

<a id="3">[3]</a> 
 https://brushlesswhoop.com/dshot-and-bidirectional-dshot/



