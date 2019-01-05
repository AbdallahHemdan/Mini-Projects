/*					Arduino Obstacle Avoiding Robot
		with a servo motor and an ultrasonic sensor HC-SR04
							LED and buzzer            */


//Libraries
#include <Servo.h> 
#include "Ultrasonic.h"

//Constants
const int button = 2;		  //Button pin to pin 2
const int led 	 = 3;		  //Led pin (throught resistor) to pin 3
const int buzzer = 4;		  //Buzzer pin to pin 4
const int motorA1= 6;		  //motor A positive (+) pin to pin 6 (PWM) (from L298 module!)
const int motorA2= 9;         //motor A negative (-) pin to pin 9 (PWM)
const int motorB1=10;		  //motor B positive (+) pin to pin 10 (PWM)
const int motorB2=11;		  //motor B negative (-) pin to pin 11 (PWM)

Ultrasonic ultrasonic(A4 ,A5); //Create Ultrsonic object ultrasonic(trig pin,echo pin)
Servo myservo;  			  //Create Servo object to control a servo

//Variables
int distance;				  //Variable to store distance from an object
int checkRight;
int checkLeft;
int function=0;				  //Variable to store function of robot: '1' running or '0' stoped. By default is stoped
int buttonState=0;            //Variable to store the state of the button. By default '0'
int pos=90;    				  //Variable to store the servo position. By default 90 degrees - sensor will 'look' forward
int flag=0;					  //Useful flag to keep the button state when button is released 


void setup()
{
    myservo.attach(5);  	   		//Servo pin connected to pin 5
    myservo.write(pos);        	// tell servo to go to position in variable 'pos' 
	pinMode(button, INPUT_PULLUP);
	pinMode(led, 	OUTPUT);
	pinMode(buzzer, OUTPUT);
	pinMode(motorA1,OUTPUT);
	pinMode(motorA2,OUTPUT);
	pinMode(motorB1,OUTPUT);
	pinMode(motorB2,OUTPUT);
	
}

void loop()
{
	//Check button state
	buttonState = digitalRead(button);
	unsigned long currentMillis = millis(); //counting...

	//Change main function (stoped/running) when button is pressed 
  	if (buttonState == LOW) {//If button is pressed once...
  		delay(500);
    	if ( flag == 0){
      		function = 1;
        	flag=1; //change flag variable
    	}
    	else if ( flag == 1){	 //If button is pressed twice
    		function = 0;
	    	flag=0; //change flag variable again 
    	}    
  	}
  	
	if (function == 0){ 	//If button is unpressed or pressed twice then:
		myservo.write(90);  	//set servo 90 degress - sensor will look forward
		stop();					//robot remain stoped
		noTone(buzzer);			//buzzer off
		digitalWrite(led, HIGH);// and led on
		
	}
	else if (function == 1){//If button is pressed then:
		//Read distance...
		distance = ultrasonic.Ranging(CM); //Tip: Use 'CM' for centimeters or 'INC' for inches
		//Check for objects...
		if (distance > 10){
			forward(); //All clear, move forward!
			noTone(buzzer);
			digitalWrite(led,LOW);
		}
		else if (distance <=10){
			stop(); //Object detected! Stop the robot and check left and right for the better way out!
			tone(buzzer,500); // play a tone
			digitalWrite(led,HIGH); // turn the led on
			//Start scanning... 
			for(pos = 0; pos < 180; pos += 1){  //goes from 0 degrees to 180 degrees 
                myservo.write(pos);             //tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position 
            } 
            
            checkLeft = ultrasonic.Ranging(CM);		//Take distance from the left side
            
            for(pos = 180; pos>=0; pos-=1){     //goes from 180 degrees to 0 degrees                           
                myservo.write(pos);             //tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position   
            }
            
            checkRight= ultrasonic.Ranging(CM);
            
            myservo.write(90);                   // Sensor "look" forward again
            
            //Finally, take the right decision, turn left or right?
            if (checkLeft < checkRight){
            	left();
            	delay(400); // delay, change value if necessary to make robot turn.            
            	}
            else if (checkLeft > checkRight){
            	right();
            	delay(400); // delay, change value if necessary to make robot turn.
            }
            else if (checkLeft <=10 && checkRight <=10){
            	backward(); //The road is closed... go back and then left ;)
            	left();
            }
		}
	}

}


void forward(){
	digitalWrite(motorA1, HIGH);
	digitalWrite(motorA2, LOW);
	digitalWrite(motorB1, HIGH);
	digitalWrite(motorB2, LOW);	
}

void backward(){
	digitalWrite(motorA1, LOW);
	digitalWrite(motorA2, HIGH);
	digitalWrite(motorB1, LOW);
	digitalWrite(motorB2, HIGH);
}

void left(){
	digitalWrite(motorA1, HIGH);
	digitalWrite(motorA2, LOW);
	digitalWrite(motorB1, LOW);
	digitalWrite(motorB2, HIGH);
}

void right(){
	digitalWrite(motorA1, LOW);
	digitalWrite(motorA2, HIGH);
	digitalWrite(motorB1, HIGH);
	digitalWrite(motorB2, LOW);	
}

void stop(){
	digitalWrite(motorA1, LOW);
	digitalWrite(motorA2, LOW);
	digitalWrite(motorB1, LOW);
	digitalWrite(motorB2, LOW);
}


