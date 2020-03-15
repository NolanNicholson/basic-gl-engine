#include "opengl.h"
#include "object.h"
#include "math3d.h"

#include "sierpinski.h"
#include "twotriangles.h"
#include "checkeredfloor.h"

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
    CheckeredFloor cf;
    Sierpinski st;

    bool initialize() {

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
      st.initialize();
      cf.initialize();

      //Done!
      return true;
    }

    void render(float time) {
      //Clear the screen
      static const GLfloat color[] = { 0.1f, 0.1f, 0.1f, 1.f };
      glClearBufferfv(GL_COLOR, 0, color);

      //Set the shader program
      glUseProgram(program);

      //Transformation matrix stack
      mat4 model, view, projection;
      model.set_identity();
      view.set_identity();
      projection.set_identity();

      glUniformMatrix4fv(10, 1, GL_FALSE, model.A);
      glUniformMatrix4fv(11, 1, GL_FALSE, view.A);
      glUniformMatrix4fv(12, 1, GL_FALSE, projection.A);

      //Set the position offset
      GLfloat position[] = {
        0.1f * float(cos(time)),
        0.1f * float(sin(time)),
        0.0f, 0.0f, };
      glVertexAttrib4fv(2, position);

      cf.render(time);

      //Mix up the position offset
      position[0] = -0.1f * float(cos(-time));
      position[1] = 0.1f * float(sin(-time));
      glVertexAttrib4fv(2, position);

      st.render(time);

      //Clean up
      glBindVertexArray(0);
      glUseProgram(0);

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
      cf.cleanup();
      st.cleanup();
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
