#include "stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontweight, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT font = CreateFont
	(
		fontSize,
		0,
		0,
		0,
		fontweight,
		0,
		0,
		0,
		HANGEUL_CHARSET,
		0,
		0,
		0,
		0,
		TEXT(fontName)
	);

	
	auto oldFont = (HFONT)SelectObject(hdc, font);;

	SetTextColor(hdc, color);

	const int stringLength = strlen(printString);
	wchar_t charBuffer[256];
	

	TextOut(hdc, destX, destY, printString, stringLength);



	SelectObject(hdc, oldFont);
	DeleteObject(font);
}
