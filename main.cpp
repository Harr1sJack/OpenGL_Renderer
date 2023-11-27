#include"Model.h"

int winWidth = 1000;
int winHeight = 1000;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "OpenGL", NULL, NULL);
	
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, winWidth, winHeight);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag","Default");
	Shader lightShader("light.vert","light.frag","Light");

	//shaderProgram.Activate();
	lightShader.Activate();

	//to enable depth buffer
	glEnable(GL_DEPTH_TEST);
	Camera camera(winWidth, winHeight, glm::vec3(0.0f, 0.0f, 2.0f));
	
	Model skeleton("models/Skeleton/skeleton.gltf");
	Model light("models/light/light.gltf");
	Model wood("models/wood/wood.gltf");

	glm::vec3 bgColor = glm::vec3(0.85f, 0.85f, 1.0f);
	

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(bgColor.x, bgColor.y, bgColor.z,1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.01f, 100.0f);

		glm::vec3 lightPos = glm::vec3(3.0f, 6.0f, 0.0f);
		glm::vec4 lightCol = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	    shaderProgram.Activate();
		glUniform3fv(glGetUniformLocation(shaderProgram.ID, "bgColor"), 1, glm::value_ptr(bgColor));
		glUniform3fv(glGetUniformLocation(shaderProgram.ID, "camPos"), 1, glm::value_ptr(camera.position));
		glUniform3fv(glGetUniformLocation(shaderProgram.ID, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform4fv(glGetUniformLocation(shaderProgram.ID, "lightColor"), 1, glm::value_ptr(lightCol));

		lightShader.Activate();
		
		glUniform4fv(glGetUniformLocation(lightShader.ID, "lightColor"), 1, glm::value_ptr(lightCol));

		light.Draw(lightShader, camera,lightPos);
		skeleton.Draw(shaderProgram, camera, glm::vec3(0.0f, 0.0f, 0.0f));
		wood.Draw(shaderProgram, camera, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f));


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	shaderProgram.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}