#include "opengl.h"

unsigned const int k_screen_width = 640;
unsigned const int k_screen_height = 480;
unsigned const int k_screen_fps = 60;

void run_main_loop(int val);

static void key_callback( GLFWwindow* window,
    int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int main(int argc, char* args[]) {
  std::cout << "Hello" << std::endl;

  //Initialize GLFW
  if (!glfwInit()) {
    return -1;
  }

  //Create a GLFW window running OpenGL 4.5
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  //Set GLFW window context and other properties
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // wait for vsync
  glfwSetKeyCallback(window, key_callback);

  //Initialize OpenGL and load shaders
  if (!init_opengl()) {
    std::cerr << "Failed to initialize OpenGL - terminating" << std::endl;
    return 1;
  }
  GLuint program;
  if (!load_shaders(program)) {
    std::cerr << "Failed to load/compile shaders - terminating" << std::endl;
    return 1;
  }

  while (!glfwWindowShouldClose(window)) {
    render();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
