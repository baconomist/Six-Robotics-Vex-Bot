
#include <algorithm>
#include <math.h>
#include "main.h"
#include "robot/motors.h"
#include "motor_gearsets.h"
#include "misc.h"
#include "encoders.h"

/*

// Colors in order from top-bottom orange, purple, green
#define ORANGE_SIG 1
#define PURPLE_SIG 2
#define GREEN_SIG 3


float xPosition, yPosition;
void findPosition()
{
  float wheelDiameter = 3;
  // Distance the bot moves per degree of tracking wheel turn
  float distPerDegree = (wheelDiameter * M_PI) / 360;
  // Average of the two X tracking wheels
  int xRotation = (RightXEncoder.get_value() + LeftXEncoder.get_value()) / 2;
  int yRotation = YEncoder.get_value();
  xPosition = distPerDegree * xRotation;
  yPosition = distPerDegree * yRotation;
}

/* At 1m:
 * w 36px h 34px
 * x 156px y 124px
 *

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
            // std::cout << "The average is: " << average_total / average_count << " " << *max_element(values, values + 999) << "\n";
            timer = millis();
            average_total = 0;
            average_count = 0;
            memset(values, 0, sizeof values);
        }
        std::cout << "encoder  " << LeftXEncoder.get_value() << "\n";
        arcade();
        // transmission();
        // object = vision_sensor.get_by_sig(0, 2);
        //std::cout << object.width << "\n";
        delay(50);
    }
}

*/