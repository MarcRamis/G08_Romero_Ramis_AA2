#include "InputManager.h"

InputManager::InputManager() {}

InputManager::~InputManager() {}

InputManager* InputManager::input = nullptr;

void InputManager::UpdateDeltaTime() {
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
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