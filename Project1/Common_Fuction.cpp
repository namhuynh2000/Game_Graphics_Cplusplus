#include "Common_Fuction.h"

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path) 
{
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0, 0);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}

	}
	return optimize_image;
}

void SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
}
void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);
}

void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}

int SDLCommonFunc::CheckCollision(const SDL_Rect& human, const SDL_Rect& threat)
{
	SDL_Rect center;
	center.x=human.x + human.w / 2;
	center.y = human.y + human.h / 2 + 13;
	int left_a = threat.x;
	int right_a = threat.x + threat.w;
	int top_a = threat.y;
	int bottom_a = threat.y + threat.h;

	if (left_a <= center.x && center.x <= right_a && top_a <= center.y && center.y <= bottom_a)
	{
		return 0; // va chạm
	}
	else if (center.y >= SCREEN_HEIGHT-human.w/2-20)
	{
		return 1; // chiến thắng
	}
}

int SDLCommonFunc::CheckCollision2(const SDL_Rect& human, const SDL_Rect& threat)
{
	SDL_Rect center;
	center.x = human.x + human.w / 2;
	center.y = human.y + human.h / 2+13;
	int left_a = threat.x;
	int right_a = threat.x + threat.w;
	int top_a = threat.y;
	int bottom_a = threat.y + threat.h;

	 if (center.y >= SCREEN_HEIGHT - human.w / 2 - 20)
	{
		return 1; // chiến thắng
	}
	else if (left_a <= center.x && center.x <= right_a && top_a <= center.y && center.y <= bottom_a)
	 {
		 return 0; // va chạm
	 }
	else if (170 <= center.y && center.y <= 250)
	 {
		 if (551 <= center.x || center.x <= 489)
			 return 0;
		 else return 2;
	 }
	else if (330 <= center.y && center.y <= 410)
	 {
		 if (271 <= center.x || center.x <= 209)
			 return 0;
		 else return 2;
	 }
	else return 2;
}

void SDLCommonFunc::Continue_(int& heart, int &level)
{
	fstream f;
	f.open("continue.txt", ios::in);
	f >> heart;
	f >> level;
	f.close();
}

void SDLCommonFunc::save_(int& heart, int& level)
{
	fstream f;
	f.open("continue.txt", ios::trunc|ios::out);
	f << heart;
	f << " ";
	f << level;
	f.close();
	heart = 3;
	level = 1;
}