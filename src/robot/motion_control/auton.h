//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_MOTION_TRACKER_H
#define VEXROBOT_MOTION_TRACKER_H

#include "main.h"
#include "PID.h"
#include "action_queue.h"

class AutonAction : public QueueableAction
{
public:
    float distance = 0;
    float heading = 0;

    AutonAction(void (*execute_func)(AutonAction*), bool(*finished_func)(),
            float distance = 0, float heading = 0);

    virtual void execute() override;

    virtual bool finished() override;

private:
    void (*execute_func)(AutonAction*);
    bool (*finished_func)();

};

class Auton
{
public:
    static float x;
    static float y;
    static float heading;

    static float expectedLPos;
    static float expectedRPos;
    static float expectedDistance;
    static float expectedHeadingDeg;

    static constexpr const float kP = 0.5f;

    static void (*action_complete_callback)();

    static P *currentMoveAlgorithm;

    static ADIEncoder *leftEncoder;
    static ADIEncoder *rightEncoder;
    static ADIEncoder *centerEncoder;

    static void initialize();

    static void update();

    static void goto_pos(float x, float y);

    static void goto_pos(float x, float y, float final_heading);

    static float get_x();

    static float get_y();

    static void goto_heading(float heading_degrees);

    static float get_heading();

    static void register_action_complete_callback(void (*callback)());

    static void print_debug();

private:
    static ActionQueue *actionQueue;

    static void reset_encoders();

    static float calculate_rotation_from_motion();

    static float get_l_pos();

    static float get_r_pos();

    static void set_algorithm(P* algorithm);
};

#endif //VEXROBOT_MOTION_TRACKER_H
