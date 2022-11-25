#include "VertexArrary.h"
#include "VertexBufferLayout.h"

VertexArrary::VertexArrary()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArrary::~VertexArrary()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArrary::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type,element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArrary::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArrary::UnBind() const
{
	GLCall(glBindVertexArray(0));
}
