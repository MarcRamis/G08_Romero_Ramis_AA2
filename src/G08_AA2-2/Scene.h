#pragma once

#include "Collisions.h"
#include "Constants.h"
#include "Renderer.h"
#include "Audio.h"

class Scene
{
protected:

	Renderer* r = Renderer::GetInstance();
	Audio* au = Audio::GetInstance();

public:
	Scene();
	~Scene();
	
	virtual void Update() {};
	virtual void Draw() {};
};