/*
 * Use vex text coding studio to configure this file
 * */

/*vex-vision-config:begin*/
#include "../../../../Documents/vexcode-projects/MyProject1/include/vex.h"
vex::vision::signature SIG_1 = vex::vision::signature (1, 5381, 6157, 5769, -1289, -831, -1060, 3, 0);
vex::vision::signature SIG_2 = vex::vision::signature (2, -7247, -5957, -6602, -3569, -1915, -2742, 3, 0);
vex::vision::signature SIG_3 = vex::vision::signature (3, 1105, 2097, 1601, 6295, 8029, 7162, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision1 = vex::vision (vex::PORT15, 150, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/