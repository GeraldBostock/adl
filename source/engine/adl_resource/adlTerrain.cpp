#include "adlTerrain.h"

#include "engine/adl_resource/adlModel.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_helper/adlTimer.h"

#include <map>

adlTerrain::adlTerrain(int width, int height, const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const std::string& name,
	const std::vector<adlVec3>& faces, const std::vector<adlVec3>& face_normals, const std::vector<float>& heightfield)
	:	width_(width),
		height_(height),
		vertices_(vertices),
		indices_(indices),
		name_(name),
		faces_(faces),
		face_normals_(face_normals),
		heightfield_(heightfield),
		terrain_model_(nullptr)
{
	terrain_model_ = MAKE_SHARED(adlModel, "terrain");
	
	adlMesh mesh;
	mesh.add_vertices(vertices_, indices_);
	terrain_model_->add_mesh(mesh);
}

adlTerrain::~adlTerrain()
{

}

adlModel_shared_ptr adlTerrain::get_model()
{
	return terrain_model_;
}

const std::string& adlTerrain::get_name()
{
	return name_;
}

const Vertex& adlTerrain::get_vertex_at_index(int i, int j)
{
	return vertices_[width_ * i + j];
}

const std::vector<Vertex>& adlTerrain::get_vertices()
{
	return vertices_;
}

int adlTerrain::get_width()
{
	return width_;
}

int adlTerrain::get_height()
{
	return height_;
}

void adlTerrain::edit_vertices(const std::set<std::pair<int, int>>& vertex_indices, const std::vector<Vertex>& vertex_values)
{
	for (unsigned int i = 0; i < vertex_indices.size(); ++i)
	{
		std::pair<int, int> vertex_index = *std::next(vertex_indices.begin(), i);
		vertices_[vertex_index.first * width_ + vertex_index.second] = vertex_values[i];
		heightfield_[(width_ - (vertex_index.first + 1)) * width_ + (height_ - (vertex_index.second + 1))] = vertex_values[i].position.y;

		std::map<unsigned int, std::vector<adlVec3>> vertices_normals;
		for (int k = vertex_index.first - 1; k < vertex_index.first + 2; ++k)
		{
			for (int l = vertex_index.second - 1; l < vertex_index.second + 2; ++l)
			{
				if (k == height_ - 1 || l == width_ - 1 || k == -1 || l == -1)
				{
					continue;
				}
				int index = width_ * k + l;

				adlVec3 edge1 = vertices_[index + width_].position - vertices_[index].position;
				adlVec3 edge2 = vertices_[index + 1].position - vertices_[index].position;
				adlVec3 normal = adlMath::crossp(edge1, edge2);
				normal = normal.normalize();

				std::vector<adlVec3> normals = vertices_normals[index + 1];
				normals.push_back(normal);
				vertices_normals[index + 1] = normals;
				normals = vertices_normals[index];
				normals.push_back(normal);
				vertices_normals[index] = normals;
				normals = vertices_normals[index + width_];
				normals.push_back(normal);
				vertices_normals[index + width_] = normals;

				normals = vertices_normals[index + 1];
				normals.push_back(normal);
				vertices_normals[index + 1] = normals;
				normals = vertices_normals[index + width_];
				normals.push_back(normal);
				vertices_normals[index + width_] = normals;
				normals = vertices_normals[index + width_ + 1];
				normals.push_back(normal);
				vertices_normals[index + width_ + 1] = normals;

				std::vector<adlVec3> vertex_normals = vertices_normals[index];
				adlVec3 average_normal(0.0f);
				for (auto vertex_normal : vertex_normals)
				{
					average_normal = average_normal + vertex_normal;
				}
				if (!vertex_normals.empty())
				{
					average_normal = average_normal / vertex_normals.size();
					vertices_[index].normal = average_normal;
				}
			}
		}
	}

	adlModel_shared_ptr model = MAKE_SHARED(adlModel, "terrain");
	adlMesh mesh;
	mesh.add_vertices(vertices_, indices_);
	model->add_mesh(mesh);
	terrain_model_ = model;

	adlScene_manager* scn_mngr = &adlScene_manager::get();
	scn_mngr->set_terrain(heightfield_);
	/*std::vector<std::pair<int, int>> elevated_vertices;
	for (auto vertex : vertex_indices)
	{
		int iVertex = vertex.first;
		int jVertex = vertex.second;
		vertices_[iVertex * width_ + jVertex].position.y++;
		vertices_[(iVertex + 1) * width_ + jVertex].position.y++;
		vertices_[iVertex * width_ + jVertex + 1].position.y++;
		vertices_[(iVertex + 1) * width_ + jVertex + 1].position.y++;

		heightfield_[(width_ - (iVertex + 1)) * width_ + (height_ - (jVertex + 1))]++;
		heightfield_[(width_ - (iVertex + 2)) * width_ + (height_ - (jVertex + 1))]++;
		heightfield_[(width_ - (iVertex + 1)) * width_ + (height_ - (jVertex + 2))]++;
		heightfield_[(width_ - (iVertex + 2)) * width_ + (height_ - (jVertex + 2))]++;

		std::map<unsigned int, std::vector<adlVec3>> vertices_normals;
		for (int i = iVertex - 1; i < iVertex + 2; i++)
		{
			for (int j = jVertex - 1; j < jVertex + 2; j++)
			{
				if (i == height_ - 1 || j == width_ - 1)
				{
					continue;
				}
				int index = width_ * i + j;

				adlVec3 edge1 = vertices_[index + width_].position - vertices_[index].position;
				adlVec3 edge2 = vertices_[index + 1].position - vertices_[index].position;
				adlVec3 normal = adlMath::crossp(edge1, edge2);
				normal = normal.normalize();

				std::vector<adlVec3> normals = vertices_normals[index + 1];
				normals.push_back(normal);
				vertices_normals[index + 1] = normals;
				normals = vertices_normals[index];
				normals.push_back(normal);
				vertices_normals[index] = normals;
				normals = vertices_normals[index + width_];
				normals.push_back(normal);
				vertices_normals[index + width_] = normals;

				normals = vertices_normals[index + 1];
				normals.push_back(normal);
				vertices_normals[index + 1] = normals;
				normals = vertices_normals[index + width_];
				normals.push_back(normal);
				vertices_normals[index + width_] = normals;
				normals = vertices_normals[index + width_ + 1];
				normals.push_back(normal);
				vertices_normals[index + width_ + 1] = normals;

				std::vector<adlVec3> vertex_normals = vertices_normals[index];
				adlVec3 average_normal(0.0f);
				for (auto vertex_normal : vertex_normals)
				{
					average_normal = average_normal + vertex_normal;
				}
				if (!vertex_normals.empty())
				{
					average_normal = average_normal / vertex_normals.size();
					vertices_[index].normal = average_normal;
				}
			}
		}
	}

	adlModel_shared_ptr model = MAKE_SHARED(adlModel, "terrain");
	adlMesh mesh;
	mesh.add_vertices(vertices_, indices_);
	model->add_mesh(mesh);
	terrain_model_ = model;

	adlScene_manager* scn_mngr = &adlScene_manager::get();
	scn_mngr->set_terrain(heightfield_);*/
}

void adlTerrain::edit_vertex(int iVertex, int jVertex)
{
	adlTimer timer;

	vertices_[iVertex * width_ + jVertex].position.y++;
	vertices_[(iVertex + 1) * width_ + jVertex].position.y++;
	vertices_[iVertex * width_ + jVertex + 1].position.y++;
	vertices_[(iVertex + 1) * width_ + jVertex + 1].position.y++;

	heightfield_[(width_ - (iVertex + 1)) * width_ + (height_ - (jVertex + 1))]++;
	heightfield_[(width_ - (iVertex + 2)) * width_ + (height_ - (jVertex + 1))]++;
	heightfield_[(width_ - (iVertex + 1)) * width_ + (height_ - (jVertex + 2))]++;
	heightfield_[(width_ - (iVertex + 2)) * width_ + (height_ - (jVertex + 2))]++;

	std::map<unsigned int, std::vector<adlVec3>> vertices_normals;
	timer.start();
	for (int i = iVertex - 1; i < iVertex + 2; i++)
	{
		for (int j = jVertex - 1; j < jVertex + 2; j++)
		{
			if (i == height_ - 1 || j == width_ - 1)
			{
				continue;
			}
			int index = width_ * i + j;

			adlVec3 edge1 = vertices_[index + width_].position - vertices_[index].position;
			adlVec3 edge2 = vertices_[index + 1].position - vertices_[index].position;
			adlVec3 normal = adlMath::crossp(edge1, edge2);
			normal = normal.normalize();

			std::vector<adlVec3> normals = vertices_normals[index + 1];
			normals.push_back(normal);
			vertices_normals[index + 1] = normals;
			normals = vertices_normals[index];
			normals.push_back(normal);
			vertices_normals[index] = normals;
			normals = vertices_normals[index + width_];
			normals.push_back(normal);
			vertices_normals[index + width_] = normals;

			normals = vertices_normals[index + 1];
			normals.push_back(normal);
			vertices_normals[index + 1] = normals;
			normals = vertices_normals[index + width_];
			normals.push_back(normal);
			vertices_normals[index + width_] = normals;
			normals = vertices_normals[index + width_ + 1];
			normals.push_back(normal);
			vertices_normals[index + width_ + 1] = normals;

			std::vector<adlVec3> vertex_normals = vertices_normals[index];
			adlVec3 average_normal(0.0f);
			for (auto vertex_normal : vertex_normals)
			{
				average_normal = average_normal + vertex_normal;
			}
			if (!vertex_normals.empty())
			{
				average_normal = average_normal / vertex_normals.size();
				vertices_[index].normal = average_normal;
			}
		}
	}
	std::cout << timer.get_elapsed_milli_seconds() << std::endl;

	timer.start();


	std::vector<adlVec3> face_normals;


	std::cout << timer.get_elapsed_milli_seconds() << std::endl;

	timer.start();

	adlModel_shared_ptr model = MAKE_SHARED(adlModel, "terrain");
	adlMesh mesh;
	mesh.add_vertices(vertices_, indices_);
	model->add_mesh(mesh);
	terrain_model_ = model;

	std::cout << timer.get_elapsed_milli_seconds() << std::endl;

	timer.start();

	adlScene_manager* scn_mngr = &adlScene_manager::get();
	scn_mngr->set_terrain(heightfield_);

	std::cout << timer.get_elapsed_milli_seconds() << std::endl;

	timer.start();
}

void adlTerrain::calculate_normal(int i, int j)
{
	std::map<unsigned int, std::vector<adlVec3>> vertices_normals;

	{
		if (i == height_ - 1 || j == width_ - 1)
		{
			return;
		}
		int index = width_ * i + j;

		adlVec3 edge1 = vertices_[index + width_].position - vertices_[index].position;
		adlVec3 edge2 = vertices_[index + 1].position - vertices_[index].position;
		adlVec3 normal = adlMath::crossp(edge1, edge2);
		normal = normal.normalize();

		std::vector<adlVec3> normals = vertices_normals[index + 1];
		normals.push_back(normal);
		vertices_normals[index + 1] = normals;
		normals = vertices_normals[index];
		normals.push_back(normal);
		vertices_normals[index] = normals;
		normals = vertices_normals[index + width_];
		normals.push_back(normal);
		vertices_normals[index + width_] = normals;

		normals = vertices_normals[index + 1];
		normals.push_back(normal);
		vertices_normals[index + 1] = normals;
		normals = vertices_normals[index + width_];
		normals.push_back(normal);
		vertices_normals[index + width_] = normals;
		normals = vertices_normals[index + width_ + 1];
		normals.push_back(normal);
		vertices_normals[index + width_ + 1] = normals;
	}

	for (unsigned int i = 0; i < vertices_.size(); i++)
	{
		std::vector<adlVec3> normals = vertices_normals[i];
		adlVec3 average_normal(0.0f);
		for (auto normal : normals)
		{
			average_normal = average_normal + normal;
		}
		if (!normals.empty())
		{
			average_normal = average_normal / normals.size();
			vertices_[i].normal = average_normal;
		}
	}
}