#include"VertexBuffer.h"
#include"Renderer.h"

VertexBuffer::VertexBuffer(const void* data, float size)
{
	glCall(glGenBuffers(1, &m_render_id));
	glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_render_id);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
}
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
