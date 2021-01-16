#include "InputManager.h"

//InputManager* InputManager::input = nullptr;

void InputManager::Update()
{
	SetFalseKeyDown();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			SetKeyValue(InputKeys::QUIT, true);
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) SetKeyValue(InputKeys::ESC, true);

			if (event.key.keysym.sym == SDLK_w) SetKeyValue(InputKeys::W, true);
			if (event.key.keysym.sym == SDLK_a) SetKeyValue(InputKeys::A, true);
			if (event.key.keysym.sym == SDLK_s) SetKeyValue(InputKeys::S, true);
			if (event.key.keysym.sym == SDLK_d) SetKeyValue(InputKeys::D, true);

			if (event.key.keysym.sym == SDLK_SPACE) SetKeyValue(InputKeys::SPACE, true);

			if (event.key.keysym.sym == SDLK_UP) SetKeyValue(InputKeys::UP, true);
			if (event.key.keysym.sym == SDLK_DOWN) SetKeyValue(InputKeys::DOWN, true);
			if (event.key.keysym.sym == SDLK_LEFT) SetKeyValue(InputKeys::LEFT, true);
			if (event.key.keysym.sym == SDLK_RIGHT) SetKeyValue(InputKeys::RIGHT, true);

			if (event.key.keysym.sym == SDLK_RCTRL) SetKeyValue(InputKeys::RIGHT_CTRL, true);
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE) SetKeyValue(InputKeys::ESC, false);

			if (event.key.keysym.sym == SDLK_w) SetKeyValue(InputKeys::W, false);
			if (event.key.keysym.sym == SDLK_a) SetKeyValue(InputKeys::A, false);
			if (event.key.keysym.sym == SDLK_s) SetKeyValue(InputKeys::S, false);
			if (event.key.keysym.sym == SDLK_d) SetKeyValue(InputKeys::D, false);

			if (event.key.keysym.sym == SDLK_SPACE) SetKeyValue(InputKeys::SPACE, false);

			if (event.key.keysym.sym == SDLK_UP) SetKeyValue(InputKeys::UP, false);
			if (event.key.keysym.sym == SDLK_DOWN) SetKeyValue(InputKeys::DOWN, false);
			if (event.key.keysym.sym == SDLK_LEFT) SetKeyValue(InputKeys::LEFT, false);
			if (event.key.keysym.sym == SDLK_RIGHT) SetKeyValue(InputKeys::RIGHT, false);

			if (event.key.keysym.sym == SDLK_RCTRL) SetKeyValue(InputKeys::RIGHT_CTRL, false);
			break;

		case SDL_MOUSEMOTION:
			SetMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) SetKeyValue(InputKeys::MOUSE_LEFT, true);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) SetKeyValue(InputKeys::MOUSE_LEFT, false);
			break;
		default:;
		}
	}
}

void InputManager::UpdateDeltaTime() {
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	deltaFrameTime = (clock() - lastFrameTime);
	if (deltaFrameTime >= MOVEMENT_FRAME_TIME)
	{
		lastFrameTime = clock();
		itsFrameTime = true;
	}
	else
		itsFrameTime = false;
	deltaFrameTime /= CLOCKS_PER_SEC;
}

const float* InputManager::GetDeltaTime() const { return &deltaTime; };

void InputManager::SetScreenSize(VEC2 sSize) { screenSize = sSize; }
const VEC2* InputManager::GetScreenSize() const { return &screenSize; }

VEC2 InputManager::GetMouseCoords() { return mouseCoords; }
void InputManager::SetMouseCoords(VEC2 coords) { mouseCoords = coords; }
void InputManager::SetMouseCoords(int x, int y) {
	mouseCoords = { x, y };
}

bool InputManager::isPressed(InputKeys key) {
	return keyboardPressed[(int)key];
}

bool InputManager::JustPressed(InputKeys key) {
	return keyboardKeyDown[(int)key];
}

void InputManager::SetKeyValue(InputKeys key, bool value) {
	if (!keyboardPressed[(int)key]) {
		keyboardKeyDown[(int)key] = value;
	}
	else {
		keyboardKeyDown[(int)key] = false;
	}
	keyboardPressed[(int)key] = value;
}

void InputManager::SetFalseKeyDown() {
	for (int i = 0; i < (int)InputKeys::COUNT; i++) {
		keyboardKeyDown[i] = false;
	}
}