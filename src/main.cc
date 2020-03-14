#include "opengl.h"
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
    GLuint program, VAO, VBO;

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

      //Set up VAO
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);

      //Set up VBO
      static const GLfloat vertices[] = {
         0.0,  0.0,  0.5,  1.0,
         0.4,  0.4,  0.5,  1.0,
         0.0,  0.4,  0.5,  1.0,
         0.0,  0.0,  0.5,  1.0,
        -0.4, -0.4,  0.5,  1.0,
         0.0, -0.4,  0.5,  1.0,
      };
      glCreateBuffers(1, &VBO);
      glNamedBufferStorage(VBO,
          sizeof(vertices),
          vertices,
          GL_MAP_WRITE_BIT);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);

      //Set up the VAO to feed the vertex shader
      glVertexArrayVertexBuffer(VAO,
          0, //first vertex buffer binding
          VBO,
          0, // offset
          4 * sizeof(GLfloat) // each vertex is one vec4
          );
      glVertexArrayAttribFormat(VAO,
          0,
          4, // number of components
          GL_FLOAT,
          GL_FALSE, // don't normalize
          0 // first element
          );
      glEnableVertexArrayAttrib(VAO, 0);

      //Done!
      return true;
    }

    void render(float time) {
      //Clear the screen
      static const GLfloat color[] = { 0.1f, 0.1f, 0.1f, 1.f };
      glClearBufferfv(GL_COLOR, 0, color);

      //Pass in shader data
      GLfloat position[] = {
        0.5f * float(cos(time)),
        0.5f * float(sin(time)),
        0.0f, 0.0f, };
      glVertexAttrib4fv(1, position);

      //Set the program and draw
      glUseProgram(program);
      glDrawArrays(GL_TRIANGLES, 0, 6);

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
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
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
