#include "InputManager.h"

InputData::InputData() {}

InputData::~InputData() {}

InputData* InputData::input = nullptr;

void InputData::UpdateDeltaTime() {
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
}

const float* InputData::GetDeltaTime() const { return &deltaTime; };

void InputData::SetScreenSize(VEC2 sSize) { screenSize = sSize; }
const VEC2* InputData::GetScreenSize() const { return &screenSize; }

VEC2 InputData::GetMouseCoords() { return mouseCoords; }
void InputData::SetMouseCoords(VEC2 coords) { mouseCoords = coords; }
void InputData::SetMouseCoords(int x, int y) {
	mouseCoords = { x, y };
}

bool InputData::isPressed(InputKeys key) {
	return keyboardPressed[(int)key];
}

bool InputData::JustPressed(InputKeys key) {
	return keyboardKeyDown[(int)key];
}

void InputData::SetKeyValue(InputKeys key, bool value) {
	if (!keyboardPressed[(int)key]) {
		keyboardKeyDown[(int)key] = value;
	}
	else {
		keyboardKeyDown[(int)key] = false;
	}
	keyboardPressed[(int)key] = value;
}

void InputData::SetFalseKeyDown() {
	for (int i = 0; i < (int)InputKeys::COUNT; i++) {
		keyboardKeyDown[i] = false;
	}
}