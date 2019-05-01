#ifndef adl_terrain_texture_pack_h__
#define adl_terrain_texture_pack_h__

#include <vector>
#include <string>

#include "engine/adlShared_types.h"

class adlTerrain_texture_pack
{
public:
	adlTerrain_texture_pack(const std::string& name, adlTexture_shared_ptr tex1, adlTexture_shared_ptr tex2, 
		adlTexture_shared_ptr tex3, adlTexture_shared_ptr tex4);
	adlTerrain_texture_pack(const std::string& name, const std::vector<adlTexture_shared_ptr>& textures);

	~adlTerrain_texture_pack();

	const std::vector<adlTexture_shared_ptr>& get_textures();

private:
	std::string name_;
	std::vector<adlTexture_shared_ptr> textures_;
};

#endif //adl_terrain_texture_pack_h__