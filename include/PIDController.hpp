
class PIDController {

  private:

    double kP;
    int minSpeed;
    double error;

  public:

    PIDController(double inkP, int inMinSpeed);
    int getSpeedToMotors(int target, int current);   // fill in
    double getError();

};
