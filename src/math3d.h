#ifndef MATH3D_H
#define MATH3D_H

#include "opengl.h"
#include <iostream>
#include <cmath>

struct vec3 {
  GLfloat A[3] = { 0 };

  vec3(GLfloat Ai[3]) {
    for (int i = 0; i < 3; i++) {
      A[i] = Ai[i];
    }
  }

  vec3() {
  }

  vec3(GLfloat x, GLfloat y, GLfloat z) {
    A[0] = x; A[1] = y; A[2] = z;
  }

  static GLfloat dot(vec3 a, vec3 b) {
    return (
          a.A[0] * b.A[0]
        + a.A[1] * b.A[1]
        + a.A[2] * b.A[2]
        );
  }

  static vec3 cross(const vec3 &a, const vec3 &b) {
    GLfloat result[] = {
      (a.A[1] * b.A[2]) - (a.A[2] * b.A[1]),
      (a.A[2] * b.A[0]) - (a.A[0] * b.A[2]),
      (a.A[0] * b.A[1]) - (a.A[1] * b.A[0]),
    };
    return vec3(result);
  }

  static vec3 plus(const vec3 &a, const vec3 &b) {
    GLfloat result[] = {
      a.A[0] + b.A[0],
      a.A[1] + b.A[1],
      a.A[2] + b.A[2],
    };
    return vec3(result);
  }

  static vec3 minus(const vec3 &a, const vec3 &b) {
    GLfloat result[] = {
      a.A[0] - b.A[0],
      a.A[1] - b.A[1],
      a.A[2] - b.A[2],
    };
    return vec3(result);
  }

  static vec3 divide(const vec3 &a, GLfloat b) {
    GLfloat result[] = {
      a.A[0] / b,
      a.A[1] / b,
      a.A[2] / b,
    };
    return vec3(result);
  }

  GLfloat magnitude() {
    return (sqrt(A[0] * A[0] + A[1] * A[1] + A[2] * A[2]));
  }

  void print() {
    std::cout << "vec3: ( ";
    for (int i = 0; i < 3; i++) {
      std::cout << A[i] << " ";
    }
    std::cout << ")" << std::endl;
  }
};

struct mat4 {
  GLfloat A[16] = { 0 };

  void set_zero() {
    for (int i = 0; i < 16; i++) {
      A[i] = 0;
    }
  }

  mat4() {
  }

  mat4(GLfloat Ai[16]) {
    for (int i = 0; i < 16; i++) {
      A[i] = Ai[i];
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

  static mat4 lookat(const vec3 &camera, const vec3 &target, const vec3 &up) {
    vec3 forward = vec3::minus(target, camera);
    forward = vec3::divide(forward, forward.magnitude()); //normalize
    //forward.print();
    vec3 side = vec3::cross(forward, up);
    vec3 up_camera = vec3::cross(side, forward);

    GLfloat result[16] = { // note: column-major order
      side.A[0],      side.A[1],      side.A[2],      0.0,
      up_camera.A[0], up_camera.A[1], up_camera.A[2], 0.0,
      forward.A[0],   forward.A[1],   forward.A[2],   0.0,
      -camera.A[0],   -camera.A[1],   -camera.A[2],   1.0,
    };
    return mat4(result);
  }

  void print() {
    for (int r = 0; r < 4; r++) {
      std::cout << (r == 0 ? "mat4: ( " : "        ");
      for (int c = 0; c < 4; c++) {
        std::cout << at(r, c) << " ";
      }
      std::cout << std::endl;
    }
  }

};

#endif //MATH3D_H
