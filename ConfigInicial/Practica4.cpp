// Medina Villa Samuel 
// 320249538
// Practica#4
// Fecha de entrega:28 de febrero de 2026


#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers



	// use with Perspective Projection

	// 1. Cafe CLARO 
	float verticesCafe[] = {
								//Colores (RGB: 0.6f, 0.3f, 0.1f)
		-0.5f, -0.5f,  0.5f,	0.6f, 0.3f, 0.1f,
		 0.5f, -0.5f,  0.5f,	0.6f, 0.3f, 0.1f,
		 0.5f,  0.5f, 0.5f,		0.6f, 0.3f,	0.1f,
		0.5f,  0.5f, 0.5f,		0.6f, 0.3f,	0.1f,
		-0.5f,  0.5f, 0.5f,		0.6f, 0.3f,	0.1f,
		-0.5f, -0.5f, 0.5f,		0.6f, 0.3f, 0.1f,

		-0.5f, -0.5f,-0.5f, 0.6f, 0.3f,0.1f,//Back
		 0.5f, -0.5f,-0.5f, 0.6f, 0.3f,0.1f,
		 0.5f,  0.5f,-0.5f, 0.6f, 0.3f,0.1f,
		 0.5f,  0.5f,-0.5f, 0.6f, 0.3f,0.1f,
		-0.5f,  0.5f,-0.5f, 0.6f, 0.3f,0.1f,
		-0.5f, -0.5f,-0.5f, 0.6f, 0.3f,0.1f,

		 0.5f, -0.5f,  0.5f,  0.6f, 0.3f,0.1f,
		 0.5f, -0.5f, -0.5f,  0.6f, 0.3f,0.1f,
		 0.5f,  0.5f, -0.5f,  0.6f, 0.3f,0.1f,
		 0.5f,  0.5f, -0.5f,  0.6f, 0.3f,0.1f,
		 0.5f,  0.5f,  0.5f,  0.6f, 0.3f,0.1f,
		 0.5f,  -0.5f, 0.5f, 0.6f, 0.3f,0.1f,

		-0.5f,  0.5f,  0.5f,  0.6f, 0.3f,0.1f,
		-0.5f,  0.5f, -0.5f,  0.6f, 0.3f,0.1f,
		-0.5f, -0.5f, -0.5f,  0.6f, 0.3f,0.1f,
		-0.5f, -0.5f, -0.5f,  0.6f, 0.3f,0.1f,
		-0.5f, -0.5f,  0.5f,  0.6f, 0.3f,0.1f,
		-0.5f,  0.5f,  0.5f,  0.6f, 0.3f,0.1f,

		-0.5f, -0.5f, -0.5f, 0.6f, 0.3f,0.1f,
		0.5f, -0.5f, -0.5f,  0.6f, 0.3f,0.1f,
		0.5f, -0.5f,  0.5f,  0.6f, 0.3f,0.1f,
		0.5f, -0.5f,  0.5f,  0.6f, 0.3f,0.1f,
		-0.5f, -0.5f,  0.5f, 0.6f, 0.3f,0.1f,
		-0.5f, -0.5f, -0.5f, 0.6f, 0.3f,0.1f,

		-0.5f,  0.5f, -0.5f, 0.6f, 0.3f,0.1f,
		0.5f,  0.5f, -0.5f,  0.6f, 0.3f,0.1f,
		0.5f,  0.5f,  0.5f,  0.6f, 0.3f,0.1f,
		0.5f,  0.5f,  0.5f,  0.6f, 0.3f,0.1f,
		-0.5f,  0.5f,  0.5f, 0.6f, 0.3f,0.1f,
		-0.5f,  0.5f, -0.5f, 0.6f, 0.3f,0.1f,
	};


	// 2. Cafe OSCURO 
	float verticesCafeOscuro[] = {
								// Colores (RGB más oscuro: 0.3f, 0.15f, 0.05f)
		-0.5f, -0.5f,  0.5f,   0.3f, 0.15f, 0.05f,
		 0.5f, -0.5f,  0.5f,   0.3f, 0.15f, 0.05f,
		  0.5f,  0.5f, 0.5f,	0.3f, 0.15f,0.05f,
		0.5f,  0.5f, 0.5f,		0.3f, 0.15f,0.05f,
		-0.5f,  0.5f, 0.5f,		0.3f, 0.15f,0.05f,
		-0.5f, -0.5f, 0.5f,		0.3f, 0.15f,0.05f,

		-0.5f, -0.5f,-0.5f, 0.3f, 0.15f,0.05f,//Back
		 0.5f, -0.5f,-0.5f, 0.3f, 0.15f,0.05f,
		 0.5f,  0.5f,-0.5f, 0.3f, 0.15f,0.05f,
		 0.5f,  0.5f,-0.5f, 0.3f, 0.15f,0.05f,
		-0.5f,  0.5f,-0.5f, 0.3f, 0.15f,0.05f,
		-0.5f, -0.5f,-0.5f, 0.3f, 0.15f,0.05f,

		 0.5f, -0.5f,  0.5f,  0.3f, 0.15f,0.05f,
		 0.5f, -0.5f, -0.5f,  0.3f, 0.15f,0.05f,
		 0.5f,  0.5f, -0.5f,  0.3f, 0.15f,0.05f,
		 0.5f,  0.5f, -0.5f,  0.3f, 0.15f,0.05f,
		 0.5f,  0.5f,  0.5f,  0.3f, 0.15f,0.05f,
		 0.5f,  -0.5f, 0.5f, 0.3f, 0.15f,0.05f,

		-0.5f,  0.5f,  0.5f,  0.3f, 0.15f,0.05f,
		-0.5f,  0.5f, -0.5f,  0.3f, 0.15f,0.05f,
		-0.5f, -0.5f, -0.5f,  0.3f, 0.15f,0.05f,
		-0.5f, -0.5f, -0.5f,  0.3f, 0.15f,0.05f,
		-0.5f, -0.5f,  0.5f,  0.3f, 0.15f,0.05f,
		-0.5f,  0.5f,  0.5f,  0.3f, 0.15f,0.05f,

		-0.5f, -0.5f, -0.5f, 0.3f, 0.15f,0.05f,
		0.5f, -0.5f, -0.5f,  0.3f, 0.15f,0.05f,
		0.5f, -0.5f,  0.5f,  0.3f, 0.15f,0.05f,
		0.5f, -0.5f,  0.5f,  0.3f, 0.15f,0.05f,
		-0.5f, -0.5f,  0.5f, 0.3f, 0.15f,0.05f,
		-0.5f, -0.5f, -0.5f, 0.3f, 0.15f,0.05f,

		-0.5f,  0.5f, -0.5f, 0.3f, 0.15f,0.05f,
		0.5f,  0.5f, -0.5f,  0.3f, 0.15f,0.05f,
		0.5f,  0.5f,  0.5f,  0.3f, 0.15f,0.05f,
		0.5f,  0.5f,  0.5f,  0.3f, 0.15f,0.05f,
		-0.5f,  0.5f,  0.5f, 0.3f, 0.15f,0.05f,
		-0.5f,  0.5f, -0.5f, 0.3f, 0.15f,0.05f,
	};


	// 3. BLANCO (Pecho / Patas / Punta de la cola)
	float verticesBlanco[] = {
		// Posiciones          // Colores (RGB: 0.9f, 0.9f, 0.9f)
		-0.5f, -0.5f,  0.5f,   0.9f, 0.9f, 0.9f,
		 0.5f, -0.5f,  0.5f,   0.9f, 0.9f, 0.9f,
		 0.5f,  0.5f, 0.5f,		0.9f, 0.9f,0.9f,
		0.5f,  0.5f, 0.5f,		0.9f, 0.9f,0.9f,
		-0.5f,  0.5f, 0.5f,		0.9f, 0.9f,0.9f,
		-0.5f, -0.5f, 0.5f,		0.9f, 0.9f,0.9f,

		-0.5f, -0.5f,-0.5f, 0.9f, 0.9f,0.9f,//Back
		 0.5f, -0.5f,-0.5f, 0.9f, 0.9f,0.9f,
		 0.5f,  0.5f,-0.5f, 0.9f, 0.9f,0.9f,
		 0.5f,  0.5f,-0.5f, 0.9f, 0.9f,0.9f,
		-0.5f,  0.5f,-0.5f, 0.9f, 0.9f,0.9f,
		-0.5f, -0.5f,-0.5f, 0.9f, 0.9f,0.9f,

		 0.5f, -0.5f,  0.5f,  0.9f, 0.9f,0.9f,
		 0.5f, -0.5f, -0.5f,  0.9f, 0.9f,0.9f,
		 0.5f,  0.5f, -0.5f,  0.9f, 0.9f,0.9f,
		 0.5f,  0.5f, -0.5f,  0.9f, 0.9f,0.9f,
		 0.5f,  0.5f,  0.5f,  0.9f, 0.9f,0.9f,
		 0.5f,  -0.5f, 0.5f, 0.9f, 0.9f,0.9f,

		-0.5f,  0.5f,  0.5f,  0.9f, 0.9f,0.9f,
		-0.5f,  0.5f, -0.5f,  0.9f, 0.9f,0.9f,
		-0.5f, -0.5f, -0.5f,  0.9f, 0.9f,0.9f,
		-0.5f, -0.5f, -0.5f,  0.9f, 0.9f,0.9f,
		-0.5f, -0.5f,  0.5f,  0.9f, 0.9f,0.9f,
		-0.5f,  0.5f,  0.5f,  0.9f, 0.9f,0.9f,

		-0.5f, -0.5f, -0.5f, 0.9f, 0.9f,0.9f,
		0.5f, -0.5f, -0.5f,  0.9f, 0.9f,0.9f,
		0.5f, -0.5f,  0.5f,  0.9f, 0.9f,0.9f,
		0.5f, -0.5f,  0.5f,  0.9f, 0.9f,0.9f,
		-0.5f, -0.5f,  0.5f, 0.9f, 0.9f,0.9f,
		-0.5f, -0.5f, -0.5f, 0.9f, 0.9f,0.9f,

		-0.5f,  0.5f, -0.5f, 0.9f, 0.9f,0.9f,
		0.5f,  0.5f, -0.5f,  0.9f, 0.9f,0.9f,
		0.5f,  0.5f,  0.5f,  0.9f, 0.9f,0.9f,
		0.5f,  0.5f,  0.5f,  0.9f, 0.9f,0.9f,
		-0.5f,  0.5f,  0.5f, 0.9f, 0.9f,0.9f,
		-0.5f,  0.5f, -0.5f, 0.9f, 0.9f,0.9f,
	};

	// 4. NEGRO (Nariz / Ojos / Mancha principal)
	float verticesNegro[] = {
		// Posiciones          // Colores (RGB: 0.1f, 0.1f, 0.1f)
		-0.5f, -0.5f,  0.5f,   0.1f, 0.1f, 0.1f,
		 0.5f, -0.5f,  0.5f,   0.1f, 0.1f, 0.1f,
		 0.5f,  0.5f, 0.5f,		0.1f, 0.1f,0.1f,
		0.5f,  0.5f, 0.5f,		0.1f, 0.1f,0.1f,
		-0.5f,  0.5f, 0.5f,		0.1f, 0.1f,0.1f,
		-0.5f, -0.5f, 0.5f,		0.1f, 0.1f,0.1f,

		-0.5f, -0.5f,-0.5f, 0.1f, 0.1f,0.1f,//Back
		 0.5f, -0.5f,-0.5f, 0.1f, 0.1f,0.1f,
		 0.5f,  0.5f,-0.5f, 0.1f, 0.1f,0.1f,
		 0.5f,  0.5f,-0.5f, 0.1f, 0.1f,0.1f,
		-0.5f,  0.5f,-0.5f, 0.1f, 0.1f,0.1f,
		-0.5f, -0.5f,-0.5f, 0.1f, 0.1f,0.1f,

		 0.5f, -0.5f,  0.5f,  0.1f, 0.1f,0.1f,
		 0.5f, -0.5f, -0.5f,  0.1f, 0.1f,0.1f,
		 0.5f,  0.5f, -0.5f,  0.1f, 0.1f,0.1f,
		 0.5f,  0.5f, -0.5f,  0.1f, 0.1f,0.1f,
		 0.5f,  0.5f,  0.5f,  0.1f, 0.1f,0.1f,
		 0.5f,  -0.5f, 0.5f, 0.1f, 0.1f,0.1f,

		-0.5f,  0.5f,  0.5f,  0.1f, 0.1f,0.1f,
		-0.5f,  0.5f, -0.5f,  0.1f, 0.1f,0.1f,
		-0.5f, -0.5f, -0.5f,  0.1f, 0.1f,0.1f,
		-0.5f, -0.5f, -0.5f,  0.1f, 0.1f,0.1f,
		-0.5f, -0.5f,  0.5f,  0.1f, 0.1f,0.1f,
		-0.5f,  0.5f,  0.5f,  0.1f, 0.1f,0.1f,

		-0.5f, -0.5f, -0.5f, 0.1f, 0.1f,0.1f,
		0.5f, -0.5f, -0.5f,  0.1f, 0.1f,0.1f,
		0.5f, -0.5f,  0.5f,  0.1f, 0.1f,0.1f,
		0.5f, -0.5f,  0.5f,  0.1f, 0.1f,0.1f,
		-0.5f, -0.5f,  0.5f, 0.1f, 0.1f,0.1f,
		-0.5f, -0.5f, -0.5f, 0.1f, 0.1f,0.1f,

		-0.5f,  0.5f, -0.5f, 0.1f, 0.1f,0.1f,
		0.5f,  0.5f, -0.5f,  0.1f, 0.1f,0.1f,
		0.5f,  0.5f,  0.5f,  0.1f, 0.1f,0.1f,
		0.5f,  0.5f,  0.5f,  0.1f, 0.1f,0.1f,
		-0.5f,  0.5f,  0.5f, 0.1f, 0.1f,0.1f,
		-0.5f,  0.5f, -0.5f, 0.1f, 0.1f,0.1f,
	};



	GLuint VBOs[4], VAOs[4];
	glGenVertexArrays(4, VAOs);
	glGenBuffers(4, VBOs);
	//glGenBuffers(1, &EBO);



	//Configuracion para el color Cafe 
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCafe), verticesCafe, GL_STATIC_DRAW);
	// Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	//Configuracion para el color Cafe mas oscuro
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCafeOscuro), verticesCafeOscuro, GL_STATIC_DRAW);
	// Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Configuracion para el color blanco

	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBlanco), verticesBlanco, GL_STATIC_DRAW);
	// Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



	//Configuracion para el color Negro

	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNegro), verticesNegro, GL_STATIC_DRAW);
	// Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	



		/////////////////////////////////////////////////////////////// Cafe claro //////////////////////////////////////////////////////////////////////

		glBindVertexArray(VAOs[0]); 



		// Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cabeza
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.35f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		// Parte de la cabeza 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.1f, 0.5f, 0.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		//Cachetes
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.1f, 0.5f, 0.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Parte superior de las 4 patas 
		// 
		// 1. Delantera Izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.15f, -0.4f, 0.45f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.15f, -0.4f, 0.45f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Trasera Izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.15f, -0.4f, -0.45f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Trasera Derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.15f, -0.4f, -0.45f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/////////////////////////////////////////////////////////////// //////////////////////////////////////////////////////////////////////

		

		///////////////////////////////////////////////////////////////// Cafe oscuro //////////////////////////////////////////////////////////////////////

		glBindVertexArray(VAOs[1]); // Cafe oscuro



         //Oreja Izquierda (Vista de frente, lado derecho de la pantalla)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.3f, 0.45f, 0.23f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		// 2. Oreja Derecha (Vista de frente, lado izquierdo de la pantalla)

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, 0.45f, 0.23f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.2f, 0.751f, 0.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.005f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Mancha de la pata izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.251f, 0.1f, 0.5f));
		model = glm::scale(model, glm::vec3(0.005f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.2f, 0.1f, 0.55f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.005f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Mancha de la pata izquierda de abajo 

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.2f, -0.5f, 0.55f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.005f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.251f, -0.5f, 0.5f));
		model = glm::scale(model, glm::vec3(0.005f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Mancha de la pata derecha 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.1f, -0.5f, 0.55f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.005f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//mancha de la pata derecha arriba
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.2f, -0.09f, 0.55f));
		model = glm::scale(model, glm::vec3(0.13f, 0.1f, 0.005f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Mancha abajo de la mancha negra del lomo

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.251f, -0.2f, 0.1f));
		model = glm::scale(model, glm::vec3(0.005f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Mancha a lado de la mancha negra entre la T
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.251f, -0.02f, -0.35f));
		model = glm::scale(model, glm::vec3(0.005f, 0.12f, 0.12f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		//Mancha de la pata izquierda de atras
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.251f, -0.5f, -0.5f));
		model = glm::scale(model, glm::vec3(0.005f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cachete
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.2f, 0.35f, 0.68f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.005f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.251f, 0.35f, 0.65f));
		model = glm::scale(model, glm::vec3(0.005f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		///////////////////////////////////////////////////////////////// //////////////////////////////////////////////////////////////////////

		//

		///////////////////////////////////////////////////////////////// Color blanco //////////////////////////////////////////////////////////////////////



		glBindVertexArray(VAOs[2]);//Color blanco


		// Cabeza
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//// Patas delanteras
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.15f, -0.65f, 0.45f)); // Posición de la pata
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // Tamaño de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.15f, -0.65f, 0.45f)); // Posición de la pata
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // Tamaño de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Patas traseras
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.15f, -0.65f, -0.45f)); // Posición de la pata
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // Tamaño de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.15f, -0.65f, -0.45f)); // Posición de la pata
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // Tamaño de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		////Hocico

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.4f, 0.8f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);





		//  Parche de Pecho Blanco 

		// 1. Parte superior del pecho (Más ancha, justo debajo de la cabeza)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.15f, 0.56f));
		model = glm::scale(model, glm::vec3(0.25f, 0.2f, 0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 2. Parte media de la panza (Un poco más angosta)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.05f, 0.56f));
		model = glm::scale(model, glm::vec3(0.25f, 0.2f, 0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 3. Tira baja (La que baja entre las dos patas delanteras)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.25f, 0.56f));
		// Un ancho de 0.1f 
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		// Tira atras de la tira negra de la cola 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.48f, -0.9f));
		model = glm::scale(model, glm::vec3(0.15f, 0.45f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Base de la cola 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.18f, -0.6f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.45f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		

		// Punta de la cola 

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.78f, -0.75f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		///////////////////////////////////////////////////////////////// //////////////////////////////////////////////////////////////////////




		///////////////////////////////////////////////////////////////// Color negro //////////////////////////////////////////////////////////////////////




		glBindVertexArray(VAOs[3]);//Color Negro


		// Ojos
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.2f, 0.6f, 0.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.2f, 0.6f, 0.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);




		// MANCHA DEL LOMO (Forma de "T" invertida) 

		// 1. Franja Superior (Cubre la parte alta de la espalda, de cuello a cadera)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.15f, -0.15f));
		model = glm::scale(model, glm::vec3(0.52f, 0.22f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		// 1. Franja que llega hasta la cola 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.15f, -0.33f));
		model = glm::scale(model, glm::vec3(0.32f, 0.22f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);




		// 2. Caída Lateral 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.05f, -0.15f));
		model = glm::scale(model, glm::vec3(0.52f, 0.3f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		

		// COLA 

		// 1. Base de la cola (Conecta exactamente sobre el final del lomo)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.33f, -0.6f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 2. Mitad de la cola (Sube y se hace un "paso" hacia atrás)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.48f, -0.75f));
		model = glm::scale(model, glm::vec3(0.15f, 0.45f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Punta de la cola
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.78f, -0.6f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);




		////// Nariz
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.93f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		///////////////////////////////////////////////////////////////// //////////////////////////////////////////////////////////////////////



		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(4, VAOs);
	glDeleteBuffers(4, VBOs);


	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.4f;
}
