#pragma once


class IndexBuffer
{
private:
	unsigned int m_render_id;
	int count;
public:

	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	inline int get_count() const { return count; };
};
