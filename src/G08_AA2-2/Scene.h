#pragma once

#include "Constants.h"
#include "Renderer.h"
#include "Audio.h"

class Scene
{
private:

public:
	Scene();
	~Scene();
	
	virtual void Update() {};
	virtual void Draw() {};
};