//
// Created by Lucas on 1/29/2020.
//
#include "main.h"
#include "vision.h"
#include "stdlib.h"

using namespace pros;

/* At 1m:
 * w 36px h 34px
 * x 156px y 124px
 * */

void test_vision() {

    vision_object_s_t object;
    float distance_to_robot_edge = 0;
    float y = 0;
    float fov_in = 0; // To be calculated using cube_px_width_in_view / cube_px_width_1m_away
    float d = (fov_in / 400) * y + distance_to_robot_edge;

    float timer = millis();
    float average_time = 1000; // 5 sec
    float average_total;
    int average_count = 0;

    float values[999];

    pros::Vision vision_sensor(15);

    while (true) {

        std::cout << vision_sensor.get_by_size(1).width << "\n";

        float x = vision_sensor.get_by_sig(0, 3).width;
        average_total += 36 / x;
        values[average_count] = 36 / x;
        average_count++;

        if (millis() - timer >= average_time) {
            std::cout << "The average is: " << average_total / average_count << " "
                      << *std::max_element(values, values + 999) << "\n";
            timer = millis();
            average_total = 0;
            average_count = 0;
            memset(values, 0, sizeof values);
        }

        // arcade();
        // transmission();
        object = vision_sensor.get_by_sig(0, 1);
        //std::cout << object.width << "\n";
        delay(50);
    }
}