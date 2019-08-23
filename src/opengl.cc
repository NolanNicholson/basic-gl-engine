#include "opengl.h"

bool init_opengl() {
  //Initialize projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Initialize modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  //Check for errors
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cerr << "Error initializing OpenGL: " 
      << gluErrorString(error) << std::endl;
    return false;
  }
  return true;
}

void render() {
  //Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  //Render a quad
  glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
  glEnd();

  //Update screen
  glutSwapBuffers();
}
