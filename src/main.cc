#include "opengl.h"

unsigned const int k_screen_width = 640;
unsigned const int k_screen_height = 480;
unsigned const int k_screen_fps = 60;

void run_main_loop(int val);

int main(int argc, char* args[]) {
  std::cout << "Hello World" << std::endl;

  //Initialize FreeGLUT
  glutInit(&argc, args);

  //Create OpenGL 2.1 context
  glutInitContextVersion(2, 1);

  //Create double-buffered window
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(k_screen_width, k_screen_height);
  glutCreateWindow("OpenGL");

  //Initialize OpenGL
  bool success = init_opengl();
  if (!success) {
    return 1;
  }

  //Set rendering and timer functions
  glutDisplayFunc(render);
  glutTimerFunc(1000 / k_screen_fps, run_main_loop, 0);

  //Start the GLUT main loop
  glutMainLoop();

  return 0;
}

void run_main_loop(int val) {
  //Per-frame logic
  render();

  //Queue up next frame
  glutTimerFunc(1000 / k_screen_fps, run_main_loop, val);
}
