#include "adlLight_editor.h"

#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adlInput.h"
#include "engine/adl_entities/adlLight.h"
#include "engine/adl_entities/adlSun.h"
#include "engine/adl_Entities/adlPoint_light.h"

adlLight_editor::adlLight_editor()
{
}

adlLight_editor::~adlLight_editor()
{
}

void adlLight_editor::update(adlSun_shared_ptr sun, std::vector<adlPoint_light_shared_ptr>& point_lights)
{

	ImGui::Begin("Light Editor");

	if (ImGui::CollapsingHeader("Sun"))
	{
		ImGui::Indent();
		sunStats(sun);
		ImGui::Unindent();
	}
		
	if (ImGui::CollapsingHeader("Point Lights"))
	{
		ImGui::Indent();

		for (size_t i = 0; i < point_lights.size(); i++)
		{	
			std::string name = point_lights[i]->get_name();
			if (ImGui::CollapsingHeader(name.c_str()))
			{
				ImGui::Indent();
				ImGui::Text("Point Light (%d)", i);
				lightStats(point_lights[i], i);
				ImGui::Unindent();
			}
		}
		ImGui::Unindent();
	}

	ImGui::End();

}

void adlLight_editor::sunStats(adlSun_shared_ptr sun)
{
	adlVec3 sun_position = sun->get_position();
	adlVec3 sun_rotation = sun->get_rotation();
	adlVec3 sun_scale = sun->getScale();

	std::string id = "id: " + std::to_string(sun->get_id());
	ImGui::Text(id.c_str());

	ImGui::Text("Sun");
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader("Position"))
		{
			ImGui::Text("Position(x,y,z)");
			float sunPos[3] = { sun_position.x, sun_position.y, sun_position.z };
			ImGui::InputFloat3("##SunPos", &sunPos[0], 2);
			sun_position = adlVec3(sunPos[0], sunPos[1], sunPos[2]);
			sun->set_position(sun_position);
		}
		if (ImGui::CollapsingHeader("Rotation"))
		{
			ImGui::Text("Rotation(x,y,z)");
			float sunRot[3] = { sun_rotation.x, sun_rotation.y, sun_rotation.z };
			ImGui::InputFloat3("##SunRot", &sunRot[0], 2);
			sun_rotation = adlVec3(sunRot[0], sunRot[1], sunRot[2]);
			sun->set_rotation(sun_rotation);
		}
		if (ImGui::CollapsingHeader("Scale"))
		{
			ImGui::Text("Scale(x,y,z)");
			float sunScale[3] = { sun_scale.x, sun_scale.y, sun_scale.z };
			ImGui::InputFloat3("##SunScale", &sunScale[0], 2);
			sun_scale = adlVec3(sunScale[0], sunScale[1], sunScale[2]);
			sun->set_scale(sun_scale);
		}
		ImGui::Unindent();
	}
	if (ImGui::CollapsingHeader("Light Properties"))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader("Light Reflections"))
		{
			ImGui::Indent();

			ImGui::Text("Exp: Ambient, Diffuse, Specular");

			if (ImGui::BeginMenu("Reflections"))
			{
				float lightAmbient[3] = { sun->getAmbient().x, sun->getAmbient().y, sun->getAmbient().z };
				float lightDiffuse[3] = { sun->getDiffuse().x, sun->getDiffuse().y, sun->getDiffuse().z };
				float lightSpecular[3] = { sun->getSpecular().x, sun->getSpecular().y, sun->getSpecular().z };

				if (ImGui::ColorEdit3("Ambient", lightAmbient))
				{
					adlVec3 ambientTemp(lightAmbient[0], lightAmbient[1], lightAmbient[2]);
					sun->setAmbient(ambientTemp);
				}
				if (ImGui::ColorEdit3("Diffuse", lightDiffuse))
				{
					adlVec3 diffuseTemp(lightDiffuse[0], lightDiffuse[1], lightDiffuse[2]);
					sun->setDiffuse(diffuseTemp);
				}

				if (ImGui::ColorEdit3("Specular", lightSpecular))
				{
					adlVec3 specularTemp(lightSpecular[0], lightSpecular[1], lightSpecular[2]);
					sun->setSpecular(specularTemp);
				}

				ImGui::EndMenu();
			}

			ImGui::Unindent();
		}
		if (ImGui::CollapsingHeader("Sun Light Properties"))
		{
			ImGui::Indent();

			ImGui::Text("Property");

			ImGui::Unindent();
		}
		ImGui::Unindent();
	}
}

void adlLight_editor::lightStats(adlPoint_light_shared_ptr pointLight, int index)
{
	adlVec3 light_position = pointLight->getPosition();
	adlVec3 light_rotation = pointLight->getRotation();
	adlVec3 light_scale = pointLight->getScale();

	std::string id = "id: " + std::to_string(pointLight->get_id());
	ImGui::Text(id.c_str());

	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader("Position"))
		{
			ImGui::Text("Position(x,y,z)");

			std::string label = "##PointLightPos" + std::to_string(index + 1);

			float lightPos[3] = { light_position.x, light_position.y, light_position.z };
			ImGui::InputFloat3(label.data(), &lightPos[0], 2);
			light_position = adlVec3(lightPos[0], lightPos[1], lightPos[2]);
			pointLight->set_position(light_position);
		}
		if (ImGui::CollapsingHeader("Rotation"))
		{
			ImGui::Text("Rotation(x,y,z)");

			std::string label = "##PointLightRot" + std::to_string(index + 1);

			float lightRot[3] = { light_rotation.x, light_rotation.y, light_rotation.z };
			ImGui::InputFloat3(label.data(), &lightRot[0], 2);
			light_rotation = adlVec3(adlMath::deg_to_rad(lightRot[0]), adlMath::deg_to_rad(lightRot[1]), adlMath::deg_to_rad(lightRot[2]));
			pointLight->set_rotation(light_rotation);
		}
		if (ImGui::CollapsingHeader("Scale"))
		{
			ImGui::Text("Scale(x,y,z)");

			std::string label = "##PointLightScale" + std::to_string(index + 1);

			float lightScale[3] = { light_scale.x, light_scale.y, light_scale.z };
			ImGui::InputFloat3(label.data(), &lightScale[0], 2);
			light_scale = adlVec3(lightScale[0], lightScale[1], lightScale[2]);
			pointLight->setScale(light_scale);
		}
		ImGui::Unindent();
	}
	if (ImGui::CollapsingHeader("Light Properties"))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader("Light Reflections"))
		{
			ImGui::Indent();

			ImGui::Text("Exp: Ambient, Diffuse, Specular");

			if (ImGui::BeginMenu("Reflections"))
			{
				float lightAmbient[3] = { pointLight->getAmbient().x, pointLight->getAmbient().y, pointLight->getAmbient().z };
				float lightDiffuse[3] = { pointLight->getDiffuse().x, pointLight->getDiffuse().y, pointLight->getDiffuse().z };
				float lightSpecular[3] = { pointLight->getSpecular().x, pointLight->getSpecular().y, pointLight->getSpecular().z };

				if (ImGui::ColorEdit3("Ambient", lightAmbient))
				{
					adlVec3 ambientTemp(lightAmbient[0], lightAmbient[1], lightAmbient[2]);
					pointLight->setAmbient(ambientTemp);
				}
				if (ImGui::ColorEdit3("Diffuse", lightDiffuse))
				{
					adlVec3 diffuseTemp(lightDiffuse[0], lightDiffuse[1], lightDiffuse[2]);
					pointLight->setDiffuse(diffuseTemp);
				}

				if (ImGui::ColorEdit3("Specular", lightSpecular))
				{
					adlVec3 specularTemp(lightSpecular[0], lightSpecular[1], lightSpecular[2]);
					pointLight->setSpecular(specularTemp);
				}

				ImGui::EndMenu();
			}

			ImGui::Unindent();
		}
		if (ImGui::CollapsingHeader("Point Light Properties"))
		{
			ImGui::Text("Constant: %d | Linear: %d | Quadratic: %d", pointLight->get_constant(), pointLight->get_linear (), pointLight->get_quadratic());

			ImGui::Indent();
			if (ImGui::CollapsingHeader("Constant Property"))
			{
				ImGui::Indent();

				ImGui::Text("Constant(0f, 50f)");

				float lightConstant = pointLight->get_constant();

				ImGui::SliderFloat("##Constant", &lightConstant, 0.0f, 50.0f);
				pointLight->set_constant(lightConstant);

				ImGui::Unindent();

			}

			if (ImGui::CollapsingHeader("Linear Property"))
			{
				ImGui::Indent();

				ImGui::Text("Linear(0f, 1f)");

				float lightLinear = pointLight->get_linear();

				ImGui::SliderFloat("##Linear", &lightLinear, 0.0f, 1.0f);
				pointLight->set_linear(lightLinear);

				ImGui::Unindent();

			}
			if (ImGui::CollapsingHeader("Quadratic Property"))
			{
				ImGui::Indent();

				ImGui::Text("Quadratic(0f, 1f)");

				float lightQuadratic = pointLight->get_quadratic();

				ImGui::SliderFloat("##Quadratic", &lightQuadratic, 0.0f, 1.0f);
				pointLight->set_quadratic(lightQuadratic);

				ImGui::Unindent();

			}

			ImGui::Unindent();
		}
		ImGui::Unindent();
	}
}
