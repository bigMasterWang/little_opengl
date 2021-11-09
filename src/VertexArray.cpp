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
	unsigned int offset = 0;
	for (int i = 0; i < a.size(); i++)
	{
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), 0);
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, a[i].count, a[i].type, a[i].normalize, layout.get_stride(), (const void*)offset);
		offset += a[i].count * sizeof(a[i].type);
	}
}
