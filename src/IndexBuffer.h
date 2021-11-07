#pragma once


class IndexBuffer
{
private:
	unsigned int m_render_id;
	unsigned int count;
public:

	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	inline unsigned int get_count() { return count; };
};
