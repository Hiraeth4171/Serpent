#include <iostream>

#include "Renderer.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "Error: (" << error << "):" << function << " | " << file << " : " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::ColorClear (vec4<int> Color) const 
{
	GLCall(glClearColor(Color.R/255.0f, Color.G/255.0f, Color.B/ 255.0f, Color.A/255.0f));
	Clear();
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
