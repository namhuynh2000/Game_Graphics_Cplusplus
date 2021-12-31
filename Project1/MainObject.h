#pragma once
#include "Common_Fuction.h"
#include "BaseObject.h"

#define WIDTH_MAIN_OBJECT 70
#define HEIGHT_MAIN_OBJECT 70
#define STEP 40
class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event events);
private:
	int x_val_;
	int y_val_;
};