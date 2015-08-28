
#include "Arduino.h"
#include <Adafruit_MotorShield.h>

#define MOTOR_COUNT = 4;
#define MOTORS_PER_SKID = 2;


class Pilot {

	private:

		enum Wheels{
			LEFT_FRONT = 0,
			LEFT_REAR = 1,
			RIGHT_FRONT = 2,
			RIGHT_REAR = 3
		}

		class Skid{

			private: 

				Adafruit_DCMotor *frontMotor;
				Adafruit_DCMotor *rearMotor;

			public:

				Skid(Adafruit_DCMotor *_frontMotor, 
					Adafruit_DCMotor *_rearMotor);

				void run(Speed _speed);

		};

		Adafruit_MotorShield AFMS;

		Adafruit_DCMotor *motors[MOTOR_COUNT];
		Adafruit_DCMotor *portSkid[MOTORS_PER_SKID];
		Adafruit_DCMotor *starboardSkid[MOTORS_PER_SKID];

		Speed currentSpeed = Speed.STOP;
		Direction currentDirection = Direction.AHEAD;
		Side currentYaw = Yaw.CENTER;

	public:

		Pilot();

		enum Speed {
			FULL = 255,
			HALF = 128,
			SLOW = 64,
			DEAD_SLOW = 32,
			STOP = 0,
			REV_DEAD_SLOW = -32,
			REV_SLOW = -64,
			REV_HALF = -128,
			REV_FULL = -255
		};

		enum Direction {
			AHEAD = 1,
			ASTERN = 2,
			BREAK = 3,
			RELEASE = 4,			
		}

		enum Yaw {
			PORT = 0,
			CENTER = 1,
			STARBOARD = 2
		}

		void stop();
		void throttle(Speed _speed);
		void run(Direction _direction);
		void turn(Side _side);

		/*
		* Implement later for finer control 
		*
		int powerPortMotor(Speed speed);
		int powerStarboardMotor(Speed speed);
		int powerAhead(Speed speed);
		int powerAstern(Speed speed);
		*
		*/

};
