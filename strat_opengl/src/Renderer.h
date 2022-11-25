#pragma once
#include <iostream>
#include <glad/glad.h>

#include "VertexArrary.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLogCall(#x,__FILE__,__LINE__))
void GLClearError();
bool GLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const ;
    void Draw(const VertexArrary& va, const IndexBuffer& ib, const Shader& shader);
};