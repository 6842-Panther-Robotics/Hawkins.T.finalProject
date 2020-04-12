#include "main.h"

pros::Motor tilterMotor(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIPotentiometer tilterPot('B');

PIDController tilterPID(5, 20);

void tilter(int speed) {
  tilterMotor.move(speed);
}

void moveTilterTimed(int speed, int time) {
  tilter(speed);
  wait(time);
  tilter(0);
}

void brakeTilter() {
  tilterMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void coastTilter() {
  tilterMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void score() {

  tilter(tilterPID.getSpeedToMotors(3000, tilterPot.get_value()));
}

void tilterBack() {

  tilter(tilterPID.getSpeedToMotors(200, tilterPot.get_value()));
}

void tilterOP() {

  brakeTilter();

  if (master.get_analog(ANALOG_LEFT_Y)) {
    score();
  }

  else if (master.get_analog(ANALOG_RIGHT_Y)) {
    tilterBack();
  }

  else {
    brakeTilter();
  }
}
