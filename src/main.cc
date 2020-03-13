#include "opengl.h"

static void key_callback(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
  //GLFW key press callback function
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

void framebuffer_size_callback(GLFWwindow* window,
    int width, int height) {
  //GLFW framebuffer resize callback function
  std::cout << "Framebuffer resized: " << width << " " << height << std::endl;
  glViewport(0, 0, width, height);
}

int main(int argc, char* args[]) {
  std::cout << "Starting..." << std::endl;

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
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

  //Set up a VAO (empty, but needs to be initialized for GL to draw anything?)
  GLuint VAO;
  glCreateVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //Main loop
  std::cout << "Rendering..." << std::endl;
  while (!glfwWindowShouldClose(window)) {
    render(program);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  //Wrap up
  glDeleteVertexArrays(1, &VAO);
  glDeleteProgram(program);
  glfwTerminate();
  return 0;
}
