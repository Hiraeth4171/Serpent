#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "./Page/utils/types.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

void GLClearError();

bool GLCheckError(const char* function, const char* file, int line);

class Renderer
{
private:


public:
	Renderer();
	~Renderer();
	void Clear() const;
	void ColorClear(vec4<int> Color) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
