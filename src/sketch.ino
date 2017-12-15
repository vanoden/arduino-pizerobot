// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor* motor[4];
Adafruit_DCMotor *motor0 = AFMS.getMotor(1);
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);
Adafruit_DCMotor *motor2 = AFMS.getMotor(3);
Adafruit_DCMotor *motor3 = AFMS.getMotor(4);

int motor_select = 1;
int motor_speed[4];

void setup() {
  Serial.begin(19200);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

	motor[0] = motor0;
	motor[1] = motor1;
	motor[2] = motor2;
	motor[3] = motor3;

	for (int i = 0; i <= 3; i ++) {
		//motor_init(i);
	}
}

int speed = 0;
void loop() {
	char incomingByte;
	if (Serial.available() > 0) {
		incomingByte = Serial.read();
		if (incomingByte - '0' >= 1 && incomingByte - '0' <= 4) {
			motor_select = incomingByte - '0' + 1;
		}
	
		if (incomingByte == 'w') {
			motor[motor_select]->run(FORWARD);
			motor_speed[motor_select] += 20;
		}
		if (incomingByte == 's') {
			motor[motor_select]->run(FORWARD);
			motor_speed[motor_select] = 0;
		}
		Serial.write("Motor ");
		Serial.print(motor_select);
		Serial.write("Speed: ");
		Serial.println(motor_speed[motor_select]);
		
		//motor[motor_select]->setSpeed(motor_speed[motor_select]);
	}
}

void motor_init(int motorid) {
		motor[motorid]->setSpeed(0);
		motor[motorid]->run(RELEASE);
}