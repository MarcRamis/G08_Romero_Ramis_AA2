#pragma once


#include "Constants.h"

#include "Renderer.h"
#include "Audio.h"

#include "Collisions.h"
#include "InputManager.h"

#include <iostream>

class Scene
{
protected:
	
	Renderer* r = Renderer::GetInstance();
	Audio* au = Audio::GetInstance();

public:
	Scene();
	~Scene();
	
	virtual void Update(InputManager &input) {};
	virtual void Draw() {};
};