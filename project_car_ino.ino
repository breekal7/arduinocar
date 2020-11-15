#define TRIG1 14
#define ECHO1 15
#define TRIG2 16
#define ECHO2 17
#define TRIG3 18
#define ECHO3 19
#define SONAR_MIN_DIST 10
#define SONAR_MAX_DIST 300

#include<AFMotor.h>
AF_DCMotor M_Left(4);
AF_DCMotor M_Right(3);

#include<NewPing.h>
NewPing sonar1(TRIG1, ECHO1, SONAR_MAX_DIST);
NewPing sonar2(TRIG2, ECHO2, SONAR_MAX_DIST);
NewPing sonar3(TRIG3, ECHO3, SONAR_MAX_DIST);

void setup(){
    Serial.begin(9600);
    delay(3000);
    M_Left.setSpeed(170);
    M_Right.setSpeed(200); 
    M_Left.run(RELEASE);
    M_Right.run(RELEASE);
}

void loop(){
    static int i = 0;
    int Left = sonar1.ping_cm();
    int Right = sonar2.ping_cm();
    int Front = sonar3.ping_cm();
    Serial.print("Loop: ");
    Serial.println(i++);
    Serial.print("Left: ");
    Serial.println(Left);
    Serial.print("Right: ");
    Serial.println(Right);
    Serial.print("Front : ");
    Serial.println(Front);
    delay(500);
    if(Front > 40){
        if(Right > 25){
            if(Left > 25){
                movForward();  
            }
            else{
                turnLeft();
            }
        }
        else{
            turnRight();
        }
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
