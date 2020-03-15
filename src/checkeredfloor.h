#ifndef CHECKEREDFLOOR_H
#define CHECKEREDFLOOR_H

#include "object.h"

class CheckeredFloor : public Object {
  private:
    float tilesize = 0.05;
    int tiles_wide = 12;
    int tiles_tall = 12;
  public:
    void load_resources() {
      //Position and color data
      //Vertex count: 3 vertices per triangle,
      //2 tris per quad,
      //tiles_wide * tiles_tall quads in the floor

      vertex_count = 3 * 2 * tiles_wide * tiles_tall;

      positions = new GLfloat[vertex_count * 4];
      static const GLfloat lightgray[] = { 0.7, 0.7, 0.7, 1.0 };
      static const GLfloat darkgray[]  = { 0.5, 0.5, 0.5, 1.0 };
      const GLfloat *this_color;
      bool alternating = false;

      colors = new GLfloat[vertex_count * 4];
      int i = 0; // index within positions
      for (int t_x = 0; t_x < tiles_wide; t_x++) {
        for (int t_y = 0; t_y < tiles_tall; t_y++) {
          positions[i+ 0] = (t_x + 0) * tilesize;
          positions[i+ 1] = (t_y + 0) * tilesize;
          positions[i+ 2] = 0.5;
          positions[i+ 3] = 1.0;

          positions[i+ 4] = (t_x + 1) * tilesize;
          positions[i+ 5] = (t_y + 0) * tilesize;
          positions[i+ 6] = 0.5;
          positions[i+ 7] = 1.0;

          positions[i+ 8] = (t_x + 0) * tilesize;
          positions[i+ 9] = (t_y + 1) * tilesize;
          positions[i+10] = 0.5;
          positions[i+11] = 1.0;

          positions[i+12] = (t_x + 1) * tilesize;
          positions[i+13] = (t_y + 0) * tilesize;
          positions[i+14] = 0.5;
          positions[i+15] = 1.0;

          positions[i+16] = (t_x + 0) * tilesize;
          positions[i+17] = (t_y + 1) * tilesize;
          positions[i+18] = 0.5;
          positions[i+19] = 1.0;

          positions[i+20] = (t_x + 1) * tilesize;
          positions[i+21] = (t_y + 1) * tilesize;
          positions[i+22] = 0.5;
          positions[i+23] = 1.0;

          //colors: alternate between light gray and dark gray
          alternating = ((t_x & 1) ^ (t_y & 1));
          this_color = (alternating ? &lightgray[0] : &darkgray[0]);

          for (int j = 0; j < 24; j++) {
            colors[i+j] = this_color[j % 4];
          }

          i += 24; // 6 vertices added * 4 coords per vertex
        }
      }

    }
};

#endif //CHECKEREDFLOOR_H
