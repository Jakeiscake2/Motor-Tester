#include "main.h"
#include "lemlib\api.hpp"

using namespace std;
using namespace pros;

Controller controls(E_CONTROLLER_MASTER);

Motor flywheel1(19, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor flywheel2(20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

void initialize(){
	lcd::initialize();
	pros::lcd::set_text(1, "Program running");
}

string statuss = "none";


screen_touch_status_s_t status;
bool status_checker(int x1, int x2, int y1, int y2){
	if (status.x >= x1 && status.x <= x2 && status.y >= y1 && status.y <= y2)
	{
		return true;
	}
	return false;
}
void auton_selector(){
	screen::set_eraser(COLOR_BLACK);
  status.x = 2;
	while (true){
		if (status.x != c::screen_touch_status().x && status.y != c::screen_touch_status().y){
			screen::erase();
			status = c::screen_touch_status();
			screen::set_pen(COLOR_RED);
			screen::draw_rect(0, 0, 100, 50);
			pros::c::screen_print_at(TEXT_LARGE, 10, 10, "On");
			pros::c::screen_print_at(TEXT_LARGE, 10, 30, "19",flywheel1.get_actual_velocity());
			screen::set_pen(COLOR_BLUE);
			pros::c::screen_print_at(TEXT_LARGE, 400, 10, "Off");
			pros::c::screen_print_at(TEXT_LARGE, 10, 30, "20",flywheel2.get_actual_velocity());
			screen::draw_rect(380, 0, 480, 50);
			if (status_checker(0,100,0,50)){
		    statuss = "on";
			}
			else if (status_checker(380,480,0,50)){
				statuss = "off";
      }              
			screen::set_pen(COLOR_WHITE);
			if (statuss == "on"){
        c::screen_print_at(TEXT_LARGE, 100, 10,"selected ON");
        flywheel1 = 127;
        flywheel2=127;
			}
			else if (statuss == "off"){
        c::screen_print_at(TEXT_LARGE, 100, 10,"selected OFF");
        flywheel1 = 0;
        flywheel2=0;
			}
	  }
  }
}

void disabled() {}
void competition_initialize() {}
void autonomous() {}
void opcontrol(){
  
	auton_selector();
	// vision_object_s_t goal = vision_sensor.get_by_size(0);
  
  int x=0,y=0;
	while (true){
		controls.set_text(0, 0, "How did we get here?");

        }
}
