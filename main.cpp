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

int main()
{
    Display display(800, 600, "Hello World");

    // SDL init
    // SDL setAttribute
    // Create window & context
    // glewInit()

    Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
                          Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
                          Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)), };



    unsigned int indices[] = {0, 1, 2};

    // mesh
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Mesh mesh2("./res/monkey3.obj");
    Mesh mesh3("./res/xyzCoords.obj");

    Shader shader("./res/basicShader");
    Texture texture("./res/bricks.jpg");
    Camera camera(glm::vec3(0, 2, -15), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
    Transform transform;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float counter = 0.0f;

    while (!display.isClosed()) {

        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);

        //transform.GetPos().x = sinCounter;
        //transform.GetPos().z = cosCounter;
        //transform.GetRot().x = counter * 5;
        transform.GetRot().y = counter * 5;
        //transform.GetRot().z = counter * 5;

        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);

        mesh3.Draw();
        display.Update();
        counter += 0.002f;
    }
    return 0;
}
