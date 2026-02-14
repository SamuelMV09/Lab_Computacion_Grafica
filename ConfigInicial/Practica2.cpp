// Medina Villa Samuel
// 320249538
// Practica#2
// Fecha de entrega: 15 de febrero de 2026



#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);

	//Verificaci�n de errores de creacion  ventana
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {

			// Posición (X, Y, Z)          // Color (R, G, B) - Blanco
			-0.2f,  0.9f,  0.0f,          1.0f, 1.0f, 1.0f,// 0: Punta oreja izquierda
			 0.5f,  0.5f,  0.0f,          1.0f, 1.0f, 1.0f,

			 -0.1f,  0.7f,  0.0f,          1.0f, 1.0f, 1.0f,
			 -0.5f,  0.65f,  0.0f,          1.0f, 1.0f, 1.0f,
			 -0.4f,  0.4f,  0.0f,          1.0f, 1.0f, 1.0f,
			  0.1f,  0.38f,  0.0f,          1.0f, 1.0f, 1.0f,
			  0.2f,  0.42f,  0.0f,          1.0f, 1.0f, 1.0f,
			  0.2f,  0.1f,  0.0f,          1.0f, 1.0f, 1.0f,  // Vertice del cuello 
			  0.5f,  0.0f,  0.0f,          1.0f, 1.0f, 1.0f,
			  0.7f,  0.38f,  0.0f,          1.0f, 1.0f, 1.0f,
			  0.74f,  0.27f,  0.0f,          1.0f, 1.0f, 1.0f,

			  //Cuerpo

			0.2f,  0.1f,  0.0f,          1.0f, 1.0f, 1.0f,// Vertice del cuello 
			-0.25f,  -0.2f,  0.0f,          1.0f, 1.0f, 1.0f,
			-0.25f,  -0.5f,  0.0f,          1.0f, 1.0f, 1.0f,
			-0.05f,  -0.8f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.23f,  -0.46f,  0.0f,          1.0f, 1.0f, 1.0f,
			
			//Manos

			0.23f,  -0.46f,  0.0f,          1.0f, 1.0f, 1.0f, //Vertice de la panza
			0.55f,  -0.6f,  0.0f,          1.0f, 1.0f, 1.0f, //Vertice de la mano
			0.46f,  -0.43f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.59f,  -0.44f,  0.0f,          1.0f, 1.0f, 1.0f, //Vertice de la mano izquierda
			0.44f,  -0.2f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.5f,  0.0f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.2f,  0.1f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.23f,  -0.46f,  0.0f,          1.0f, 1.0f, 1.0f,

			//Patas

			-0.05f,  -0.8f,  0.0f,          1.0f, 1.0f, 1.0f, //24
			0.55f,  -0.8f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.09f,  -0.64f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.17f,  -0.66f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.55f,  -0.7f,  0.0f,          1.0f, 1.0f, 1.0f,
			0.2f,  -0.52f,  0.0f,          1.0f, 1.0f, 1.0f,


			//Cola

			-0.25f,  -0.2f,  0.0f,          1.0f, 1.0f, 1.0f,
			-0.38f,  -0.14f,  0.0f,          1.0f, 1.0f, 1.0f,
			-0.5f,  -0.19f,  0.0f,          1.0f, 1.0f, 1.0f,
			-0.45f,  -0.3f,  0.0f,          1.0f, 1.0f, 1.0f,
			-0.25f,  -0.38f,  0.0f,          1.0f, 1.0f, 1.0f,

			//Lineas para conectar 

			0.41f,  -0.31f,  0.0f,          1.0f, 1.0f, 1.0f,

			
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1,
		2, 0,
		2, 1, 
		1, 3,
		3, 4,
		4, 5,
		5, 6,
		6, 1,
		5, 7,
		7, 8,
		1, 9,
		9, 10,
		10, 8,
		7, 17,
		20, 35,
		14, 25, 
		25, 26,
		27, 28,
		28, 29,

	};



	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)



	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);


		glPointSize(7);
		//glDrawArrays(GL_POINTS,20,1);

		//glDrawArrays(GL_LINES,0,2);



		
		

		//Funcion para crear el cuerpo
		glDrawArrays(GL_LINE_LOOP,11,5);

		//Funcion para las manos
		glDrawArrays(GL_LINE_LOOP, 16, 8);


		//Funcion para la cola
		glDrawArrays(GL_LINE_LOOP, 30, 5);




		//glDrawArrays(GL_TRIANGLES, 15, 3);

		glDrawElements(GL_LINES, 40,GL_UNSIGNED_INT,0);



		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}