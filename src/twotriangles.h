#ifndef TWOTRIANGLES_H
#define TWOTRIANGLES_H

#include "object.h"

class TwoTriangles : public Object {
  public:
    void load_resources() {
      //Position and color data
      vertex_count = 6;

      positions = new GLfloat[vertex_count * 4] {
         0.0,  0.0,  0.5,  1.0,
         0.4,  0.4,  0.5,  1.0,
         0.0,  0.4,  0.5,  1.0,
         0.0,  0.0,  0.5,  1.0,
        -0.4, -0.4,  0.5,  1.0,
         0.0, -0.4,  0.5,  1.0,
      };

      static const GLfloat yellow[] = { 1.0, 0.7, 0.3, 1.0 };
      static const GLfloat red[]    = { 1.0, 0.3, 0.3, 1.0 };
      colors = new GLfloat[vertex_count * 4] {
        yellow[0], yellow[1], yellow[2], yellow[3],
        yellow[0], yellow[1], yellow[2], yellow[3],
        yellow[0], yellow[1], yellow[2], yellow[3],
        red[0], red[1], red[2], red[3],
        red[0], red[1], red[2], red[3],
        red[0], red[1], red[2], red[3],
      };
    }
};

#endif //TWOTRIANGLES_H
