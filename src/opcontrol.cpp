
#include <algorithm>
#include "main.h"
#include "headers/motors.h"
#include "headers/controllers.h"
#include "headers/motor_gearsets.h"

#define VISION_PORT 1
// Colors in order from top-bottom orange, purple, green
#define ORANGE_SIG 1
#define PURPLE_SIG 2
#define GREEN_SIG 3

using namespace std;
void tank()
{
    int deadZone = 15;
    int velLY = master.get_analog(ANALOG_LEFT_Y);
    int strafe = 90 * (master.get_digital(DIGITAL_RIGHT) - master.get_digital(DIGITAL_LEFT));
    int velRY = master.get_analog(ANALOG_RIGHT_Y);

    driveLB.move_velocity(velLY - strafe);
    driveLF.move_velocity(velLY + strafe);
    driveRB.move_velocity(velRY - strafe);
    driveRF.move_velocity(velRY + strafe);
}

void arcade(){
    /*
    arcade joystick control + strafe
    */
    int deadZone = 15;//motors wont move if abs(joystick) is within this range
    int velLY = master.get_analog(ANALOG_LEFT_Y) * get_gearset_rpm(driveLB.get_gearing()) / 127;//scaling the values to 200 to match the internal gearset for move_velocity
    int velRY = master.get_analog(ANALOG_RIGHT_Y) * get_gearset_rpm(driveRB.get_gearing()) / 127;//^^
    int velLX = master.get_analog(ANALOG_LEFT_X) * get_gearset_rpm(driveLB.get_gearing()) / 127;//^^
    int velRX = master.get_analog(ANALOG_RIGHT_X) * get_gearset_rpm(driveRB.get_gearing()) / 127;//^^


    if (abs(velLX) < deadZone && abs(velLY) > deadZone)
    {
        //drives straight if the Y dir is greater than dead zone and X dir is within dead zone
        driveLF.move_velocity(velLY + velRX);
        driveLB.move_velocity(velLY - velRX);
        driveRF.move_velocity(velLY - velRX);
        driveRB.move_velocity(velLY + velRX);
    } else if (abs(velLY) < deadZone && abs(velLX) > deadZone)
    {
        //turns on point if the X dir is greater than dead zone and Y dir is within dead zone
        driveLF.move_velocity(velLX + velRX);
        driveLB.move_velocity(velLX - velRX);
        driveRF.move_velocity(-velLX - velRX);
        driveRB.move_velocity(-velLX + velRX);
    } else
    {
        //arcade control + strafe
        driveLF.move_velocity(velLY - velLX + velRX);
        driveLB.move_velocity(velLY - velLX - velRX);
        driveRF.move_velocity(velLY + velLX - velRX);
        driveRB.move_velocity(velLY + velLX + velRX);
    }
}

void transmission()
{
    /*
    uses 2 motors to control lift + tray
    tray = transB(hold) and transT(+- power)
    lift = transB(+-power) and transT(-+ power)
    */
    int tilt = 100 * (master.get_digital(DIGITAL_R1) - master.get_digital(
            DIGITAL_R2));//sets tilit speed to 50 * the direction, scaled to match internal gearset
    int lift = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(
            DIGITAL_L2));//sets lift speed to 100 * the direction, scaled to match internal gearset
    if (tilt)
    {
        //moves the tray forwards and backwards
        transB.move_velocity(0);//uses motor brake(hold) to prevent motor from turning
        transT.move_velocity(-tilt);//rotates about transB
    } else if (lift)
    {
        //moves lift
        transB.move_velocity(-lift);
        transT.move_velocity(lift);
    } else
    {
        //holds the motors in the current postion
        transB.move_velocity(0);
        transT.move_velocity(0);
    }
}

/* At 1m:
 * w 36px h 34px
 * x 156px y 124px
 * */

vision_object_s_t object;
void opcontrol()
{
    float distance_to_robot_edge = 0;
    float y= 0;
    float fov_in = 0; // To be calculated using cube_px_width_in_view / cube_px_width_1m_away
    float d = (fov_in / 400)*y + distance_to_robot_edge;

    float timer = millis();
    float average_time = 1000; // 5 sec
    float average_total;
    int average_count = 0;

    float values[999];

    pros::Vision vision_sensor(VISION_PORT);
    while (true)
    {
        float x = vision_sensor.get_by_sig(0, 3).width;
        average_total +=  36 / x;
        values[average_count] = 36 / x;
        average_count ++;

        if(millis() - timer >= average_time)
        {
            std::cout << "The average is: " << average_total / average_count << " " << *max_element(values, values + 999) << "\n";
            timer = millis();
            average_total = 0;
            average_count = 0;
            memset(values, 0, sizeof values);
        }

       // arcade();
       // transmission();
       object = vision_sensor.get_by_sig(0, 2);
       //std::cout << object.width << "\n";
       delay(50);
    }
}
