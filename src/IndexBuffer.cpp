#include"IndexBuffer.h"
#include"GL/glew.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : count(count)
{
	glGenBuffers(1, &m_render_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_render_id);
}
void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id);
}
void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
