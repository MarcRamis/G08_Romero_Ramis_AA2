
#include "Renderer.h"

Renderer::Renderer()
{
	// SDL --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	m_window = SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if (m_window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	//IMG --- INIT ---
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_imageinit";

	//TTF --- INIT ---
	if (TTF_Init() != 0) throw"No es pot inicialitzar SDL_ttf";
};
Renderer::~Renderer()
{
	for (auto &t : m_textureData) SDL_DestroyTexture(t.second), t.second = nullptr;
	for (auto &f : m_fontData) TTF_CloseFont(f.second), f.second = nullptr;
	for (auto& f : m_rects) { delete f.second; f.second = nullptr; };

	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;

	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

};

void Renderer::Clear() { SDL_RenderClear(m_renderer); };
void Renderer::Render() { SDL_RenderPresent(m_renderer); };

Renderer* Renderer::renderer = nullptr;

const SDL_Rect Renderer::MyRect2SDL(const RECT* r) { return { r->x, r->y, r->w, r->h }; }
const RECT Renderer::RectSDL2My(const SDL_Rect* r) { return RECT(r->x, r->y, r->w, r->h); }

void Renderer::LoadFont(const Font &font) {
	TTF_Font *ttfFont{ TTF_OpenFont(font.path.c_str(), font.size) };
	if (ttfFont == nullptr) throw"No espot inicialitzar TTF_Font";
	m_fontData[font.id] = ttfFont;
};
void Renderer::LoadTexture(const std::string &id, const std::string &path) {
	SDL_Texture *texture{ IMG_LoadTexture(m_renderer, path.c_str()) };
	if (texture == nullptr) throw "No s'han pogut crear les textures";
	m_textureData[id] = texture;
};
VEC2 Renderer::LoadTextureText(const std::string& fontId, Text text) {
	SDL_Surface* tmpSurf = TTF_RenderText_Blended(m_fontData[fontId], text.text.c_str(), SDL_Color{ text.color.r, text.color.g, text.color.b,text.color.a });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_DestroyTexture(m_textureData[text.id]);
	m_textureData[text.id] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf); //hace un new
	return { tmpSurf->w,tmpSurf->h };
};
void Renderer::LoadRect(const std::string& idRect, const RECT &rect) {
	m_rects[idRect] = new SDL_Rect{ rect.x,rect.y,rect.w,rect.h };
};

VEC2 Renderer::GetTextureSize(const std::string &id) {
	int w; int h;
	SDL_QueryTexture(m_textureData[id], NULL, NULL,&w, &h);
	return {w, h};
};

void Renderer::PushImage(const std::string &id, const std::string &idRect) {
	SDL_RenderCopy(m_renderer, m_textureData[id], nullptr, m_rects[idRect]);
}
void Renderer::PushImage(const std::string& id, const RECT* rectPos) {
	SDL_RenderCopy(m_renderer, m_textureData[id], nullptr, &MyRect2SDL(rectPos));
}
void Renderer::PushSprite(const std::string &id, const std::string &idRectSprite,const std::string &idRectPos) {

	SDL_RenderCopy(m_renderer, m_textureData[id],m_rects[idRectSprite], m_rects[idRectPos]);
}
void Renderer::PushSprite(const std::string& id, const RECT* rectSprite, const RECT* rectPos)
{	
	SDL_RenderCopy(m_renderer, m_textureData[id], &MyRect2SDL(rectSprite), &MyRect2SDL(rectPos));
}
void Renderer::PushRotatedSprite(const std::string & id, const std::string& idRectSprite, const std::string& idRectPos ,float angle){
	SDL_Point center = { m_rects[idRectPos]->w / 2, m_rects[idRectPos]->h / 2 };
	SDL_RenderCopyEx(m_renderer, m_textureData[id], m_rects[idRectSprite], m_rects[idRectPos], angle, &center, SDL_FLIP_NONE);
}

void Renderer::SetRenderDrawColor(int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
}
void Renderer::SetRenderDrawColor(const Color &c)
{
	SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, 255);
}
void Renderer::SetTexture(const std::string& id, const std::string& newID)
{
	m_textureData[id] = m_textureData[newID];
}

void Renderer::SetRect(const std::string& idRect, const RECT& rect)
{
	m_rects[idRect]->x = rect.x;
	m_rects[idRect]->y = rect.y;
	m_rects[idRect]->w = rect.w;
	m_rects[idRect]->h = rect.h;
}
RECT Renderer::GetRect(const std::string& idRect)
{
	RECT rect;
	rect.x = m_rects[idRect]->x;
	rect.y = m_rects[idRect]->y;
	rect.w = m_rects[idRect]->w;
	rect.h = m_rects[idRect]->h;
	
	return {rect.x, rect.y, rect.w, rect.h};
}