#include "main.h"

double kP = 0;

int minSpeed = 30;

PIDController::PIDController(double inkP, int inMinSpeed) {
  kP = inkP;
  minSpeed = inMinSpeed;
}

int PIDController::getSpeedToMotors(int target, int current) {

  double error = target - current;

  int speed = error * kP;

    if(speed <= minSpeed && speed >= 0) {
      speed = minSpeed;
    }

    if(speed >= -minSpeed && speed < 0) {
      speed = -minSpeed;
    }

  return speed;
}

double PIDController::getError() {
  return error;
}
