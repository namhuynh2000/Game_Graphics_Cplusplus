#pragma once
#include <windows.h>
#include <string>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <fstream>

#undef main
#define WIDTH_MAIN_OBJECT 70
#define HEIGHT_MAIN_OBJECT 70
#define WIDTH_THREAT 175
#define HEIGHT_THREAT 80

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL, *g_bkground2=NULL,*g_bkground3=NULL,*Menu = NULL;
static SDL_Event g_even,geven;



namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(string file_path); //hàm load ảnh
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y); //hàm vẽ ảnh đã load
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp(); // hàm xóa
	int CheckCollision(const SDL_Rect& human, const SDL_Rect& threat); // hàm kiểm tra
	int CheckCollision2(const SDL_Rect& human, const SDL_Rect& threat);
	void Continue_(int& heart, int &level);
	void save_(int& heart, int& level);
}