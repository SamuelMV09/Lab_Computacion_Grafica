// Medina Villa Samuel
// 320249538
// Practica#9
// Fecha de entrega: 10 de abril de 2026

// Std. Includes
#include <string>
#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

// Posiciones de las point lights 
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),   // Point light 0 - Fogata (se actualiza abajo)
    glm::vec3(0.0f, 0.0f, 0.0f),   // Point light 1 - Apagada
    glm::vec3(0.0f, 0.0f, 0.0f),   // Point light 2 - Apagada
    glm::vec3(0.0f, 0.0f, 0.0f)    // Point light 3 - Apagada
};

// Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Controles para activar/desactivar luces con teclas
bool luzDireccionalActiva = true;   // Tecla 1
bool luzPuntualActiva = true;       // Tecla 2
bool luzReflectorActiva = true;     // Tecla 3

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Fuentes de Luz - Samuel Medina Villa", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

   
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");

    // Carga de modelos
    Model red_dog((char*)"Models/RedDog.obj");
    Model granero((char*)"Models/Granero/Granero.obj");
    Model tractor((char*)"Models/tractor/tractor.obj");
    Model cloud((char*)"Models/clouds/clouds.obj");
    Model cloud2((char*)"Models/clouds2/clouds2.obj");
    Model burro((char*)"Models/burro/burro.obj");
    Model corral((char*)"Models/corral/corral.obj");
    Model planta((char*)"Models/plantas/planta.obj");
    Model planta2((char*)"Models/plantas/planta2.obj");
    Model planta3((char*)"Models/plantas/planta3.obj");
    Model carretilla((char*)"Models/carretilla/carretilla.obj");

    // Modelos para emitir las luces
    Model fogata((char*)"Models/fogata/fogata.obj");
    Model luna((char*)"Models/moon/moon.obj");
    Model poste((char*)"Models/poste/poste.obj");

    // Posiciones de los modelos 
    // 
    // La fogata esta en frente del perro 
    glm::vec3 fogataPos = glm::vec3(0.0f, -0.3f, 2.0f);

    // La luna en el cielo 
    glm::vec3 lunaPos = glm::vec3(5.0f, 12.0f, -8.0f);

    // El poste a lado del corral 
    
    glm::vec3 postePos = glm::vec3(14.0f, -0.3f, -0.5f);

    // Posicion de la luz del spotlight 
    glm::vec3 spotLightPos = glm::vec3(14.0f, 0.8f, 0.37f);
    glm::vec3 spotLightDir = glm::vec3(0.0f, -1.0f, 0.0f); // Apunta hacia abajo

    // Posicion de la point light de la fogata 
    pointLightPositions[0] = glm::vec3(fogataPos.x, fogataPos.y + 0.5f, fogataPos.z);

    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set texture units
    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    
    while (!glfwWindowShouldClose(window))
    {
        // Deltatime
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();

        // Cielo de noche 
        glClearColor(0.02f, 0.02f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        lightingShader.Use();
        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);

        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Luz direccional (Luna)
        if (luzDireccionalActiva)
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.08f, 0.08f, 0.15f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.4f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.5f);
        }
        else
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.0f, 0.0f, 0.0f);
        }

        // Luz puntual (fogata)
        if (luzPuntualActiva)
        {
            // Efecto de parpadeo del fuego usando funciones seno
            float flicker = 0.9f + 0.1f * sin(glfwGetTime() * 8.0f) * cos(glfwGetTime() * 5.3f);

            glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"),
                pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"),
                0.15f * flicker, 0.08f * flicker, 0.02f * flicker);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"),
                1.0f * flicker, 0.5f * flicker, 0.1f * flicker);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"),
                1.0f * flicker, 0.6f * flicker, 0.2f * flicker);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);
        }
        else
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"),
                pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.0f);
        }

        // Point lights 1, 2, 3 - Apagadas
        for (int i = 1; i < 4; i++)
        {
            std::string base = "pointLights[" + std::to_string(i) + "].";
            glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "position").c_str()), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "ambient").c_str()), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "diffuse").c_str()), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "specular").c_str()), 0.0f, 0.0f, 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "constant").c_str()), 1.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "linear").c_str()), 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "quadratic").c_str()), 0.0f);
        }

        // luz de tipo reflector (poste)
        if (luzReflectorActiva)
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"),
                spotLightPos.x, spotLightPos.y, spotLightPos.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"),
                spotLightDir.x, spotLightDir.y, spotLightDir.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.1f, 0.1f, 0.08f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.9f, 0.9f, 0.7f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 0.8f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(65.0f)));
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(65.0f)));
        }
        else
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"),
                spotLightPos.x, spotLightPos.y, spotLightPos.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"),
                spotLightDir.x, spotLightDir.y, spotLightDir.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(15.0f)));
            glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(25.0f)));
        }

        // Material
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

        // Matrices de vista y proyeccion
        glm::mat4 view = camera.GetViewMatrix();
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Dibujo de los modelos

        glm::mat4 model(1);

        // Perro 
        model = glm::mat4(1);
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        red_dog.Draw(lightingShader);

        // Granero
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        granero.Draw(lightingShader);

        // Tractor
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.3f, 6.0f, -11.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        tractor.Draw(lightingShader);

        // Nubes
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        cloud.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        cloud2.Draw(lightingShader);

        // Burro
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        burro.Draw(lightingShader);

        // Corral
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        corral.Draw(lightingShader);

        // Plantas
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        planta.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        planta2.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        planta3.Draw(lightingShader);

        // Carretilla
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.28f, -7.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        carretilla.Draw(lightingShader);

        

        // Fogata 
        model = glm::mat4(1);
        model = glm::translate(model, fogataPos);
        model = glm::scale(model, glm::vec3(0.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        fogata.Draw(lightingShader);

        // Poste de luz 
        model = glm::mat4(1);
        model = glm::translate(model, postePos);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        poste.Draw(lightingShader);

        glBindVertexArray(0);

        // dibujo de la luna 
        shader.Use();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        model = glm::mat4(1);
        model = glm::translate(model, lunaPos);
        model = glm::scale(model, glm::vec3(0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        luna.Draw(shader);

        glBindVertexArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// Movimiento de la camara
void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Llamadas al teclado
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }

    // Tecla 1: Activar/Desactivar luz direccional (Luna)
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        luzDireccionalActiva = !luzDireccionalActiva;
        std::cout << "Luz Direccional (Luna): " << (luzDireccionalActiva ? "ON" : "OFF") << std::endl;
    }

    // Tecla 2: Activar/Desactivar luz puntual (Fogata)
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        luzPuntualActiva = !luzPuntualActiva;
        std::cout << "Luz Puntual (Fogata): " << (luzPuntualActiva ? "ON" : "OFF") << std::endl;
    }

    // Tecla 3: Activar/Desactivar luz reflector (Poste)
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        luzReflectorActiva = !luzReflectorActiva;
        std::cout << "Luz Reflector (Poste): " << (luzReflectorActiva ? "ON" : "OFF") << std::endl;
    }
}


void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}