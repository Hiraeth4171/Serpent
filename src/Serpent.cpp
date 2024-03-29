#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include <iostream>
#include "Interpreter.h"

#define WIDTH 640
#define HEIGHT 480


int main(int argc, char * argv[]) {


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Serpent", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW_NOT_OK" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		/*float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;

		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		Shader shader("./res/shaders/Base.shader");
		shader.Bind();
		
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();*/

		Renderer renderer;
		Page page(&renderer, WIDTH, HEIGHT, (char*)"Serpent");
		Generator generator(&page);
		Interpreter interpeter(generator);
		interpeter.Interpret(argc, argv);
		// going to need an AddObject function of some sort


		/*float r = 0.0f;
		float increment = 0.05f;*/

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */

			//shader.Bind();
			//shader.SetUniform4f("u_Color", r, 0.3f, 0.6f, 0.1f);
			
			generator.m_Page->Draw();
			//renderer.Draw(va, ib, shader);

			//if (r > 1.0f || r < 0.0f) increment *= -1;
			
			//r += increment;
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}