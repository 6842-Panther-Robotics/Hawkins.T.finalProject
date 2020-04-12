#include "main.h"


pros::Motor liftMotor(5, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIPotentiometer liftPot('A');

PIDController liftPID(2.5, 15);

void lift(int speed) {
  liftMotor.move(speed);
}

void moveLiftTimed(int speed, int time) {
  lift(speed);
  wait(time);
  lift(0);
}

void brakeLift() {
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void coastLift() {
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void moveLift(int targetPosition) {

  lift(liftPID.getSpeedToMotors(targetPosition, liftPot.get_value()));

}

void liftOP() {

  brakeLift();

  if(master.get_digital(DIGITAL_L1)) {
    lift(127);
    }

  else if(master.get_digital(DIGITAL_L2)) {
    lift(-127);
    }

  else {
    brakeLift();
  }

  brakeRollers();
  if(master.get_digital(DIGITAL_R1)) {
    rollers(127);
  }
  else if(master.get_digital(DIGITAL_R2)) {
    rollers(-127);
  }
  else {
    brakeRollers();
  }

}
