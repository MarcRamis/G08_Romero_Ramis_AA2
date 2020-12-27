#pragma once

#include <string>
#include <map>
#include <unordered_map>

// Game general information
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 704

// -- GAME TIME CONFIG --
const int FPS{ 60 };

// -- MENU LINE SPACING--
const int TEXTSIZE_MENU{ 6 };
const int TEXT_LINESPACING_MENU{ 15 };

// -- TEXTURE|RECT NAMES --
const std::string T_BG{ "Background" };
const std::string T_TITLE{ "TitleGame" };
//const std::string T_PLAYERS{ "Players" };

// -- MENU BUTTONS
const std::string T_BTN_PLAY_LV1{ "BtnPlayLv1" };
const std::string T_BTN_PLAY_LV1_N{ "BtnPlayLv1N" };
const std::string T_BTN_PLAY_LV1_H{ "BtnPlayLv1H" };
const std::string T_BTN_PLAY_LV2{ "BtnPlayLv2" };
const std::string T_BTN_PLAY_LV2_N{ "BtnPlayLv2N" };
const std::string T_BTN_PLAY_LV2_H{ "BtnPlayLv2H" };
const std::string T_BTN_RANKING{ "BtnRanking" };
const std::string T_BTN_RANKING_N{ "BtnRankingN" };
const std::string T_BTN_RANKING_H{ "BtnRankingH" };
const std::string T_BTN_SOUND{ "BtnSound" };
const std::string T_BTN_SOUND_N{ "BtnSoundN" };
const std::string T_BTN_SOUND_H{ "BtnSoundH" };
const std::string T_BTN_EXIT{ "BtnExit" };
const std::string T_BTN_EXIT_N{ "BtnExitN" };
const std::string T_BTN_EXIT_H{ "BtnExitH" };

// -- GAME TIME
//const std::string T_TXT_TIME{ "TextTime" };

// -- SCORE TEXT
//const std::string T_TXT_SC_NUM{ "TextScNum" };
//const std::string T_TXT_SC_PLAYERS{ "TextTxtSc" };
//const std::string R_SC_PLAYERS{ "RectScPl" };
//const std::string RF_SC_PLAYERS{ "RectTxtSc" };
//const std::string T_TXT_SC_PL1{ "TextScPl1" };
//const std::string T_TXT_SC_PL2{ "TextScPl2" };

// -- FONTS
const std::string F_SAIYAN{ "FontSaiyan" };
const std::string F_SAIYAN_TITLE{ "FontSaiyanTitle" };
const std::string F_GAMEOVER{ "FontGameOver" };

// -- AUDIO
//const std::string S_MAIN_THEME{"SoundMainTheme"};