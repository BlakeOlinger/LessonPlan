#include "robot-config.h"

          

int main() {
    int speedMove = 100;
    int speedTurn = 100;
    
    while(OnOff) {
        
     ControllerDriveForward(speedMove);
        
     ControllerDriveBackward(speedMove);
        
        
        ControllerTurnLeft(speedTurn);

        ControllerTurnRight(speedTurn);

        ControllerMoveArmUp();

        ControllerMoveArmDown();

        ControllerClawOpen();

        ControllerClawClose();
        
        if(ConOne.ButtonY.pressing()) {
            if(speedMove > 100 && (speedMove - 50) > 99) {
                printToScreen("Slow Down");
                speedMove -= 50;
                speedTurn -= 25;
            } else {
                printToScreen("At Minimum Speed");
            }
        }
       
        if(ConOne.ButtonX.pressing()) {
            if(speedMove < 500 ) {
                printToScreen("Speed Up");
                speedMove += 50;
                speedTurn += 25;
            } else {
                printToScreen("At Max Speed");
            }
        }
        
        task::sleep(100);
    }
}
