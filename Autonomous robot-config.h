#include <string>
vex::brain Brain;

using namespace std;
using namespace vex;



// main.cpp functions
void drive(int);

// General Functions
motor assignMotor(int);
controller assignControler();
int getAxisPosition(int);
void printError();
void printToScreen(const char*);
void pauseTask(int); // time in milliseconds between 100 and 5000
// Autonomous Functions List
// All two parameter functions take the form of Function(speed, time)
// All single parameter functions take the form of Function(time)
void AutoDriveForward(int, int);
void AutoDriveBackward(int, int);
void AutoDriveTurnLeft(int, int);
void AutoDriveTurnRight(int, int);
bool AutoMoveArmUp(int, int);
bool AutoMoveArmDown(int);
bool AutoClawOpen(int, int);
bool AutoClawClosed(int);

// Sensor Functions

// Declared and Defined Variables
motor DriveMotorLeft = assignMotor(1);
motor DriveMotorRight = assignMotor(2);
motor ArmMotor = assignMotor(3);
motor ClawMotor = assignMotor(4);
controller ConOne = assignControler();
bool OnOff = true;

// General Functions

void printError() {
    Brain.Screen.print("Error: values input outside permitted limits!");
}

void pauseTask(int time) {
    if(time < 100 || time > 5000) {
        printError();
    } else {
        task::sleep(time);
    }
}
int getAxisPosition(int motorPort) {
    int posVal = 0;
    
    if(motorPort == 3) {
        posVal = ConOne.Axis3.value();
    }else if(motorPort == 4) {
        posVal = ConOne.Axis2.value();
    }
    
    return posVal;
}

motor assignMotor(int portNumber) {
    return motor(portNumber - 1);
}

controller assignControler() {
    return controller();
}

void printToScreen(const char* input) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(input);
}

void ProgramStop() {
    if(ConOne.ButtonX.pressing()) {
        OnOff = false;
    }
}

// End General Functions
// AUTONOMOUS SECTION  

// Speed 15-100 dps  Time 500-5000
void AutoDriveForward(int speed, int time) {
    if(speed < 15 || speed > 500) {
        printError();
    } else if(time < 500 || time > 5000) {
        printError();
    } else {
        printToScreen("Forward");
        DriveMotorLeft.spin(directionType::fwd, speed, velocityUnits::dps);
        DriveMotorRight.spin(directionType::rev, speed, velocityUnits::dps);
        
        task::sleep(time);
        
        DriveMotorLeft.stop();
        DriveMotorRight.stop();
        
        task::sleep(700);
    }
}

void AutoDriveBackward(int speed, int time) {
    if(speed < 15 || speed > 500) {
        printError();
    } else if(time < 500 || time > 5000) {
        printError();
    } else {
        printToScreen("Backward");
        DriveMotorLeft.spin(directionType::rev, speed, velocityUnits::dps);
        DriveMotorRight.spin(directionType::fwd, speed, velocityUnits::dps);
        
        task::sleep(time);
        
        DriveMotorLeft.stop();
        DriveMotorRight.stop();
        task::sleep(700);
    }
}

void AutoDriveTurnLeft(int speed, int time) {
    if(speed < 15 || speed > 500) {
        printError();
    } else if(time < 500 || time > 5000) {
        printError();
    } else {
        printToScreen("Turning Left");
        DriveMotorLeft.spin(directionType::rev, speed, velocityUnits::dps);
        DriveMotorRight.spin(directionType::rev, speed, velocityUnits::dps);
        
        task::sleep(time);
        
        DriveMotorLeft.stop();
        DriveMotorRight.stop();
        
        task::sleep(700);
    }
}

void AutoDriveTurnRight(int speed, int time) {
    if(speed < 15 || speed > 500) {
        printError();
    } else if(time < 500 || time > 5000) {
        printError();
    } else {
        printToScreen("Turning Right");
        DriveMotorLeft.spin(directionType::fwd, speed, velocityUnits::dps);
        DriveMotorRight.spin(directionType::fwd, speed, velocityUnits::dps);
        
        task::sleep(time);
        
        DriveMotorLeft.stop();
        DriveMotorRight.stop();
        
        task::sleep(700);
    }
}

bool AutoMoveArmUp(int degrees, int time) {
    if(time < 500 || time > 5000) {
        printError();
        return false;
    } else {
        if(degrees > 500) {
            degrees = 500;
        }
        printToScreen("Arm Up");
        ArmMotor.startRotateTo(degrees, rotationUnits::deg, 150, velocityUnits::dps);
        
        task::sleep(time);
        
        ArmMotor.startRotateTo(0, rotationUnits::deg, 0, velocityUnits::dps);
        
        task::sleep(700);
        return true;
    }
}

bool AutoMoveArmDown(int time) {
    if(time < 500 || time > 5000) {
        printError();
        return false;
    } else {
        printToScreen("Arm Down");
        ArmMotor.startRotateTo(-500, rotationUnits::deg, 150, velocityUnits::dps);
        
        task::sleep(time);
        
        ArmMotor.startRotateTo(0, rotationUnits::deg, 0, velocityUnits::dps);
        
        task::sleep(700);
        return true;
    }
}

bool AutoClawOpen(int degrees, int time) {
    if(time < 500 || time > 5000) {
        printError();
        return false;
    } else {
        if(degrees > 190) {
            degrees = 190;
        }
        printToScreen("Claw Opening");
        ClawMotor.startRotateTo(-degrees, rotationUnits::deg, 150, velocityUnits::dps);
        
        task::sleep(time);
        
        ClawMotor.startRotateTo(0, rotationUnits::deg, 0, velocityUnits::dps);
        
        task::sleep(700);
        return true;
    }
}

bool AutoClawClose(int time) {
    if(time < 500 || time > 5000) {
        printError();
        return false;
    } else {
        printToScreen("Claw Closing");
        ClawMotor.startRotateTo(190, rotationUnits::deg, 150, velocityUnits::dps);
        
        task::sleep(time);
        
        ClawMotor.startRotateTo(0, rotationUnits::deg, 0, velocityUnits::dps);
        
        task::sleep(700);
        return true;
    }
}
// END AUTONOMOUS SECTION
