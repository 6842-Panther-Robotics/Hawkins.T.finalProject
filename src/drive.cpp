#include "main.h"

pros::Motor rightFront(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftFront(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Imu inertial(9);

PIDController movePID(0.5, 30);
PIDController turnPID(0.2, 30);

double pi = 3.1415928;

void right(int speed) {
  rightFront.move(speed);
  rightBack.move(speed);
}

void left(int speed) {
  leftFront.move(speed);
  leftBack.move(speed);
}

void wait(int time) {
  pros::delay(time);
}

void timedDrive(int time, int speed) {
  left(speed);
  right(speed);
  wait(time);
  left(0);
  right(0);

}

void brake() {
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void coast() {
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void move(int targetInInches) {

  rightFront.tare_position();
  leftFront.tare_position();

  int time = 0;

  double target = 360 * (targetInInches  / (4 * pi));


  while (time < 50) {

    int PIDSpeed = movePID.getSpeedToMotors(target, rightFront.get_position());


    if (rightFront.get_position() - leftFront.get_position() >= 2 ) {
      right(PIDSpeed * 0.75);
      left(PIDSpeed);
    }

    else if (leftFront.get_position() - rightFront.get_position() >= 2 ) {
      right(PIDSpeed);
      left(PIDSpeed * 0.75);

    right(PIDSpeed);
    left(PIDSpeed);

      if (movePID.getError() < 1 && movePID.getError() >= 0) {
        time++;
        wait(2);
      }

      else if (movePID.getError() > -1 && movePID.getError() < 0) {
        time++;
        wait(2);
      }

    }
  }
  right(0);
  left(0);
}

void turn (int target) {

int time = 0;

  while (time <= 50) {

  right(turnPID.getSpeedToMotors(target, inertial.get_rotation()));
  left(-(turnPID.getSpeedToMotors(target, inertial.get_rotation())));

    if (turnPID.getError() < 1 && turnPID.getError() >= 0) {
      time++;
      wait(2);
    }
    else if (turnPID.getError() > -1 && turnPID.getError() < 0) {
      time++;
      wait(2);
    }
  }

  right(0);
  left(0);
}



void moveBackward(int targetInInches) {

  rightFront.tare_position();
  leftFront.tare_position();

  int time = 0;

  double target = 360 * (targetInInches  / (4 * pi));


  while (time < 50) {

    int PIDSpeed = movePID.getSpeedToMotors(target, rightFront.get_position());


    if ((-rightFront.get_position()) - (-leftFront.get_position()) <= -2 ) {
      right(-PIDSpeed * 0.75);
      left(-PIDSpeed);
    }

    else if ((-leftFront.get_position()) - (-rightFront.get_position()) <= -2 ) {
      right(-PIDSpeed);
      left(-PIDSpeed * 0.75);

    right(-PIDSpeed);
    left(-PIDSpeed);

      if (movePID.getError() < 1 && movePID.getError() >= 0) {
        time++;
        wait(2);
      }

      else if (movePID.getError() > -1 && movePID.getError() < 0) {
        time++;
        wait(2);
      }

    }
  }
  right(0);
  left(0);

}

void driveOP() {

}
