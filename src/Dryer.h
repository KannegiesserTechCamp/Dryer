#ifndef DRYER_H
#define DRYER_H

#define MOTOR_OFF 0
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 2

// Functions that are available for the main
void Motorsetup();
void MotorLeft();
void MotorRight();
void MotorStopRight();
void MotorStopLeft();
void MotorOff();
void SetMotorSpeed(int direction, int rampStep);

#endif