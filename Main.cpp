#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>





	const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0 ) in vec3 aPos;\n "
"void main()\n"
"{\n"
"       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		" FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
		"}\n\0";







using namespace std;
int main() {

	// to initialize the GLFW
	glfwInit();

	// To tell the GLFW what version am i using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell glfw we are using core profile ( only modern functions now )
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 


	// Vertices Coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f , // left lower corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f , // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f , // upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f ,// Inner right
		0.0f / -0.5f  * float(sqrt(3)) / 3, 0.0f ,// Inner Down


	};


	GLuint indices[] =
	{
		0, 3, 5, // lo wer left triang
		3,2,4, // lower right
		5,4,1 // upper trian
	};



	// here we creat a window 800 oixel by 800 pixel, and naming it openglprojxx xd

	GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGLPROJXX", NULL, NULL); 
	 // just an error check
	if (window == NULL) {

		cout << "Failed to create a window nigs" << endl ;
		glfwTerminate();
		return -1;

	}

	// we introduce the window to the current context yea
	glfwMakeContextCurrent(window); 

	//load Gl so it configures Opengl
	gladLoadGL();
	glViewport(0, 0, 800, 800);



	// Create Vertex Shader Objext and get it refrenced
	GLuint	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach vertex shader sourec to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 

	//compile the vertex shader into machine code
	glCompileShader(vertexShader); 



	//Create fragment shader objext and get its refrence
	GLuint	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram(); 

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader); 

	glLinkProgram(shaderProgram);

	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);





	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glad_glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 








	// this is the color of the background innit
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// clean the back buffer and assign a color to it
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); 

		glfwSwapBuffers(window);


		// to take care of all evens, basicalky makes it responsive in some sense.
		glfwPollEvents();
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}