#pragma once
#include"Renderer.h"

class Texture
{
private:
	std::string file_path;
	unsigned char* img_buffer;
	unsigned int m_render_id;
	//bits per pixel
	int width, height, bpp;
public:
	Texture(const std::string& _path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline int get_width() const { return width; }
	inline int get_height() const { return height; }
	inline int get_bpp() const { return bpp; }
};
