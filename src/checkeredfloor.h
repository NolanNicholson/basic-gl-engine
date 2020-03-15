#ifndef CHECKEREDFLOOR_H
#define CHECKEREDFLOOR_H

#include "object.h"

class CheckeredFloor : public Object {
  private:
    float tilesize = 0.1;
    int tiles_x = 12;
    int tiles_z = 12;
    int floor_y = 0;
  public:
    void load_resources() {
      //Position and color data
      //Vertex count: 3 vertices per triangle,
      //2 tris per quad,
      //tiles_x * tiles_z quads in the floor

      vertex_count = 3 * 2 * tiles_x * tiles_z;

      float x_offset = tilesize * tiles_x / 2;
      float y_offset = tilesize * tiles_z / 2;

      positions = new GLfloat[vertex_count * 4];
      static const GLfloat lightgray[]  = { 0.7, 0.7, 0.7, 1.0 };
      static const GLfloat darkgray[]   = { 0.5, 0.5, 0.5, 1.0 };
      static const GLfloat darkergray[] = { 0.3, 0.3, 0.3, 1.0 };
      const GLfloat *this_color;
      bool alternating = false;

      colors = new GLfloat[vertex_count * 4];
      int i = 0; // index within positions
      for (int t_x = 0; t_x < tiles_x; t_x++) {
        for (int t_y = 0; t_y < tiles_z; t_y++) {
          positions[i+ 0] = (t_x + 0) * tilesize - x_offset;
          positions[i+ 1] = floor_y;
          positions[i+ 2] = (t_y + 0) * tilesize - y_offset;
          positions[i+ 3] = 1.0;

          positions[i+ 4] = (t_x + 1) * tilesize - x_offset;
          positions[i+ 5] = floor_y;
          positions[i+ 6] = (t_y + 0) * tilesize - y_offset;
          positions[i+ 7] = 1.0;

          positions[i+ 8] = (t_x + 0) * tilesize - x_offset;
          positions[i+ 9] = floor_y;
          positions[i+10] = (t_y + 1) * tilesize - y_offset;
          positions[i+11] = 1.0;

          positions[i+12] = (t_x + 1) * tilesize - x_offset;
          positions[i+13] = floor_y;
          positions[i+14] = (t_y + 0) * tilesize - y_offset;
          positions[i+15] = 1.0;

          positions[i+16] = (t_x + 0) * tilesize - x_offset;
          positions[i+17] = floor_y;
          positions[i+18] = (t_y + 1) * tilesize - y_offset;
          positions[i+19] = 1.0;

          positions[i+20] = (t_x + 1) * tilesize - x_offset;
          positions[i+21] = floor_y;
          positions[i+22] = (t_y + 1) * tilesize - y_offset;
          positions[i+23] = 1.0;

          //colors: alternate between light gray and dark gray
          alternating = ((t_x & 1) ^ (t_y & 1));
          this_color = (alternating ? &darkergray[0] : &darkgray[0]);

          for (int j = 0; j < 24; j++) {
            colors[i+j] = this_color[j % 4];
          }

          i += 24; // 6 vertices added * 4 coords per vertex
        }
      }

    }
};

#endif //CHECKEREDFLOOR_H
