#include "Renderer.h"

void GLClearError()
{
	while (glGetError() != 0);
}
bool GLogCall(const char* function, const char* file, int line)
{
	while (unsigned int error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "):" << function << " " << file << " " << line << std::endl;
		return false;
	}
	return true;
}


void Renderer::Clear() const
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArrary& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
