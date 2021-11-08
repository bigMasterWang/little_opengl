#include"VertexArray.h"
#include"GL/glew.h"
#include"Renderer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_render_id);
	glBindVertexArray(m_render_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_render_id);
}


void VertexArray::Bind() const
{
	glBindVertexArray(m_render_id);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}


void VertexArray::SetLayout(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const std::vector<LayoutElement> a = layout.get_elements();
	for (int i = 0; i < a.size(); i++)
	{
		glCall(glEnableVertexAttribArray(i));
		glVertexAttribPointer(i, a[i].count, a[i].type, a[i].normalize, a[i].count * sizeof(a[i].type), a[i].pointer);
	}
}
