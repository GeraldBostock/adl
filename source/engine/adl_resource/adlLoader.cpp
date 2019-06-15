#include "adlLoader.h"

#include "adlMesh.h"
#include "adlModel.h"
#include "adlFont.h"
#include "adlTexture.h"
#include "adlTerrain.h"
#include "engine/adl_debug/adlLogger.h"
#include "engine/adl_resource/adlStatic_shader.h"
#include "adlCube_map.h"

#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_renderer/adlDebug_renderer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stdlib.h>
#include <time.h>  

adlLoader::adlLoader()
{
	srand(time(NULL));
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

	std::string model_folder_path = mesh_path;
	const size_t last_slash_idx = model_folder_path.rfind('/');
	model_folder_path = model_folder_path.erase(last_slash_idx, mesh_path.size()) + '/';

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

	process_ai_node(scene->mRootNode, scene, new_model, model_folder_path);

	const std::vector<adlMesh_shared_ptr>& meshes = new_model->get_all_meshes();
	new_model->set_bounding_box(generate_model_bounding_box(meshes));

	return new_model;
}

void adlLoader::process_ai_node(aiNode* node, const aiScene* scene, adlModel_shared_ptr model, const std::string& model_folder_location)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		adlMesh_shared_ptr new_mesh = process_mesh(mesh, scene);

		aiMaterial* mtl = scene->mMaterials[mesh->mMaterialIndex];
		if (scene->HasTextures())
		{
			aiTexture * text = scene->mTextures[mesh->mMaterialIndex];

			if (text != nullptr)
			{
				std::vector<unsigned char> pixel_array;
				for (unsigned int j = 0; j < text->mWidth * text->mHeight; ++j)
				{
					aiTexel pixel = text->pcData[j];
					/*pixel_array.push_back(pixel.r);
					pixel_array.push_back(pixel.g);
					pixel_array.push_back(pixel.b);
					pixel_array.push_back(pixel.a);*/
					pixel_array.push_back(1);
					pixel_array.push_back(1);
					pixel_array.push_back(1);
					pixel_array.push_back(1);
				}

				adlTexture_shared_ptr texture = MAKE_SHARED(adlTexture);
				glBindTexture(GL_TEXTURE_2D, texture->get_id());

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text->mWidth, text->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixel_array[0]);
				glGenerateMipmap(GL_TEXTURE_2D);

				texture->set_width(text->mWidth);
				texture->set_height(text->mHeight);
				texture->set_color_format(GL_RGBA);

				texture->set_pixel_array(pixel_array);

				new_mesh->set_texture(texture);
			}
		}

		if (true/*mtl != nullptr*/)
		{
			aiString path;
			//std::cout << mtl->GetTextureCount(aiTextureType_DIFFUSE) << std::endl;
			if (AI_SUCCESS != mtl->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL))
			{
			}
			std::string assimp_texture_path = std::string(path.C_Str());
			const size_t last_slash_idx = assimp_texture_path.rfind('\\');
			std::string texture_name = assimp_texture_path;
			if (last_slash_idx > 0 && last_slash_idx < assimp_texture_path.size())
			{
				texture_name = assimp_texture_path.substr(last_slash_idx, assimp_texture_path.size());
			}

			std::string texture_file_path = model_folder_location + texture_name;

			adlTexture_shared_ptr texture = MAKE_SHARED(adlTexture);
			load_texture_from_file(texture->get_id(), texture_file_path, texture);
			new_mesh->set_texture(texture);

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
		process_ai_node(node->mChildren[i], scene, model, model_folder_location);
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

	load_texture_from_file(texture->get_id(), texture_paths.first, texture);
	if (!texture_paths.second.empty())
	{
		load_texture_from_file(texture->get_specular_map_id(), texture_paths.second, texture);
	}

	return texture;
}

void adlLoader::load_texture_from_file(unsigned int texture_id, const std::string& file_path, adlTexture_shared_ptr texture)
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
		std::vector<unsigned char> pixel_array;
		for (unsigned int i = 0; i < width * height * color_channels; i++)
		{
			pixel_array.push_back(data[i]);
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, color_format, GL_UNSIGNED_BYTE, &pixel_array[0]);
		glGenerateMipmap(GL_TEXTURE_2D);

		texture->set_width(width);
		texture->set_height(height);
		texture->set_color_format(color_format);

		texture->set_pixel_array(pixel_array);
	}
	else
	{
		logger->log_error("Failed to load texture at " + file_path);
	}

	stbi_image_free(data);
}

adlScene_shared_ptr adlLoader::load_scene(const std::string& scene_path)
{
	adlScene_shared_ptr scene = scene_loader_.load_scene(scene_path);

	return scene;
}

adlTerrain_shared_ptr adlLoader::load_terrain(const std::string& terrain_path, const std::string& terrain_name)
{
	int width;
	int height;
	int color_channels;
	unsigned char* data = stbi_load(terrain_path.c_str(), &width, &height, &color_channels, 1);
	std::vector<float> heightfield;

	std::vector<Vertex> vertices;
	width = 256;
	height = 256;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			float y = 0;//(float)data[width * (j)+i] / 20.0f;
			heightfield.push_back(y);
			//heightfield.insert(heightfield.begin(), y);
			Vertex vertex(adlVec3(width / 2 - j - 0.5f, y, height / 2 - i - 0.5f), adlVec3(0, 1, 0), adlVec2(j, i));
			vertices.push_back(vertex);
		}
	}

	std::vector<unsigned int> indices;
	std::vector<adlVec3> faces;

	std::map<unsigned int, std::vector<adlVec3>> vertices_normals;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == height - 1 || j == width - 1)
			{
				continue;
			}
			int index = width * i + j;
			indices.push_back(index + 1);
			indices.push_back(index);
			indices.push_back(index + width);

			indices.push_back(index + 1);
			indices.push_back(index + width);
			indices.push_back(index + width + 1);

			adlVec3 edge1 = vertices[index + width].position - vertices[index].position;
			adlVec3 edge2 = vertices[index + 1].position - vertices[index].position;
			adlVec3 normal = adlMath::crossp(edge1, edge2);
			normal = normal.normalize();

			std::vector<adlVec3> normals = vertices_normals[index + 1];
			normals.push_back(normal);
			vertices_normals[index + 1] = normals;
			normals = vertices_normals[index];
			normals.push_back(normal);
			vertices_normals[index] = normals;
			normals = vertices_normals[index + width];
			normals.push_back(normal);
			vertices_normals[index + width] = normals;

			normals = vertices_normals[index + 1];
			normals.push_back(normal);
			vertices_normals[index + 1] = normals;
			normals = vertices_normals[index + width];
			normals.push_back(normal);
			vertices_normals[index + width] = normals;
			normals = vertices_normals[index + width + 1];
			normals.push_back(normal);
			vertices_normals[index + width + 1] = normals;

			faces.push_back(vertices[index + 1].position);
			faces.push_back(vertices[index].position);
			faces.push_back(vertices[index + width].position);

			faces.push_back(vertices[index + 1].position);
			faces.push_back(vertices[index + width].position);
			faces.push_back(vertices[index + width + 1].position);
		}
	}

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		std::vector<adlVec3> normals = vertices_normals[i];
		adlVec3 average_normal(0.0f);
		for (auto normal : normals)
		{
			average_normal = average_normal + normal;
		}
		average_normal = average_normal / normals.size();
		vertices[i].normal = average_normal;
	}

	std::vector<adlVec3> face_normals;

	for (unsigned int i = 0; i < faces.size(); i = i + 3)
	{
		adlVec3 edge1 = faces[i] - faces[i + 2];
		adlVec3 edge2 = faces[i + 1] - faces[i + 2];

		adlVec3 normal = adlMath::crossp(edge1, edge2);
		normal = normal.normalize();
		face_normals.push_back(normal);
		adlVec3 tri_center;
		tri_center.x = (faces[i].x + faces[i + 1].x + faces[i + 2].x) / 3.0f;
		tri_center.y = (faces[i].y + faces[i + 1].y + faces[i + 2].y) / 3.0f;
		tri_center.z = (faces[i].z + faces[i + 1].z + faces[i + 2].z) / 3.0f;
		face_normals.push_back(tri_center);
 	}

	adlTerrain_shared_ptr terrain = MAKE_SHARED(adlTerrain, width, height, vertices, indices, terrain_name, faces, face_normals, heightfield);

	return terrain;
}

adlCube_map_shared_ptr adlLoader::load_cube_map(const std::vector<std::string>& faces)
{
	adlLogger* logger = &adlLogger::get();

	adlCube_map_shared_ptr cube_map = MAKE_SHARED(adlCube_map);

	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map->get_id());

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			logger->log_error("Cube map texture failed to load at path: " + faces[i]);
			stbi_image_free(data);

			return nullptr;
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return cube_map;
}

adlBounding_box adlLoader::generate_model_bounding_box(const std::vector<adlMesh_shared_ptr>& meshes)
{
	float highest_y = meshes[0]->get_bounding_box().up_left_back().y;
	float lowest_y = meshes[0]->get_bounding_box().bottom_left_back().y;

	float highest_x = meshes[0]->get_bounding_box().bottom_right_back().x;
	float lowest_x = meshes[0]->get_bounding_box().bottom_left_back().x;

	float highest_z = meshes[0]->get_bounding_box().bottom_left_front().z;
	float lowest_z = meshes[0]->get_bounding_box().bottom_left_back().z;

	for (auto mesh : meshes)
	{
		adlBounding_box bb = mesh->get_bounding_box();

		if (highest_y < bb.up_left_back().y)
		{
			highest_y = bb.up_left_back().y;
		}
		if (lowest_y > bb.bottom_left_back().y)
		{
			lowest_y = bb.bottom_left_back().y;
		}

		if (highest_x < bb.bottom_right_back().x)
		{
			highest_x = bb.bottom_right_back().x;
		}
		if (lowest_x > bb.bottom_left_back().x)
		{
			lowest_x = bb.bottom_left_back().x;
		}

		if (highest_z < bb.bottom_left_front().z)
		{
			highest_z = bb.bottom_left_front().z;
		}
		if (lowest_z > bb.bottom_left_back().z)
		{
			lowest_z = bb.bottom_left_back().z;
		}
	}

	return adlBounding_box(adlVec2(highest_x, lowest_x), adlVec2(highest_y, lowest_y), adlVec2(highest_z, lowest_z));
}