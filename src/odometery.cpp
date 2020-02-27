//
// Created by Aryan Gajelli on 2020-02-27.
//

#include "odometery.h"
#include "hardware.h"
using namespace hardware;
using namespace hardware::ports;
namespace odometry {
	std::shared_ptr<okapi::OdomChassisController> chassisController;
	std::shared_ptr<XDriveModel> meccanumDrive;
	std::shared_ptr<AsyncMotionProfileController> profileController;
	IterativePosPIDController::Gains dist = { 0.0026, 0.00001, 0, 0.0001 };
	IterativePosPIDController::Gains turn = { 0.0073, 0.00001, 0, 0.00004 };
	IterativePosPIDController::Gains angle = { 0.0026, 0, 0.0001 };

	void initialize() {
		chassisController = ChassisControllerBuilder()
			.withMotors(
				directions::drive::LEFT_FRONT * drive::LEFT_FRONT,
				directions::drive::RIGHT_FRONT * drive::RIGHT_FRONT,
				directions::drive::RIGHT_BACK * drive::RIGHT_BACK,
				directions::drive::LEFT_BACK * drive::LEFT_BACK
			)
			.withSensors(
				{ legacy::LEFT_Y_ENCODER_TOP, legacy::LEFT_Y_ENCODER_BOTTOM, true },
				{ legacy::RIGHT_Y_ENCODER_BOTTOM, legacy::RIGHT_Y_ENCODER_TOP, false },
				{ legacy::X_ENCODER_BOTTOM, legacy::X_ENCODER_TOP, false }
			)
			.withGains(
				dist,
				turn,
				angle
			).withDimensions(
				okapi::AbstractMotor::gearset::green,
				{{
					 4_in * 2,
					 12_in },
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
				std::make_unique<EKFFilter>(EKFFilter(0.0016))
				//std::make_unique<EKFFilter>(EKFFilter(0.0016))
			)
			.withClosedLoopControllerTimeUtil(30, 5, 350_ms)
			.withLogger(
				std::make_shared<Logger>(
					TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
					"/ser/sout", // Output to the PROS terminal
					Logger::LogLevel::debug // Most verbose log level
				)
			)
			.buildOdometry();
		profileController =
			AsyncMotionProfileControllerBuilder()
				.withLimits({1.0, 2.0, 10.0})
				.withOutput(chassisController)
				.buildMotionProfileController();
		meccanumDrive = std::dynamic_pointer_cast<XDriveModel>(chassisController->getModel());
	}

}