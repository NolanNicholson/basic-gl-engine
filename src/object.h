class Object {
  public:
    GLuint VAO;
    GLuint VBO[2];
    GLfloat *positions, *colors;
    int vertex_count = 0;

    virtual void load_resources() {
    }

    void init_buffers() {
      //Set up VAO
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);

      //Set up VBOs
      glCreateBuffers(2, &VBO[0]);

      //VBO 0: Positions
      int positions_size = vertex_count * 4 * sizeof(GLfloat);
      glNamedBufferStorage(VBO[0], positions_size, positions, 0);
      //Set up the VAO and VBO to feed the vertex shader
      glVertexArrayVertexBuffer(VAO,
          0, //first vertex buffer binding
          VBO[0],
          0, // offset
          4 * sizeof(GLfloat) // each vertex is one vec4
          );
      glVertexArrayAttribFormat(VAO,
          0, //first vertex buffer binding
          4, // number of components
          GL_FLOAT,
          GL_FALSE, // don't normalize
          0 // first element
          );
      glEnableVertexArrayAttrib(VAO, 0);

      //VBO 1: Colors
      int colors_size = vertex_count * 4 * sizeof(GLfloat);
      glNamedBufferStorage(VBO[1], colors_size, colors, 0);
      glVertexArrayVertexBuffer(VAO, 1, VBO[1], 0, 4 * sizeof(GLfloat));
      glVertexArrayAttribFormat(VAO, 1, 4, GL_FLOAT, GL_FALSE, 0);
      glEnableVertexArrayAttrib(VAO, 1);
    }

    void initialize() {
      load_resources();
      init_buffers();
    }

    void render(float time) {
      glDrawArrays(GL_TRIANGLES, 0, vertex_count);
    }

    void cleanup() {
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO[0]);
      glDeleteBuffers(1, &VBO[1]);
    }

    ~Object() {
      delete [] positions;
      delete [] colors;
    }
};
