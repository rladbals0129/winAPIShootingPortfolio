#pragma once
#include "SingletonBase.h"
#include <d2d1.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
class Animation;

struct D2DImageInfo
{
	ID2D1Bitmap* bitmap;
	int frameWidth;
	int frameHeight;
	int maxFrameX;
	int maxFrameY;
};
class D2DImageManager :public SingletonBase<D2DImageManager>
{
private:
	ID2D1Factory* _factory;
	ID2D1DCRenderTarget* _rendTrg;
	ID2D1Bitmap* _pBitmap;
	IWICImagingFactory* _imagingFactory;

	D2DImageInfo* _img;

	map<string, D2DImageInfo*> _mImage;
	map<string, D2DImageInfo*>::iterator _miImage;

	UINT _width, _height, _frame, _maxFrame;
	int destX, destY;
	int currentFrameX, currentFrameY;

public:
	HRESULT init(HDC hdc);
	void release(void);

	void beginDraw(void);
	void endDraw(void);

	HRESULT loadImageD2D(string key, LPCWSTR lstr, int Width, int Height, int maxFrameX, int maxFrameY);

	void render(string key, int x, int y, int currentFrameX, int currentFrameY);
	void render(string key, int x, int y, float ac1);
	void render(string key, int x, int y, float ac1, float opacity);

	HRESULT D2DInit(HWND hwnd, int width, int height,
		ID2D1Factory** factory, ID2D1DCRenderTarget** rt);
	HRESULT WICInit(IWICImagingFactory** factory);
	HRESULT D2DLoadBitmap(LPCWSTR fileName, ID2D1DCRenderTarget* target,
		IWICImagingFactory* factory, ID2D1Bitmap** bitmap);


	inline int getFrameWidth(void) { return _img->frameWidth; }

	inline int getFrameHeight(void) { return _img->frameHeight; }


	inline int getMaxFrameX(void) { return _img->maxFrameX; }

	inline int getMaxFrameY(void) { return _img->maxFrameY; }



	D2DImageManager();
	~D2DImageManager() {}
};
