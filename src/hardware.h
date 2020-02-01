#ifndef VEXBOT_PORTS_H
#define VEXBOT_PORTS_H
#include "main.h"
/**
 * All robot port definitions
 * */
namespace hardware {
	namespace ports {
		const int VISION_PORT = 5;

		namespace drive {
			const uint8_t LEFT_FRONT = 1;
			const uint8_t LEFT_BACK = 10;
			const uint8_t RIGHT_FRONT = 2;
			const uint8_t RIGHT_BACK = 4;
		}

		namespace transmission {
			const uint8_t BOTTOM = 7;
			const uint8_t TOP = 8;
		}

		namespace intake {
			const uint8_t LEFT = 19;
			const uint8_t RIGHT = 20;
		}

		/**
		 * Legacy Ports (A=1, B=2...)
		 * **/
		namespace legacy {
			const int LEFT_Y_ENCODER_TOP = 5;
			const int LEFT_Y_ENCODER_BOTTOM = 6;
			const int RIGHT_Y_ENCODER_TOP = 7;
			const int RIGHT_Y_ENCODER_BOTTOM = 8;
			const int X_ENCODER_TOP = 1;
			const int X_ENCODER_BOTTOM = 2;
			const int LIFT_POT = 3;
			const int TRAY_POT = 4;
		}
	}

	namespace directions {
		namespace drive {
			const int LEFT_FRONT = 1;
			const int LEFT_BACK = 1;
			const int RIGHT_FRONT = -1;
			const int RIGHT_BACK = -1;
		}

		namespace transmission {
			const int BOTTOM = -1;
			const int TOP = 1;
		}

		namespace intake {
			const int LEFT = 1;
			const int RIGHT = -1;
		}
	}

	namespace gearsetRPM {
		const int RED = 100;
		const int GREEN = 200;
		const int BLUE = 600;
	}
}

#endif
