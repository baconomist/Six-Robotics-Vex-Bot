//
// Created by Lucas on 9/27/2019.
//

#include <float.h>
#include "main.h"
#include "../components/drive.h"
#include "../robot.h"
#include "../motors.h"
#include "auton.h"
#include "../ports.h"
#include "../../utils/math.h"
#include "PID.h"

using namespace math;

float Auton::expectedLPos = 0;
float Auton::expectedRPos = 0;
float Auton::expectedDistance = 0;
float Auton::expectedHeadingDeg = 0;

P *Auton::currentMoveAlgorithm = nullptr;
pros::ADIEncoder *Auton::leftEncoder = nullptr;
pros::ADIEncoder *Auton::rightEncoder = nullptr;
pros::ADIEncoder *Auton::centerEncoder = nullptr;

float Auton::x_position = 0;
float Auton::y_position = 0;
float Auton::heading_deg = 0;
ActionQueue *Auton::actionQueue = nullptr;

void Auton::initialize()
{
    // TODO: fix ports
    leftEncoder = new ADIEncoder(LEFT_X_ENCODER_TOP, LEFT_X_ENCODER_BOTTOM, false);
    rightEncoder = new ADIEncoder(RIGHT_X_ENCODER_TOP, RIGHT_X_ENCODER_BOTTOM, false);
    centerEncoder = new ADIEncoder(Y_ENCODER_TOP, Y_ENCODER_BOTTOM, false);
    actionQueue = new ActionQueue();
}

void Auton::update()
{
    actionQueue->update();
    if (currentMoveAlgorithm != nullptr)
    {
        if (!currentMoveAlgorithm->finished())
            currentMoveAlgorithm->update();
        else
        {
            Drive::stop();
            reset_encoders();
        }
    }
}

float Auton::calculate_rotation_from_motion()
{
    // Distance from robot center to arc center
    float arc_length = 0;

    // Distance from center of robot to corresponding side
    float s_r = Robot::WHEEL_TO_CENTER_DIST;
    float s_l = Robot::WHEEL_TO_CENTER_DIST;

    // Distances/radii from center of arc to respective sides of robot
    float r_left = arc_length + s_l;
    float r_right = arc_length - s_r;

    // 2pi * d/360d * radius = radians * radius = arc length

    float delta_theta = (Auton::get_l_pos() * TTI - Auton::get_r_pos() * TTI) / (s_l + s_r);

    return delta_theta;
}

float Auton::calculate_delta_x_from_motion()
{
    return TTI * (cos(heading_deg * DEG2RAD) * get_l_pos());
}

float Auton::calculate_delta_y_from_motion()
{
    return TTI * (sin(heading_deg * DEG2RAD) * get_l_pos());
}

float Auton::get_l_pos()
{
    return driveLF->get_position();
}

float Auton::get_r_pos()
{
    return driveRF->get_position();
}

void Auton::goto_pos(float target_x, float target_y)
{
    float x_diff = target_x - x_position;
    float y_diff = target_y - y_position;

    float distance = (float) sqrt(x_diff * x_diff + y_diff * y_diff);

    // Turn to match heading
    goto_heading((float) atan(x_diff / (y_diff == 0 ? 1 : y_diff)) * RAD2DEG);
    Auton::x_position = target_x;
    Auton::y_position = target_y;

    x_pos_before_action_start = x_position;
    y_pos_before_action_start = y_position;

    // Move to point
    actionQueue->queue_action(new AutonAction([](AutonAction *autonAction) {
        expectedDistance = autonAction->distance;
        expectedLPos = autonAction->distance * ITT;
        expectedRPos = expectedLPos;

        Auton::set_algorithm(new P(Auton::kP_straight, get_l_pos, autonAction->distance * ITT, [](float speed) {
            Auton::x_position = x_pos_before_action_start + calculate_delta_x_from_motion();
            Auton::y_position = y_pos_before_action_start + calculate_delta_y_from_motion();

            Drive::move_straight(speed);
        }));
    }, [] { return Auton::currentMoveAlgorithm->finished(); }, distance));


}

void Auton::goto_pos(float target_x, float target_y, float final_heading_degrees)
{
    goto_pos(target_x, target_y);

    goto_heading(final_heading_degrees);
}

float heading_direction = 1;

void Auton::goto_heading(float heading_degrees)
{
    heading_deg_before_action_start = Auton::heading_deg;

    actionQueue->queue_action(
            new AutonAction([](AutonAction *autonAction) {
                                expectedHeadingDeg = autonAction->heading;

                                float turn_distance = Robot::WHEEL_TO_CENTER_DIST * autonAction->heading * DEG2RAD;

                                heading_direction = (autonAction->heading > 0 ? 1 : -1);
                                Auton::set_algorithm(new P(Auton::kP_straight, get_l_pos, turn_distance * ITT, [](float speed) {
                                    Auton::heading_deg = heading_deg_before_action_start + calculate_rotation_from_motion() * RAD2DEG;
                                    Drive::turn(speed * heading_direction);
                                }));
                            },
                            [] { return Auton::currentMoveAlgorithm->finished(); }, 0, heading_degrees));

}

void Auton::register_action_complete_callback(void (*callback)())
{
    action_complete_callback = callback;
}

void Auton::reset_encoders()
{
    driveLF->tare_position();
    driveRF->tare_position();
    driveLB->tare_position();
    driveRB->tare_position();
}

void Auton::print_debug()
{
    pros::lcd::print(1, "EL: %f, AL: %f", expectedLPos, get_l_pos());
    pros::lcd::print(2, "ER: %f, AR: %f", expectedRPos, get_r_pos());
    pros::lcd::print(3, "ED: %f, AD: %f", expectedDistance, get_l_pos() * TTI);
    pros::lcd::print(4, "EH: %f, AH: %f", expectedHeadingDeg, calculate_rotation_from_motion() * RAD2DEG);
    pros::lcd::print(5, "X: %f, Y: %f", x_position, y_position);
    pros::lcd::print(6, "Heading: %f", heading_deg);
    pros::lcd::print(7, "Finished: %d", currentMoveAlgorithm->finished());
}

void Auton::set_algorithm(P *algorithm)
{
    currentMoveAlgorithm = algorithm;
    reset_encoders();
}


AutonAction::AutonAction(void (*execute_func)(AutonAction *), bool (*finished_func)(), float distance,
                         float heading)
{
    this->execute_func = execute_func;
    this->finished_func = finished_func;
    this->distance = distance;
    this->heading = heading;
}

void AutonAction::execute()
{
    this->execute_func(this);
}

bool AutonAction::finished()
{
    return this->finished_func();
}
