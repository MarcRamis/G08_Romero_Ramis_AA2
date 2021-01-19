#pragma once

#include <string>
#include <map>
#include <unordered_map>

// ----- GAME GENERAL INFORMATION

// -- SCREEN SIZE--
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 704
const int MAP_ROWS{ 11 };
const int MAP_COLS{ 13 };
const int FPS{ 60 };
const float MOVEMENT_FRAME_TIME{ 300.f };
const int MAX_RANKING_PLAYERS{ 10 };

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
const std::string P_CONFIG{ "../../res/files/config.xml" };
const std::string P_RANKING{ "../../res/files/ranking.bin" };
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
const int SPRITE_PL_ROWS{ 4 };
const int SPRITE_PL_COLS{ 3 };
const int SPRITE_ITEMS_ROWS{ 2 };
const int SPRITE_ITEMS_COLS{ 3 };
const int SPRITE_EXPLOSION_ROWS{ 6 };
const int SPRITE_EXPLOSION_COLS{ 3 };
const int EXPLOSION_BLOCKS{ 9 };

// -- PLAY HUD --
const int SPRITE_HUD_HEIGHT{ 80 };
const std::string T_TXT_TIME{ "TextTime" };
const float MAX_GAMETIME{ 80.f };
const std::string T_PL1_SCORE_TEXT{ "Player1ScoreText" };
const std::string T_PL1_SCORE{ "Player1Score" };
const std::string T_PL2_SCORE_TEXT{ "Player2ScoreText" };
const std::string T_PL2_SCORE{ "Player2Score" };

const std::string T_PL1_LIVES{ "Player1Lives" };
const std::string T_PL2_LIVES{ "Player2Lives" };

const int KILL_PLAYER_SCORE{ 100 };
const int DESTROY_WALL_SCORE{ 15 };

// -- TEXTURE|RECT NAMES --
const std::string T_BG{ "Background" };
const std::string T_TITLE{ "TitleGame" };
const std::string T_BOARDNAME{ "BoardName" };
const std::string T_BOARDSCORE{ "BoardScore" };
const std::string T_PLAYER1{ "Player1" };
const std::string T_PLAYER2{ "Player2" };
const std::string T_ITEMS{ "Items" };
const std::string T_EXPLOSION{ "Explosion" };

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

// -- FONTS 
const std::string F_SAIYAN{ "FontSaiyan" };
const std::string F_SAIYAN_TITLE{ "FontSaiyanTitle" };
const std::string F_GAMEOVER{ "FontGameOver" };
const std::string F_GAMEOVER_RANKING_VAL{ "FontGameOverRankingValues" };

// -- AUDIO
const std::string S_MENU{ "SoundMenu" };
const std::string S_GAME_THEME{"SoundGameTheme"};