#pragma once

#include <string>
#include <map>
#include <unordered_map>

// ----- GAME GENERAL INFORMATION

// -- SCREEN SIZE--
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 704
const int MAP_ROWS{ 13 };
const int MAP_COLS{ 14 };
const int FPS{ 60 };

// -- PATH GAME FILE--
// -- IMG
const std::string P_BG{ "../../res/img/bgGame.jpg" };
const std::string P_ITEMS{ "../../res/img/items.png" };
const std::string P_PLAYER1{ "../../res/img/player1.png" };
const std::string P_PLAYER2{ "../../res/img/player2.png" };
const std::string P_EXPLOSION{ "../../res/img/explosion.png" };
// -- AU
const std::string P_GAME_THEME{ "../../res/au/game_theme.mp3" };
const std::string P_MENU{ "../../res/au/menu.mp3" };
// -- FILES
// -- TTF
const std::string P_TTF_GAMEOVER{ "../../res/ttf/game_over.ttf" };
const std::string P_TTF_SAIYAN{ "../../res/ttf/saiyan.ttf" };

// -- MENU LINE SPACING--
const int TEXTSIZE_MENU{ 6 };
const int TEXT_LINESPACING_MENU{ 15 };
const int TEXT_HUD_HORIZONTAL_SPACING{ 30 };	
const int TEXT_HUD_VERTICAL_SPACING{ 10 };	

// -- SPRITES --
const int SPRITE_RES{ 48 };

// -- PLAY HUD --
const std::string T_TXT_TIME{ "TextTime" };
const float MAX_GAMETIME{ 75.f };
const std::string T_PL1_SCORE_TEXT{ "Player1ScoreText" };
const std::string T_PL1_SCORE{ "Player1Score" };
const std::string T_PL2_SCORE_TEXT{ "Player2ScoreText" };
const std::string T_PL2_SCORE{ "Player2Score" };

const std::string T_PL1_LIVES{ "Player1Lives" };
//const std::string T_PLAY_LEFT_SIDE_TIMER{ "PlayLeftTime" };
//const std::string T_PLAY_MIDDLE_SIDE_TIMER{ "PlayMidTime" };
//const std::string T_PLAY_RIGHT_SIDE_TIMER{ "PlayRightTime" };
const std::string T_PL2_LIVES{ "Player2Lives" };


// -- TEXTURE|RECT NAMES --
const std::string T_BG{ "Background" };
const std::string T_TITLE{ "TitleGame" };
const std::string T_PLAYER1{ "Player1" };
const std::string T_PLAYER2{ "Player2" };
const std::string T_ITEMS{ "Items" };

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
//const std::string F_PLAYERS_HUD{ "FontGameOverHUD" };
//const std::string F_TIMER_HUD{ "FontGameOverHUD" };

// -- AUDIO
const std::string S_MENU{ "SoundMenu" };
const std::string S_GAME_THEME{"SoundGameTheme"};