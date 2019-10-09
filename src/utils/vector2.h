//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_VECTOR2_H
#define VEXROBOT_VECTOR2_H

<<<<<<< HEAD
=======
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

<<<<<<< HEAD
>>>>>>> 00bdc5eee96d27480474277298b8b5d35b9dda71
=======


>>>>>>> 64b9b0542630b924e2c23b999a43ea2a301c5b72
#endif //VEXROBOT_VECTOR2_H
