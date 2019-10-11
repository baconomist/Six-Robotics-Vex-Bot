//
// Created by Lucas on 9/27/2019.
//

#include "robot/robot.h"
#include <stdarg.h>

extern "C" {
	int32_t  vex_vsnprintf( char *out, uint32_t max_len, const char *format, va_list args );
	void     vexDisplayPrintf( int32_t xpos, int32_t ypos, uint32_t bOpaque, const char *format, ... );
}

void
printAt( int32_t x, int32_t y, const char *format, ... ) {
   char  _textStr[128];

   va_list args;
   va_start(args, format);
   vex_vsnprintf(_textStr, sizeof(_textStr), format, args );

   vexDisplayPrintf( x, y, true, _textStr );

   va_end( args );
}
void lv_tutorial_hello_world(void){


    /*Create a Label on the currently active screen*/
    lv_obj_t * label1 =  lv_label_create(lv_scr_act(), nullptr);

    /*Modify the Label's text*/
    lv_label_set_text(label1, "Hello world!");

    /* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment*/
    //lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
}
void opcontrol()
{
    robot = new Robot();
    robot->robotMode = REMOTE_CONTROLLED;
    int count=0;

	while (true) {
		printAt( 10, 40, "Hello V5 %d", count++ );

		pros::delay(20);
  }
    //robot->start_mainloop();
    while(true){
      lv_tutorial_hello_world();
      delay(20);
    //  printAt(0,0)
    }
}
