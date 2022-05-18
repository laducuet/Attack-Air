#pragma once
#ifndef COMMON_FUMCTION_H_
#define COMMON_FUMCTION_H_

#include <Windows.h>
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


const int WIDTH_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 3;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_even;
static SDL_Surface* g_img_menu = NULL;
static SDL_Surface* g_img_gameover = NULL;
static SDL_Surface* g_img_gameover1 = NULL;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void CleanUp();
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckFocusWithRect(const int& x,const int& y,const SDL_Rect& rect);
	int ShowGameOver(SDL_Surface* des, TTF_Font* font,std::string mark_);

	
}

#endif // !COMMON_FUMCTION_H_
