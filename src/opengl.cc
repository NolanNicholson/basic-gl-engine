#include "opengl.h"
#include <cmath>

bool init_opengl() {
  //Check for errors
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cerr << "Error initializing OpenGL: " <<
      gluErrorString(error) << std::endl;
    return false;
  }

  //Initialize GLEW
  error = glewInit();
  if (error != GL_NO_ERROR) {
    std::cerr << "Error initializing GLEW" << std::endl;
    return false;
  }
  return true;
}

bool load_shader(GLuint &shader, std::string filename, GLenum shader_type) {
  //Load source file
  std::ifstream f { filename };
  if (!f.is_open()) {
    std::cerr << "File not found: " << filename << std::endl;
    return false;
  }

  //Dump source file contents into a string, then convert to a C-string
  std::string file_contents {
    std::istreambuf_iterator<char>(f),
    std::istreambuf_iterator<char>()
  };
  f.close();
  const char *shader_source = file_contents.c_str();

  //Create and compile the shader
  shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &shader_source, NULL);
  glCompileShader(shader);

  //Check for errors
  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {
    //Fetch and print error log
    GLint logSize = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    std::vector<GLchar> errorLog(logSize);
    glGetShaderInfoLog(shader, logSize, &logSize, &errorLog[0]);
    std::cerr << "Failed to compile shader:" << std::endl;
    for (GLchar ch : errorLog) {
      std::cerr << ch;
    }
    std::cerr << std::endl;

    glDeleteShader(shader);
    return false;
  }

  return true;
}

bool load_shaders(GLuint &program) {
  GLuint vs, fs; //shader handles
  bool vs_success, fs_success; //success flags

  //Load the indvidual shaders
  vs_success = load_shader(vs, "src/sh_vertex.glsl", GL_VERTEX_SHADER);
  fs_success = load_shader(fs, "src/sh_fragment.glsl", GL_FRAGMENT_SHADER);

  //Create a program, and link the shaders to it
  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  //Free up shaders (now that they've been copied into the program)
  glDeleteShader(vs);
  glDeleteShader(fs);

  //Check for errors
  GLint success = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    std::cerr << "Failed to link program" << std::endl;
    return false;
  }

  return true;
}

void render(GLuint program) {
  //Clear the screen
  static const GLfloat color[] = { 0.1f, 0.1f, 0.1f, 1.f };
  glClearBufferfv(GL_COLOR, 0, color);

  //Set the program and draw
  glUseProgram(program);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
