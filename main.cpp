#include <iostream>
#include <GL/glew.h>
#include <Display.h>
#include <Shader.h>
#include <Mesh.h>
#include <Texture.h>
#include <Transform.h>
#include <Camera.h>

#define WIDTH 800
#define HEIGHT 600

using namespace std;

//static std::string ShaderLoader(const std::string& filename)
//{
//    std::ifstream file;
//    file.open((filename).c_str());
//
//    std::string output;
//    std::string line;
//
//    if (file.is_open())
//    {
//        while (file.good())
//        {
//            getline(file, line);
//            output.append(line + "\n");
//        }
//    }
//    else
//    {
//        std::cerr << "Unable to load shader: " << filename << endl;
//    }
//    return output;
//}

int main()
{
    Display display(900, 800, "Hello World");

//     SDL init
//     SDL setAttribute
//     Create window & context
//     glewInit()

//    Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
//                          Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
//                          Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)), };
//
//
//
//    unsigned int indices[] = {0, 1, 2};
//
//    // mesh
//    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
//    Mesh mesh2("./res/monkey3.obj");
//    Mesh mesh3("./res/xyzCoords.obj");
//
//    Shader shader("./res/basicShader");
//    Texture texture("./res/bricks.jpg");
//    Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
//    Transform transform;
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//
//    float counter = 0.0f;
//
//    while (!display.isClosed()) {
//
//        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
//
//        float sinCounter = sinf(counter);
//        float cosCounter = cosf(counter);
//
//        transform.GetPos().x = sinCounter;
//        transform.GetPos().z = cosCounter;
//        transform.GetRot().x = counter * 5;
//        transform.GetRot().y = counter * 5;
//        transform.GetRot().z = counter * 5;
//
//        shader.Bind();
//        texture.Bind(0);
//        shader.Update(transform, camera);
//
//        mesh.Draw();
//        display.Update();
//        counter += 0.002f;
//    }
//    return 0;

    float vertices[] = {
         0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         -0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 1.0f,
         0.3f,  -0.3f, 0.0f, 0.6f, 1.0f, 0.0f,
         0.0f,  0.3f, 0.0f, 0.0f, 0.5f, 1.0f,
    };

    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 fragColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   fragColor = aColor;\n"
    "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 glFragColor;\n"
    "in vec3 fragColor;\n"
    "void main()\n"
    "{\n"
    "   glFragColor = vec4(fragColor, 1.0f);\n"
    "}\n";

    // SHADER
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //TODO: add error checking

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //TODO: add error checking

    // create a program for shaders & attach shaders & link
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //TODO: add error checking

    // vertex buffer (storage for vertex data)
    // vbo(vertex buffer obj - obj that can store vertices in GPU's memory)
    unsigned int vbo, vao;
    glGenBuffers(1, &vbo); // generate id
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // copy vertices data to buffer memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //TODO: add error checking

    // pos attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attrib
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!display.isClosed())
    {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        glUseProgram(shaderProgram);

        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, 2);
        glDrawArrays(GL_LINES, 2, 2); // vertical line
        glDrawArrays(GL_TRIANGLES, 4, 3);

        display.Update();
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return 0;
}
