#include "main.h"

pros::Motor rightRoller(7, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftRoller(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

void rollers(int speed) {
  rightRoller.move(speed);
  leftRoller.move(speed);
}

void moveRollersTimed(int time, int speed) {
  rollers(speed);
  wait(time);
  rollers(0);
}

void brakeRollers() {
  rightRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  leftRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void coastRoller() {
  rightRoller.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftRoller.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
