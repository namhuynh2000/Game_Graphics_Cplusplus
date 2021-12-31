#pragma once
#include <cstdio>
#include <windows.h>

namespace fcr
{
	enum ConsoleColor {
		Black,
		DarkBlue,
		DarkGreen,
		DarkCyan,
		DarkRed,
		DarkMagenta,
		DarkYellow,
		Gray,
		DarkGray,
		Blue,
		Green,
		Cyan,
		Red,
		Magenta,
		Yellow,
		White
	};

	struct Window {
		HANDLE hStdOut;
		CHAR_INFO* outBuf;
		COORD wdSize, bufCoord;
		SMALL_RECT srctWriteRect;
		WORD color;
		int iw, outBufSize;

		~Window();
	};

	void init();
	void settitle(const wchar_t* title);
	void setsize(int w, int h);
	void setfont(const wchar_t* fontName, int fontSizeX, int fontSizeY);

	void gotoxy(int x, int y);
	void clrscr();
	int textcolor();
	int backcolor();
	void setcolor(int textcolor, int backcolor);
	void settextcolor(int textcolor);
	void setbackcolor(int backcolor);
	void cursor(bool visible);

	void putchar(char c);
	void printf(const char* format, ...);
	void putwchar(wchar_t wc);
	void wprintf(const wchar_t* format, ...);

	void writebuffer();
} // namespace fcr