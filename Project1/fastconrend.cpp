#include "fastconrend.h"
#include <algorithm>

namespace fcr
{
	////////////////////////////////
	/// GLOBAL VARIABLE `window` ///
	////////////////////////////////
	Window window;

	Window::~Window()
	{
		cursor(true);
		setcolor(Gray, Black);
		free(window.outBuf);
	}

	void makeNewBuffer(int w, int h)
	{
		free(window.outBuf);

		window.outBufSize = w * h;
		window.outBuf = (CHAR_INFO*)calloc(window.outBufSize, sizeof(CHAR_INFO));
		if (!window.outBuf)
		{
			perror("Error allocating output buffer\n");
			exit(1);
		}
		for (int i = 0; i < window.outBufSize; ++i)
			window.outBuf[i].Attributes = window.color;
	}

	void init()
	{
		window.hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (window.hStdOut == INVALID_HANDLE_VALUE)
		{
			perror("Error getting stdout handle\n");
			exit(1);
		}
		window.bufCoord.X = window.bufCoord.Y = 0;
		window.srctWriteRect.Top = 0;
		window.srctWriteRect.Left = 0;
		window.iw = 0;

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(window.hStdOut, &csbi))
		{
			perror("Error `GetConsoleScreenBufferInfo`\n");
			exit(1);
		}

		window.outBuf = NULL;
		makeNewBuffer(csbi.dwSize.X, csbi.dwSize.Y);
		window.wdSize = csbi.dwSize;
		window.srctWriteRect.Bottom = window.wdSize.Y - 1;
		window.srctWriteRect.Right = window.wdSize.X - 1;
		SetConsoleWindowInfo(window.hStdOut, true, &window.srctWriteRect);
		window.color = csbi.wAttributes;
	}

	void settitle(const WCHAR* title)
	{
		SetConsoleTitleW(title);
	}

	void setsize(int w, int h)
	{
		char changeWindowSizeMsg[64];
		sprintf_s(changeWindowSizeMsg, "mode con: cols=%d lines=%d", w, h);
		system(changeWindowSizeMsg); //// system call /////

		makeNewBuffer(w, h);
		window.wdSize.X = w;
		window.wdSize.Y = h;
		window.srctWriteRect.Bottom = window.wdSize.Y - 1;
		window.srctWriteRect.Right = window.wdSize.X - 1;
		SetConsoleWindowInfo(window.hStdOut, true, &window.srctWriteRect);
	}

	void gotoxy(int x, int y)
	{
		window.iw = x + y * window.wdSize.X;
		window.iw %= window.outBufSize; // prevent overflow
	}

	void clrscr()
	{
		for (int i = 0; i < window.outBufSize; ++i)
		{
			window.outBuf[i].Attributes = window.color;
			window.outBuf[i].Char.AsciiChar = ' ';
		}
		gotoxy(0, 0);
	}

	int textcolor()
	{
		return window.color & 0xF;
	}

	int backcolor()
	{
		return (window.color >> 4) & 0xF;
	}

	void setcolor(int textColor, int backColor)
	{
		window.color = (backColor << 4) + textColor;
	}

	void settextcolor(int textColor)
	{
		setcolor(textColor, backcolor());
	}

	void setbackcolor(int backColor)
	{
		setcolor(textcolor(), backColor);
	}

	void cursor(bool visible)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(window.hStdOut, &cursorInfo);
		cursorInfo.bVisible = visible; // set the cursor visibility
		SetConsoleCursorInfo(window.hStdOut, &cursorInfo);
	}

	void putchar(char c)
	{
		window.outBuf[window.iw].Char.AsciiChar = c;
		window.outBuf[window.iw].Attributes = window.color;
		++window.iw;
	}

	void printf(const char* fmt, ...)
	{
		static char buff[1024];
		va_list args;
		va_start(args, fmt);
		vsprintf_s(buff, fmt, args);
		va_end(args);

		// Write buff to outBuf
		int wdX = window.wdSize.X;
		for (char* ptr = buff; *ptr; ++ptr)
		{
			if (*ptr == '\b')
				--window.iw;
			else if (*ptr == '\r')
				window.iw = window.iw / wdX * wdX;
			else if (*ptr == '\n')
				window.iw = (window.iw / wdX + 1) * wdX;
			else
				putchar(*ptr);
			window.iw %= window.outBufSize; // prevent overflow
		}
	}

	void putwchar(wchar_t wc)
	{
		window.outBuf[window.iw].Char.UnicodeChar = wc;
		window.outBuf[window.iw].Attributes = window.color;
		++window.iw;
	}

	void wprintf(const wchar_t* fmt, ...)
	{
		static wchar_t buff[1024];
		va_list args;
		va_start(args, fmt);
		vswprintf_s(buff, 1024, fmt, args);
		va_end(args);

		// Write buff to outBuf
		int wdX = window.wdSize.X;
		for (wchar_t* ptr = buff; *ptr; ++ptr)
		{
			if (*ptr == L'\b')
				--window.iw;
			else if (*ptr == L'\r')
				window.iw = window.iw / wdX * wdX;
			else if (*ptr == L'\n')
				window.iw = (window.iw / wdX + 1) * wdX;
			else
				putwchar(*ptr);
			window.iw %= window.outBufSize; // prevent overflow
		}
	}

	void writebuffer()
	{
		WriteConsoleOutputW(window.hStdOut,  // screen buffer to write to
			window.outBuf,   // buffer to copy from
			window.wdSize,   // col-row size of chiBuffer
			window.bufCoord, // top left src cell in chiBuffer
			&window.srctWriteRect);
	}

	void setfont(const wchar_t* fontName, int fontSizeX, int fontSizeY)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof cfi;
		cfi.nFont = 0;
		cfi.dwFontSize.X = fontSizeX;
		cfi.dwFontSize.Y = fontSizeY;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, fontName);
		if (!SetCurrentConsoleFontEx(window.hStdOut, false, &cfi))
		{
			perror("Cannot set font\n");
			exit(1);
		}
	}

} // namespace fcr