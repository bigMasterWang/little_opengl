#pragma once
#include<vector>
#include"GL/glew.h"

struct LayoutElement
{
	unsigned int count;
	unsigned int type;
	unsigned char normalize;
};


class VertexBufferLayout
{
private:
	std::vector<LayoutElement> layout_elements;
	unsigned int stride;
public:
	VertexBufferLayout() :stride(0) {}
	const std::vector<LayoutElement> get_elements() const { return layout_elements; }

	inline unsigned int get_stride() const { return stride; }

	template<typename T>
	void push(unsigned int count)
	{

	}

	template<>
	void push<float>(unsigned int count)
	{
		layout_elements.push_back({ count, GL_FLOAT, GL_FALSE });
		stride += count * sizeof(GL_FLOAT);
	}

};
