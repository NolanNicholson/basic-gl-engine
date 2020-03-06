#include "opengl.h"

bool init_opengl() {
  //Initialize clear color
  glClearColor(0.1f, 0.1f, 0.1f, 1.f);

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

bool load_shader() {
  std::string filename = "src/sh_vertex.glsl";
  GLenum shader_type = GL_VERTEX_SHADER;

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
  GLuint shader = glCreateShader(shader_type);
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
    for (GLchar ch : errorLog) {
      std::cerr << ch;
    }
    std::cerr << std::endl;

    glDeleteShader(shader);
    return false;
  }

  return true;
}

bool load_shaders() {
  return load_shader();
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
}
