#include "main.h"
using namespace pros;

Controller controls(E_CONTROLLER_MASTER);
Motor motor2(2, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
Motor motor3(3, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
Motor motor4(4, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
Motor motor5(5, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
Motor motor6(6, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
Motor motor7(7, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
Motor motor8(8, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
Motor motorArray[8] = { motor1, motor2, motor3, motor4, motor5, motor6, motor7, motor8 };

int motorControlXPoints[5] = { 0,120,240,360,480 };
int motorControlYPoints[3] = { 0,120,240 };

bool intBetween(int range1, int checkNum, int range2) {
	return range1 <= checkNum && checkNum <= range2;
}

void printText(std::string displayTextString, int xPos, int yPos) {
	char displayTextArray[displayTextString.size()];
	for (int it = 0; it < displayTextString.size();it++) {
		displayTextArray[it] = displayTextString[it];
	}
	pros::c::screen_print_at(TEXT_SMALL, xPos, yPos, displayTextArray);
}

//bool yeah[8] = { false,false,false,false,false,false, false, false };
int motorSpeedArray[8] = { 20,30,40,50,60,70,80,90 };
struct MotorControl {
	int motorNum;
	Motor motor1(motorNum, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	int x1, x2, y1, y2;
	int YHeight;
	int xButtonPoints[4];
	//make motor and speed top half
	//controls are bottom half
	/*
	| Motor 1: 200RPM |
	| On |  Off | Rev |
	*/
	MotorControl(int tempMotorNum) {
		if (tempMotorNum > 4) {
			x1 = motorControlXPoints[tempMotorNum - 5];
			x2 = motorControlXPoints[tempMotorNum - 4];
			y1 = motorControlYPoints[1];
			y2 = motorControlYPoints[2];
		}
		else {
			x1 = motorControlXPoints[tempMotorNum - 1];
			x2 = motorControlXPoints[tempMotorNum];
			y1 = motorControlYPoints[0];
			y2 = motorControlYPoints[1];
		}
		xButtonPoints[0] = x1;
		xButtonPoints[1] = x1 + ((x2 - x1) / 3);
		xButtonPoints[2] = x1 + (2 * ((x2 - x1) / 3));
		xButtonPoints[3] = x1 + (3 * ((x2 - x1) / 3));
		YHeight = y1 + (3 * (y2 - y1) / 4);
		motorNum = tempMotorNum;
	}
	void updateScreen() {
		//Motor and motor info
		screen::set_pen(COLOR_WHITE);
		screen::draw_rect(x1 + 2, y1, x2 - 2, YHeight - 2);

		printText("M" + std::to_string(motorNum) + ": " + std::to_string(int(motorArray[motorNum - 1].get_position())), x1 + 4, y1 + 4);
		printText("V: " + std::to_string(int(motorArray[motorNum - 1].get_actual_velocity())), x1 + 4, y1 + 20);
		printText("EV: " + std::to_string((motorSpeedArray[motorNum - 1] / 127) * 600), x1 + 4, y1 + 36);
		printText("W: " + std::to_string(float(motorArray[motorNum - 1].get_current_draw()) * 0.001), x1 + 4, y1 + 52);
		printText("T: " + std::to_string(int(motorArray[motorNum - 1].get_temperature())), x1 + 4, y1 + 69);

		screen::set_pen(COLOR_WHITE);
		screen::draw_rect(xButtonPoints[0] + 2, YHeight, xButtonPoints[1] - 2, y2 - 2);
		screen::draw_rect(xButtonPoints[1] + 2, YHeight, xButtonPoints[2] - 2, y2 - 2);
		screen::draw_rect(xButtonPoints[2] + 2, YHeight, xButtonPoints[3] - 2, y2 - 2);

		screen::set_pen(COLOR_GREEN);
		pros::c::screen_print_at(TEXT_SMALL, xButtonPoints[0] + 5, YHeight + 3, "ON");
		screen::set_pen(COLOR_RED);
		pros::c::screen_print_at(TEXT_SMALL, xButtonPoints[1] + 5, YHeight + 3, "OFF");
		screen::set_pen(COLOR_BLUE);
		pros::c::screen_print_at(TEXT_SMALL, xButtonPoints[2] + 5, YHeight + 3, "REV");

		screen::set_pen(COLOR_WHITE);
	}
	int checkButtons(screen_touch_status_s_t status) {
		int statx = status.x;
		int staty = status.y;
		if (intBetween(YHeight, staty, y2 - 2)) {
			if (intBetween(xButtonPoints[0] + 2, statx, xButtonPoints[1] - 2)) {
				motorSpeedArray[motorNum - 1] = 127;
				//yeah[motorNum - 1] = true;
			}
			else if (intBetween(xButtonPoints[1] + 2, statx, xButtonPoints[2] - 2)) {
				motorSpeedArray[motorNum - 1] = 0;
				//yeah[motorNum - 1] = false;
			}
			else if (intBetween(xButtonPoints[2] + 2, statx, xButtonPoints[3] - 2)) {
				motorSpeedArray[motorNum - 1] = -127;
				//yeah[motorNum - 1] = true;
			}
		}
		return motorSpeedArray[motorNum - 1];
	}
};

void initialize() {}
void disabled() {}
void competition_initialize() {}
void autonomous() {}
void opcontrol() {
	MotorControl motorControl1(1);
	MotorControl motorControl2(2);
	MotorControl motorControl3(3);
	MotorControl motorControl4(4);
	MotorControl motorControl5(5);
	MotorControl motorControl6(6);
	MotorControl motorControl7(7);
	MotorControl motorControl8(8);
	MotorControl* motorControlArray[8] = { &motorControl1, &motorControl2, &motorControl3, &motorControl4, &motorControl5, &motorControl6, &motorControl7, &motorControl8 };
	//MotorControl* motorControlArray[8] = { &motorControl1, &motorControl2, &motorControl3, &motorControl4, &motorControl5, &motorControl6, &motorControl7, &motorControl8 };

	screen::set_eraser(COLOR_BLACK);
	screen_touch_status_s_t prevTouchStatus;
	while (true) {
		screen::erase();
		//printText("yeah cool " + std::to_string(touchStatus.x) + ", " + std::to_string(touchStatus.y), 300, 0);
		for (int it = 0;it < 8;it++) {
			(*motorControlArray[it]).updateScreen();
			/*
			if (yeah[it]) {
				screen::draw_rect(100, 100, 200, 100 * curMotorControl.motorNum);
				pros::c::screen_print_at(TEXT_MEDIUM, 50 * curMotorControl.motorNum, 200, "YEAHY!!!!!!");
			}*/
		}
		screen_touch_status_s_t curTouchStatus;
		prevTouchStatus = c::screen_touch_status();
		if (curTouchStatus.x != prevTouchStatus.x && curTouchStatus.y != prevTouchStatus.y) {
			for (int it = 0;it < 8;it++) {
				if (intBetween(-10, motorArray[it].get_position(), 600)) {
					curTouchStatus = c::screen_touch_status();
					motorArray[it] = (*motorControlArray[it]).checkButtons(curTouchStatus);
				}
			}
			delay(60);
		}
	}
}
