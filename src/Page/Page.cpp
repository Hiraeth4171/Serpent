#include "Page.h"
#include "../IndexBuffer.h"
#include "../VertexBufferLayout.h"

Page::Page(Renderer* renderer, vec4<int> BGColor, int width = 640, int height = 480, char* title = (char*)"Untitled") {
	m_Renderer = renderer;
	m_BackgroundColor = BGColor;
	m_width = width;
	m_height = height;
	m_title = title;
}

Page::Page(Renderer* renderer, int width = 640, int height = 480, char* title = (char*)"Untitled") {
	m_Renderer = renderer;
	m_width = width;
	m_BackgroundColor = {0,0,0,255};
	m_height = height;
	m_title = title;
}

Page::~Page()
{
}

vec2 Page::OpenGLToScreen(vec2f OpenGL)
{
	vec2 out(0,0);
	out.x = (int)(((OpenGL.x +1)/2) * m_width);
	out.y = (int)(((OpenGL.y +1)/2) * m_height);
	return out;
}

vec2f Page::ScreenToOpenGL(vec2 Screen)
{
	// TODO LOOK UP THE PROPER WAY TO MAP THIS BECAUSE OTHERWISE THIS WON'T WORK
	vec2f out;
	out.x = ((float)((float)Screen.x / (float)m_width)*2.0f)-1.0f;
	out.y = ((float)((float)Screen.y / (float)m_height)*-2.0f)+1.0f;
	printf("[X] Screen Position: %d, %d\n", Screen.x, Screen.y);
	printf("[X] OpenGL Position: %f, %f\n", out.x, out.y);
	return out;
}

void Page::Draw()
{
	m_Renderer->ColorClear(m_BackgroundColor);
	for (int i = 0; i < m_Objects.size(); ++i)
	{
		Object obj = m_Objects.Children[i];
		VertexArray va;
		VertexBuffer vb(obj.Rect, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;

		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		
		IndexBuffer ib(obj.indices, 6);
		
		Shader shader("res/shaders/Base.shader");
		shader.Bind();
		
		// obj.style.backgroundColor; // set uniform

		shader.SetUniform4f("u_Color", obj.style.backgroundColor.R / 255.0f, obj.style.backgroundColor.G / 255.0f, obj.style.backgroundColor.B / 255.0f, obj.style.backgroundColor.A / 255.0f);
		
		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		m_Renderer->Draw(va, ib, shader);
	}
}

//void Page::Load() {
//
//}

void Page::AddObject(Object* obj)
{
	vec2f opengl = ScreenToOpenGL(obj->style.position);
	vec2f span = ScreenToOpenGL(obj->style.position + obj->style.span);

	obj->Rect[0] = (float)opengl.x;
	obj->Rect[1] = (float)opengl.y;

	obj->Rect[2] = (float)opengl.x + span.x;
	obj->Rect[3] = (float)opengl.y;

	obj->Rect[4] = (float)opengl.x + span.x;
	obj->Rect[5] = (float)opengl.y + span.y;
	
	obj->Rect[6] = (float)opengl.x;
	obj->Rect[7] = (float)opengl.y + span.y;

	for (int i = 0; i < 4; i++) printf("[%d]: %.4f, %.4f\n", i, obj->Rect[i], obj->Rect[i + 1]);

	m_Objects.addObject(obj);
}
