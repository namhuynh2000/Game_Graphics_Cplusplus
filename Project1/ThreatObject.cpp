#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	rect_.x = 0;
	rect_.y = 90;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;
	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject()
{
	;
}

void ThreatObject::HandleMove1(const int& x_border, const int& y_border)
{
	rect_.x += x_val_;
	if (rect_.x >SCREEN_WIDTH)
	{
		rect_.x = -WIDTH_THREAT;
	}
}
void ThreatObject::HandleMove2(const int& x_border, const int& y_border)
{
	rect_.x -= x_val_;
	if (rect_.x + WIDTH_THREAT < 0)
	{
		rect_.x = SCREEN_WIDTH;
	}
}

void ThreatObject::HandleInputAction(SDL_Event events)
{

}