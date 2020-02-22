#include "main.h"
#include "globals.h"

using namespace hardware;
using namespace hardware::ports;
using namespace mechanisms;
std::shared_ptr<OdomChassisController> chassisController;
std::shared_ptr<XDriveModel> meccanumDrive;

std::shared_ptr<AsyncMotionProfileController> profileController;
Controller master;
ADIEncoder leftEncoder(legacy::LEFT_Y_ENCODER_TOP, legacy::LEFT_Y_ENCODER_BOTTOM,true);
ADIEncoder rightEncoder(legacy::RIGHT_Y_ENCODER_BOTTOM, legacy::RIGHT_Y_ENCODER_TOP, false);
ADIEncoder centerEncoder(legacy::X_ENCODER_BOTTOM, legacy::X_ENCODER_TOP, false);

/**
 * Builds the chassisController
 */
void initializeDrive() {
    IterativePosPIDController::Gains distanceGains;
    distanceGains.kP = 0.0026;
    distanceGains.kI = 0.00001;
    distanceGains.kD = 0.000;
    distanceGains.kBias = 0.0001;

    IterativePosPIDController::Gains turnGains;
    turnGains.kP = 0.0073;
    turnGains.kI = 0.00001;
    turnGains.kD = 0.000;
    turnGains.kBias = 0.00004;


    IterativePosPIDController::Gains angleGains;
    angleGains.kP = 0.0026;
    angleGains.kI = 0;
    angleGains.kD = 0.0001;

    chassisController = ChassisControllerBuilder()
            .withMotors(

                    directions::drive::LEFT_FRONT * drive::LEFT_FRONT,
                    directions::drive::RIGHT_FRONT * drive::RIGHT_FRONT,
                    directions::drive::RIGHT_BACK * drive::RIGHT_BACK,
                    directions::drive::LEFT_BACK * drive::LEFT_BACK
            )
            .withSensors(
                    leftEncoder,
                    rightEncoder,
                    centerEncoder
            )
            .withGains(
                    distanceGains,
                    turnGains,
                    angleGains
            ).withDimensions(
                    okapi::AbstractMotor::gearset::green,
                    {{
                             4_in * 2,
                             12_in},
                     okapi::imev5GreenTPR
                    })
            .withOdometry(
                    {
                            //dimensions and layout of encoders
                            {
                                    3.25_in,    //encoder wheel diameter
                                    12_in,      //center to center dist. of l and R encoders
                                    0.359_in,       //dist. between middle encoder and center of bot
                                    3.25_in     //middle encoder wheel diameter
                            },
                            quadEncoderTPR    //ticks per rotation of encoder
                    },
                    StateMode::CARTESIAN
            )
            .withDerivativeFilters(
                    std::make_unique<EKFFilter>(EKFFilter(0.0016)),
                    std::make_unique<EKFFilter>(EKFFilter(0.0016))
            )
            .withClosedLoopControllerTimeUtil(30,5,350_ms)
            .withLogger(
                    std::make_shared<Logger>(
                            TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
                            "/ser/sout", // Output to the PROS terminal
                            Logger::LogLevel::debug // Most verbose log level
                    )
            )
            .buildOdometry();
    meccanumDrive = std::dynamic_pointer_cast<XDriveModel>(chassisController->getModel());
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    initializeDrive();
    chassisController->setMaxVelocity(180);
    mechanisms::initialize();
    Logger::setDefaultLogger(std::make_shared<Logger>(
            TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
            "/ser/sout", // Output to the PROS terminal
            Logger::LogLevel::debug // Most verbose log level
    ));
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
}
