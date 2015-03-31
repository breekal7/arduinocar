#include<AFMotor.h>
#include<NewPing.h>

AF_DCMotor M_Left(4);
AF_DCMotor M_Right(3);

#define SENSOR_TRIG_PIN 14
#define SENSOR_ECHO_PIN 15
#define SENSOR_MIN_DIST 10
#define SENSOR_MAX_DIST 3000


NewPing sonar1(SENSOR_TRIG_PIN, SENSOR_ECHO_PIN, SENSOR_MAX_DIST);
NewPing sonar2(16,17, SENSOR_MAX_DIST);
NewPing sonar3(18, 19, SENSOR_MAX_DIST);
static int i;

void setup() {
	Serial.begin(9600);
        i=0;
        delay(3000);
        M_Left.setSpeed(170);
        M_Right.setSpeed(200); 
        M_Left.run(RELEASE);
        M_Right.run(RELEASE);
}

void loop() {	
	int Left = sonar1.ping_cm();
	int Right = sonar2.ping_cm();
	int Front = sonar3.ping_cm();
	Serial.print("Loop : ");
        Serial.println(i++);
        Serial.print("Left : ");
        Serial.println(Left);
        Serial.print("Right: ");
        Serial.println(Right);
	Serial.print("Front : ");
        Serial.println(Front);

delay(500);
        if(Front > 40){
          
          if( Right > 25){
            if(Left > 25){  
            //move forward
            movForward();  
            }
          }
        }
        else if(Right > 40){
          //turn right
          turnRight();

        }
        else if(Left > 40){
          //turn left
          turnLeft();
      }
        else{
          recheck();
        }

}


void movForward(){          
          M_Left.setSpeed(180);
          M_Right.setSpeed(200);
          
          M_Left.run(FORWARD);
          M_Right.run(FORWARD);
        }


void turnRight(){
          M_Left.run(RELEASE);
          M_Right.run(RELEASE);
          
          M_Left.setSpeed(180);
          M_Right.setSpeed(200);
          
          M_Left.run(FORWARD);
          M_Right.run(BACKWARD);
          delay(300); // do for .3 second
          M_Left.run(RELEASE);
          M_Right.run(RELEASE);
        }

void turnLeft(){
          M_Left.run(RELEASE);
          M_Right.run(RELEASE);
          
          M_Left.setSpeed(180);
          M_Right.setSpeed(200);
          
          M_Left.run(BACKWARD);
          M_Right.run(FORWARD);
          delay(300); // do for .1 second
          M_Left.run(RELEASE);
          M_Right.run(RELEASE);
        }


void recheck(){
          
          M_Left.run(RELEASE);
          M_Right.run(RELEASE);
          
          M_Left.setSpeed(180);
          M_Right.setSpeed(200);
          
          M_Left.run(BACKWARD);
          M_Right.run(BACKWARD);
          delay(500); // do for .5 second
          M_Left.run(RELEASE);
          M_Right.run(RELEASE);
          
          turnRight();
        }
