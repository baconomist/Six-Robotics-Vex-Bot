//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_VECTOR2_H
#define VEXROBOT_VECTOR2_H

struct Vector2
{
    int x;
    int y;
    Vector2 operator - (Vector2 obj) {
      Vector2 res;
      res.x = x - obj.x;
      res.y = y - obj.y;
      return res;
    }
    Vector2 (int xpos = 0, int ypos = 0) {
      x = xpos;
      y = ypos;
    }
};

#endif //VEXROBOT_VECTOR2_H
