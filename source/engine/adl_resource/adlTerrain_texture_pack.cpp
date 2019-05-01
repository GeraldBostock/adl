#include "adlTerrain_texture_pack.h"

#include "adlTexture.h"
#include "engine/adlShared_types.h"

adlTerrain_texture_pack::adlTerrain_texture_pack(const std::string& name, adlTexture_shared_ptr tex1,
	adlTexture_shared_ptr tex2, adlTexture_shared_ptr tex3, adlTexture_shared_ptr tex4) 
{
	name_ = name;

	textures_.push_back(tex1);
	textures_.push_back(tex2);
	textures_.push_back(tex3);
	textures_.push_back(tex4);
}

adlTerrain_texture_pack::adlTerrain_texture_pack(const std::string& name, const std::vector<adlTexture_shared_ptr>& textures)
{
	name_ = name;
	for (auto texture : textures)
	{
		textures_.push_back(texture);
	}
}

adlTerrain_texture_pack::~adlTerrain_texture_pack()
{
	textures_.clear();
}

const std::vector<adlTexture_shared_ptr>& adlTerrain_texture_pack::get_textures()
{
	return textures_;
}