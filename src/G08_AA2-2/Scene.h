#pragma once


#include "Constants.h"

#include "Renderer.h"
#include "Audio.h"

#include "Collisions.h"
#include "InputManager.h"

#include <iostream>

class Scene
{
public:
	enum class ESceneState { CLICK_MENU, CLICK_PLAY_LV1, CLICK_PLAY_LV2, CLICK_RANKING, CLICK_EXIT, CLICK_QUIT, RUNNING };
	
protected:
	
	ESceneState state = Scene::ESceneState::RUNNING;
	Renderer* r = Renderer::GetInstance();
	Audio* au = Audio::GetInstance();

public:
	Scene();
	~Scene();
	
	virtual void Update(InputManager &input) {};
	virtual void Draw() {};
	
	inline const ESceneState* GetState() { return &state; };
	void SetState(ESceneState _state) { state = _state; };
};