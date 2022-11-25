#pragma once
#include "VertexBuffer.h"
class VertexBufferLayout;

class VertexArrary {
private:
	unsigned int m_RendererID;
public:
	VertexArrary();
	~VertexArrary();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void UnBind() const;
};