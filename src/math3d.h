#ifndef MATH3D_H
#define MATH3D_H

#include "opengl.h"
#include <iostream>

struct mat4 {
  GLfloat A[16];

  mat4() {
    set_zero();
  }

  mat4(GLfloat Ai[16]) {
    for (int i = 0; i < 16; i++) {
      A[i] = Ai[i];
    }
  }

  void set_zero() {
    for (int i = 0; i < 16; i++) {
      A[i] = 0;
    }
  }

  void set_identity() {
    for (int i = 0; i < 16; i++) {
      A[i] = (i % 5 ? 0 : 1);
    }
  }

  GLfloat at(int r, int c) {
    return A[c * 4 + r];
  }

  void set_at(int r, int c, GLfloat value) {
    A[c * 4 + r] = value;
  }

  static mat4 multiply(const mat4 &m1, const mat4 &m2) {
    //TODO
    mat4 result;
    return result;
  }

  void print() {
    for (int r = 0; r < 4; r++) {
      for (int c = 0; c < 4; c++) {
        std::cout << at(r, c) << " ";
      }
      std::cout << std::endl;
    }
  }

};

#endif //MATH3D_H
