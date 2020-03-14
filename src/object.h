class Object {
  public:
    GLuint VAO;
    GLuint VBO[2];
    int vertex_count;

    void initialize() {
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

      //Set up VAO
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);

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
