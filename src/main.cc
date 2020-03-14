#include "opengl.h"
#include "object.h"

#include "sierpinski.h"
#include "twotriangles.h"

#include <cmath>

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


class App {
  public:
    GLFWwindow *window;
    GLuint program;
    Sierpinski o;

    bool initialize() {
      /*
      std::cout << "Enter a number between 0 and 7: ";
      std::cin >> o.level;
      */

      std::cout << "Starting..." << std::endl;

      //Initialize GLFW
      if (!glfwInit()) {
        return false;
      }

      //Create a GLFW window running OpenGL 4.5
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
      window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
      if (!window) {
        glfwTerminate();
        return false;
      }

      //Set GLFW window context and other properties
      glfwMakeContextCurrent(window);
      glfwSwapInterval(1); // wait for vsync
      glfwSetKeyCallback(window, key_callback);
      glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

      //Initialize OpenGL and load shaders
      if (!init_opengl()) {
        std::cerr << "Failed to initialize OpenGL!" << std::endl;
        return false;
      }

      if (!load_shaders(program)) {
        std::cerr << "Failed to load/compile shaders - terminating" << std::endl;
        return false;
      }

      //Initialize a test object
      o.initialize();

      //Done!
      return true;
    }

    void render(float time) {
      //Clear the screen
      static const GLfloat color[] = { 0.1f, 0.1f, 0.1f, 1.f };
      glClearBufferfv(GL_COLOR, 0, color);


      //Pass in shader data
      GLfloat position[] = {
        0.1f * float(cos(time)),
        0.1f * float(sin(time)),
        0.0f, 0.0f, };
      glVertexAttrib4fv(2, position);

      //Set the program and draw
      glUseProgram(program);

      o.render(time);

      //Final GLFW buffer swap
      glfwSwapBuffers(window);
    }

    void mainloop() {
      while (!glfwWindowShouldClose(window)) {
        render(glfwGetTime());
        glfwPollEvents();
      }
    }

    void shutdown() {
      o.cleanup();
      glDeleteProgram(program);
      glfwTerminate();
    }
};


int main(int argc, char* args[]) {
  //Create and initialize an application instance
  App a;
  if (!a.initialize()) {
    std::cerr << "Failed to start application - terminating" << std::endl;
    return 1;
  }

  //Main loop
  std::cout << "Running..." << std::endl;
  a.mainloop();

  //Wrap up
  a.shutdown();
  return 0;
}
