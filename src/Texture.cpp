#include"Texture.h"
#include"vecdor/stb_image/stb_image.h"


Texture::Texture(const std::string& _path) :file_path(_path), width(0), height(0), bpp(0), m_render_id(0), img_buffer(nullptr)
{
	stbi_set_flip_vertically_on_load(1);
	//rgba
	img_buffer = stbi_load(file_path.c_str(), &width, &height, &bpp, 4);
	if (img_buffer == nullptr)
	{
		std::cout << stbi_failure_reason() << std::endl;
		return;
	}


	glCall(glGenTextures(1, &m_render_id));
	glCall(glBindTexture(GL_TEXTURE_2D, m_render_id));

	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_buffer));
	glCall(glBindTexture(GL_TEXTURE_2D, 0));


	if (img_buffer)
		stbi_image_free(img_buffer);

}
Texture::~Texture()
{
	glDeleteTextures(1, &m_render_id);
}
void Texture::Bind(unsigned int slot) const
{
	glCall(glActiveTexture(GL_TEXTURE0 + slot));
	glCall(glBindTexture(GL_TEXTURE_2D, m_render_id));
}
void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
