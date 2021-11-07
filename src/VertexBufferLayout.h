#pragma once
#include<vector>
#include"GL/glew.h"

struct LayoutElement
{
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0)
	unsigned int count;
	unsigned int type;
	unsigned char normalize;
	const void* pointer;
};


class VertexBufferLayout
{
private:
	std::vector<LayoutElement> layout_elements;
public:
	const std::vector<LayoutElement> get_elements() const { return layout_elements; }

	template<typename T>
	void push(unsigned int count)
	{

	}

	template<>
	void push<float>(unsigned int count)
	{
		layout_elements.push_back(LayoutElement{ count, GL_FLOAT, GL_FALSE, 0 });
	}
};
