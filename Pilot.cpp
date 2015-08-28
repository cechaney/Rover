#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include "Pilot.h"

class Pilot {

	public:

		Pilot::Pilot(){

			AFMS = Adafruit_MotorShield(); 

			motors[Wheels.LEFT_FRONT] = AFMS.getMotor(Wheels.LEFT_FRONT);
			motors[Wheels.LEFT_REAR] = AFMS.getMotor(Wheels.LEFT_REAR);
			motors[Wheels.RIGHT_FRONT] = AFMS.getMotor(Wheels.RIGHT_FRONT);
			motors[Wheels.RIGHT_REAR] = AFMS.getMotor(Wheels.RIGHT_REAR);

			portSkid = new Skid(
				motors[Wheels.LEFT_FRONT], 
				motors[Wheels.LEFT_REAR], 
				Side.PORT, 
				Direction.RELEASE, 
				Speed.STOP);

			starboardSkid = new Skid(
				motors[Wheels.RIGHT_FRONT], 
				motors[Wheels.RIGHT_REAR], 
				Side.STARBOARD, 
				Direction.RELEASE, 
				Speed.STOP);

		}

		Pilot::Skid(
			Adafruit_DCMotor *_frontMotor, 
			Adafruit_DCMotor *_rearMotor){

			frontMotor = _frontMotor;
			rearMotor = _rearMotor;

		}

		Pilot::Skid::run(Speed _speed){

			frontMotor->run(Direction.RELEASE);
			rearMotor->run(Direction.RELEASE);

			if(_speed == Speed.STOP){

				frontMotor->setSpeed(Speed.STOP);
				rearMotor->setSpeed(Speed.STOP);

				return;
			}

			if(_speed > Speed.STOP){
				
				frontMotor->setSpeed(_speed);
				rearMotor->setSpeed(_speed);
				
				frontMotor->run(Direction.AHEAD);
				rearMotor->run(Direction.AHEAD);

				return;

			}

			if(_speed < Speed.STOP){
				
				frontMotor->setSpeed(abs(_speed));
				rearMotor->setSpeed(abs(_speed));
				
				frontMotor->run(Direction.ASTERN);
				rearMotor->run(Direction.ASTERN);

				return;

			}			

			frontMotor->setSpeed(_speed);
			rearMotor->setSpeed(_speed);			

			frontMotor->run(_direction);
			rearMotor->run(_direction);

		}

		Pilot::Skid::stop(){
			run(Speed.STOP);
		}

		Pilot::stop(){

			this->currentSpeed = Speed.STOP;
			portSkid->stop();
			starboardSkid->stop();

		}

		Pilot::run(Direction _direction){

			this->currentDirection = _direction;

			if(Speed.STOP == this->currentSpeed){
				return;
			}

			switch(_direction){

				case Direction.AHEAD:

					portSkid->run(Direction.AHEAD, currentSpeed);
					starboardSkid->run(Direction.AHEAD, currentSpeed);

					break;

				case Direction.ASTERN:

					portSkid->run(Direction.ASTERN, currentSpeed);
					starboardSkid->run(Direction.ASTERN, currentSpeed);				

					break;
			}

			return;

		}

		Pilot::turn(Yaw _yaw){

			this->currentYaw = _yaw;

			if(Speed.STOP == this->currentSpeed){
				return;
			}			

			switch(_yaw){

				case Side.PORT:

					portSkid->run(Direction.ASTERN, currentSpeed);
					starboardSkid->run(Direction.AHEAD, currentSpeed);

					break;

				case Side.STARBOARD;

					portSkid->run(Direction.AHEAD, currentSpeed);
					starboardSkid->run(Direction.ASTERN, currentSpeed);				

					break;
			}

			return;


		}		
};