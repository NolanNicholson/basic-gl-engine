#ifndef SIERPINSKI_H
#define SIERPINSKI_H

#include "object.h"

class Sierpinski : public Object {
  public:
    int level = 5;
    int pos_index = 0;
    float radius = 0.8;
    float z = 0.5;

    void sierpinski_recursive(
        int sublevel,
        float c_x, float c_y, float r) {

      if (sublevel >= level) {
        //base case: `level` has been reached -
        //in this case, just add the triangle
        GLfloat triangle[12] = {
          c_x, c_y + r,
            z, 1.0,
          c_x - r, c_y - r,
            z, 1.0,
          c_x + r, c_y - r,
            z, 1.0,
        };
        for (int i = 0; i < 12; i++) {
          positions[pos_index + i] = triangle[i];
        }
        pos_index += 12;
      }
      else {
        //recursive case: make 3 smaller Sierpinskis
        sierpinski_recursive(sublevel+1,
            c_x,            c_y + 0.5 * r, r / 2);
        sierpinski_recursive(sublevel+1,
            c_x - 0.5 * r,  c_y - 0.5 * r, r / 2);
        sierpinski_recursive(sublevel+1,
            c_x + 0.5 * r,  c_y - 0.5 * r, r / 2);
      }
    }

    void load_resources() {
      //vertex count: 3 ^ (level + 1)
      vertex_count = 3;
      for (int i = 0; i < level; i++) {
        vertex_count *= 3;
      }

      //positions: assigned recursively
      positions = new GLfloat[vertex_count * 4];
      sierpinski_recursive(0, 0.0f, 0.0f, radius);

      //colors: all yellow
      static const GLfloat yellow[] = { 1.0, 0.7, 0.3, 1.0 };
      colors = new GLfloat[vertex_count * 4];
      for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < 4; j++) {
          colors[i * 4 + j] = yellow[j];
        }
      }
    }
};

#endif //SIERPINSKI_H
