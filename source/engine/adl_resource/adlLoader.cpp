#include "adlLoader.h"

#include "adlMesh.h"
#include "adlModel.h"
#include "adlFont.h"
#include "adlTexture.h"
#include "engine/adl_debug/adlLogger.h"
#include "engine/adl_resource/adlStatic_shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

adlLoader::adlLoader()
{

}

adlLoader::~adlLoader()
{

}

adlShader_shared_ptr adlLoader::load_shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
	adlShader_shared_ptr new_shader = std::make_shared<adlStatic_shader>(vertex_shader_path, fragment_shader_path);
	return new_shader;
}

adlModel_shared_ptr adlLoader::load_model(const std::string& mesh_path, const std::string& model_name)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(mesh_path,
		aiProcess_Triangulate |
		aiProcess_FlipUVs
		);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		adlLogger* adl_logger = &adlLogger::get();
		adl_logger->log_error(importer.GetErrorString());
		return nullptr;
	}

	adlModel_shared_ptr new_model = std::make_shared<adlModel>(model_name);

	process_ai_node(scene->mRootNode, scene, new_model);

	return new_model;
}

void adlLoader::process_ai_node(aiNode* node, const aiScene* scene, adlModel_shared_ptr model)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		adlMesh_shared_ptr new_mesh = process_mesh(mesh, scene);

		aiMaterial* mtl = scene->mMaterials[mesh->mMaterialIndex];
		if (mtl != nullptr)
		{
			aiColor4D diffuse(0.0f, 0.0f, 0.0f, 0.0f);
			aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse);

			aiColor4D ambient(0.0f, 0.0f, 0.0f, 0.0f);
			aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient);

			aiColor4D specular(0.0f, 0.0f, 0.0f, 0.0f);
			aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular);

			float shine = 0.0f;
			aiGetMaterialFloat(mtl, AI_MATKEY_SHININESS, &shine);

			adlMaterial_shared_ptr material = MAKE_SHARED(adlMaterial);
			adlVec3 adlAmbient(ambient.r, ambient.g, ambient.b, 0);
			adlVec3 adlDiffuse(diffuse.r, diffuse.g, diffuse.b, 0);
			adlVec3 adlSpecular(specular.r, specular.g, specular.b, 0);

			material->set_material(adlAmbient, adlDiffuse, adlSpecular, shine);

			new_mesh->set_material(material);
		}
		else
		{
			adlMaterial_shared_ptr material = MAKE_SHARED(adlMaterial);
			material->set_material(adlVec3(0.2f), adlVec3(1), adlVec3(1), 80);

			new_mesh->set_material(material);
		}

		//new_mesh->set_material(material);

		model->add_mesh(new_mesh);
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		process_ai_node(node->mChildren[i], scene, model);
	}
}

adlMesh_shared_ptr adlLoader::process_mesh(aiMesh *mesh, const aiScene* scene)
{
	adlMesh_shared_ptr new_mesh = MAKE_SHARED(adlMesh);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	adlVec2 min_max_x(9999.f, -9999.f);
	adlVec2 min_max_y(9999.f, -9999.f);
	adlVec2 min_max_z(9999.f, -9999.f);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		adlVec3 vector;

		if (mesh->HasPositions())
		{
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			if (vector.x < min_max_x.x)
			{
				min_max_x.x = vector.x;
			}
			if (vector.x > min_max_x.y)
			{
				min_max_x.y = vector.x;
			}

			if (vector.y < min_max_y.x)
			{
				min_max_y.x = vector.y;
			}
			if (vector.y > min_max_y.y)
			{
				min_max_y.y = vector.y;
			}

			if (vector.z < min_max_z.x)
			{
				min_max_z.x = vector.z;
			}
			if (vector.z > min_max_z.y)
			{
				min_max_z.y = vector.z;
			}
		}
		else
		{
			vertex.position = adlVec3::zero();
		}

		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}
		else
		{
			vertex.normal = adlVec3::zero();
		}

		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			adlVec2 uv;
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
			vertex.uv = uv;
		}
		else
		{
			vertex.uv = adlVec2::zero();
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	new_mesh->add_vertices(vertices, indices);
	new_mesh->set_bounding_box(adlBounding_box(min_max_x, min_max_y, min_max_z));

	return new_mesh;
}

adlFont_shared_ptr adlLoader::load_font(const std::string& font_path)
{
	adlLogger* logger = &adlLogger::get();
	FT_Library ft;

	adlFont_shared_ptr font = std::make_shared<adlFont>();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	std::map<char, glyph>* characters = font->get_character_map();

	if (FT_Init_FreeType(&ft))
	{
		logger->log_error("Failed to initialize FreeType library");
	}

	FT_Face face;
	if (FT_New_Face(ft, font_path.c_str(), 0, &face))
	{
		logger->log_error("Failed to load font at " + font_path);
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	for (unsigned char c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			logger->log_error("Failed to load glyph " + c);
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		glyph character = {
			texture,
			adlVec2_i32(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			adlVec2_i32(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		characters->insert(std::pair<char, glyph>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return font;
}

adlTexture_shared_ptr adlLoader::load_texture(const std::pair<std::string, std::string>& texture_paths)
{
	adlTexture_shared_ptr texture = MAKE_SHARED(adlTexture);

	load_texture_from_file(texture->get_id(), texture_paths.first);
	load_texture_from_file(texture->get_specular_map_id(), texture_paths.second);

	return texture;
}

void adlLoader::load_texture_from_file(unsigned int texture_id, const std::string& file_path)
{
	adlLogger* logger = &adlLogger::get();
	logger->log_info("Loading texture at " + file_path);

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width;
	int height;
	int color_channels;
	unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &color_channels, 0);

	float color_format = GL_RGB;
	if (color_channels == 3)
	{
		color_format = GL_RGB;
	}
	else if (color_channels == 4)
	{
		color_format = GL_RGBA;
	}

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, color_format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		logger->log_error("Failed to load diffuse texture at " + file_path);
	}

	stbi_image_free(data);
}

adlScene_shared_ptr adlLoader::load_scene(const std::string& scene_path)
{
	adlScene_shared_ptr scene = scene_loader_.load_scene(scene_path);

	return scene;
}

void adlLoader::generate_bounding_box(adlVec2 min_max_x, adlVec2 min_max_y, adlVec2 min_max_z)
{

}