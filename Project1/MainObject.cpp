#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

MainObject::~MainObject()
{
	;
}

void MainObject::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			if(rect_.y >=STEP)
			{
				rect_.y -= STEP;
			}
			break;
		case SDLK_DOWN:
			if (rect_.y + HEIGHT_MAIN_OBJECT +STEP <= SCREEN_HEIGHT)
			{
				rect_.y += STEP;
			}
			break;
		
		case SDLK_RIGHT:
			if (rect_.x + WIDTH_MAIN_OBJECT + STEP <= SCREEN_WIDTH)
			{
				rect_.x += STEP;
			}
			break;
	
		case SDLK_LEFT:
			if (rect_.x >= STEP)
			{
				rect_.x -= STEP;
			}
			break;
		case SDLK_w:
			if (rect_.y >= STEP)
			{
				rect_.y -= STEP;
			}
			break;

		case SDLK_s:
			if (rect_.y + HEIGHT_MAIN_OBJECT + STEP <= SCREEN_HEIGHT)
			{
				rect_.y += STEP;
			}
			break;

		case SDLK_d:
			if (rect_.x + WIDTH_MAIN_OBJECT + STEP <= SCREEN_WIDTH)
			{
				rect_.x += STEP;
			}
			break;

		case SDLK_a:
			if (rect_.x >= STEP)
			{
				rect_.x -= STEP;
			}
			break;
		
		default:
			break;
		}
	}
	else if(events.type == SDL_KEYUP)
	{

	}
	else if (events.type == SDL_MOUSEMOTION)
	{

	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		
	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{

	}
	else
	{

	}
}

