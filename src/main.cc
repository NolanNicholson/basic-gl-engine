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

class Object {
  public:
    GLuint VAO;
    GLuint VBO[2];
    int vertex_count;

    void initialize() {
      //Set up VAO
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);

      //Position and color data
      vertex_count = 6;
      static const GLfloat positions[] = {
         0.0,  0.0,  0.5,  1.0,
         0.4,  0.4,  0.5,  1.0,
         0.0,  0.4,  0.5,  1.0,
         0.0,  0.0,  0.5,  1.0,
        -0.4, -0.4,  0.5,  1.0,
         0.0, -0.4,  0.5,  1.0,
      };
      static const GLfloat yellow[] = { 1.0, 0.7, 0.3, 1.0 };
      static const GLfloat red[]    = { 1.0, 0.3, 0.3, 1.0 };
      static const GLfloat colors[] = {
        yellow[0], yellow[1], yellow[2], yellow[3],
        yellow[0], yellow[1], yellow[2], yellow[3],
        yellow[0], yellow[1], yellow[2], yellow[3],
        red[0], red[1], red[2], red[3],
        red[0], red[1], red[2], red[3],
        red[0], red[1], red[2], red[3],
      };

      //Set up VBOs
      glCreateBuffers(2, &VBO[0]);

      //VBO 0: Positions
      glNamedBufferStorage(VBO[0], sizeof(positions), positions, 0);
      //Set up the VAO and VBO to feed the vertex shader
      glVertexArrayVertexBuffer(VAO,
          0, //first vertex buffer binding
          VBO[0],
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

      //VBO 1: Colors
      glNamedBufferStorage(VBO[1], sizeof(colors), colors, 0);
      glVertexArrayVertexBuffer(VAO, 1, VBO[1], 0, 4 * sizeof(GLfloat));
      glVertexArrayAttribFormat(VAO, 1, 4, GL_FLOAT, GL_FALSE, 0);
      glEnableVertexArrayAttrib(VAO, 1);

    }

    void render(float time) {
      glDrawArrays(GL_TRIANGLES, 0, vertex_count);
    }

    void cleanup() {
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO[0]);
      glDeleteBuffers(1, &VBO[1]);
    }
};

class App {
  public:
    GLFWwindow *window;
    GLuint program;
    Object o;

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
        0.5f * float(cos(time)),
        0.5f * float(sin(time)),
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
