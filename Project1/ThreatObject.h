#pragma once
#include "Common_Fuction.h"
#include "BaseObject.h"
#include <time.h>
#define WIDTH_THREAT 175
#define HEIGHT_THREAT 80

class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	void HandleMove1(const int& x_border, const int& y_border); //hàm di chuyển threat từ trái sang phải
	void HandleMove2(const int& x_border, const int& y_border); //hàm di chuyển threat từ phải sang trái
	void HandleInputAction(SDL_Event events); //hàm kiểm tra sự kiện

	void set_x_val(const int& val) { x_val_ = val;}
	void set_y_val(const int& val) { y_val_ = val; }
	int get_x_val() const { return x_val_; }
	int ger_y_val() const { return y_val_; }
private:
	int x_val_;
	int y_val_;
};