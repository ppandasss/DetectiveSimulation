#pragma once

#include "GameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"

class AnimGameObject : public GameObject
{
public:	AnimGameObject(const std::string& name, const std::string& texturePath,const int spriteSheetRow,const int spriteSheetCol)
		: GameObject(name)
	{
		numFramesPerRow = spriteSheetRow;

		numFramesPerColumn = spriteSheetCol;
		frameIndex = 0;
		texture_id = Engine::LoadTexture(texturePath);
	}

	virtual void Render() override
	{
		// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
		float vertices[] = {
			// positions          // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
		};

		glm::mat4 model {1};
		float frameWidth = 1.0f / static_cast<float>(numFramesPerRow);
		float frameHeight = 1.0f / static_cast<float>(numFramesPerColumn);
		float xOffset = static_cast<float>(frameIndex % numFramesPerRow) * frameWidth;
		float yOffset = static_cast<float>(frameIndex / numFramesPerRow) * frameHeight;
		model = glm::translate(model,glm::vec3(xOffset, yOffset, 0.0f));
		model = glm::translate(model, m_position);
		model = glm::rotate(model, m_orientation, glm::vec3(0, 0, 1));
		model = glm::scale(model, m_scale);



		Application::Get().DrawTexture(texture_id, model);
		//Engine::DrawTexture(texture_id, glm::mat4{1});
	}

private:
	int texture_id;
	int frameIndex;
	int numFramesPerRow;
	int numFramesPerColumn;
	

};