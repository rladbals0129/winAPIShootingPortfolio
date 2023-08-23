#pragma once
//#include <gdiPlus.h>
//#pragma comment(lib, "gdiplus.lib")
//using namespace Gdiplus;


/*
struct FrameImageInfo
{
    Image* image;   //이미지 객체에 대한 포인터
    int x;
    int y;
    int frameWidth; // 한프레임 너비
    int frameHeight;//한프레임 높이
    int maxFrameX; //가로방향 최대프레임 개수
    int maxFrameY; //세로방향 최대프레임 개수
    int clipX;
    int clipY;
    int clipWidth;
    int clipHeight;
};

class PNGRender
{
private:
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Image* image;
    FrameImageInfo* frameImageInfo;
    REAL _angle;

    HDC memDC;
    HBITMAP hbmMem;
    HBITMAP hbmOld;
    BLENDFUNCTION blendFunc;

    HBRUSH hBrush;







public:
    PNGRender() { hBrush = CreateSolidBrush(RGB(0, 0, 0)); }
    ~PNGRender() { DeleteObject(hBrush); }
    HRESULT init(void);
    void release(void);


    void addImage(wchar_t* filePath);
    // void LoadImage(wchar_t* filePath, int Width, int Height, int maxFrameX, int maxFrameY);
    // void LoadImage(wchar_t* filePath, int clipX = 0, int clipY = 0, int clipWidth = 0, int clipHeight = 0);
    void addImage(wchar_t* filePath, int Width, int Height, int maxFrameX, int maxFrameY, int clipX = 0, int clipY = 0, int clipWidth = 0, int clipHeight = 0);
    void CreateMemDC(HDC hdc, int width, int height);
    void ReleaseMemDC();
    void RotateRender(HDC hdc, int x, int y, int width, int height, bool render);
    void rotateImage(REAL delta_angle, bool isColliding);


    void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
    void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);




    inline Image* getImage(void) { return image; }

    inline int getFrameWidth(void) { return frameImageInfo->frameWidth; }

    inline int getFrameHeight(void) { return frameImageInfo->frameHeight; }


    inline int getMaxFrameX(void) { return frameImageInfo->maxFrameX; }

    inline int getMaxFrameY(void) { return frameImageInfo->maxFrameY; }

    inline void deleteImage(Image** _image) {
        if (*_image == nullptr) return;
        delete* _image;
        *_image = nullptr;
    }

    


};


*/