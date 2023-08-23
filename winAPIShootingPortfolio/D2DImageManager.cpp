#include "Stdafx.h"
#include "D2DImageManager.h"
#include "Animation.h"

HRESULT D2DImageManager::init(HDC hdc)
{
    D2DInit(_hWnd, 0, 0, &_factory, &_rendTrg);
    WICInit(&_imagingFactory);

    HRESULT hr;
    RECT rc;
    GetClientRect(_hWnd, &rc);
    hr = _rendTrg->BindDC(hdc, &rc);

    SetLayout(hdc, LAYOUT_BITMAPORIENTATIONPRESERVED);

    return S_OK;
}

void D2DImageManager::release(void)
{

}

void D2DImageManager::beginDraw(void)
{
    _rendTrg->BeginDraw();
}

void D2DImageManager::endDraw(void)
{
    _rendTrg->EndDraw();
}

HRESULT D2DImageManager::loadImageD2D(string key, LPCWSTR lstr, int Width, int Height, int maxFrameX, int maxFrameY)
{
    D2DLoadBitmap(lstr, _rendTrg, _imagingFactory, &_pBitmap);
    _img = new D2DImageInfo;
    _img->bitmap = _pBitmap;
    _img->frameWidth = Width / maxFrameX;
    _img->frameHeight = Height / maxFrameY;
    _img->maxFrameX = maxFrameX - 1;
    _img->maxFrameY = maxFrameY - 1;

    _mImage.insert({ key, _img });

    return S_OK;
}

void D2DImageManager::render(string key, int destX, int destY, int currentFrameX, int currentFrameY)
{
   
    RECT rc;

    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + _mImage[key]->frameWidth , destY + _mImage[key]->frameHeight );
    D2D1_RECT_F rect2 = D2D1::RectF(_mImage[key]->frameWidth * currentFrameX, _mImage[key]->frameHeight * currentFrameY,
        _mImage[key]->frameWidth * currentFrameX + _mImage[key]->frameWidth,
        _mImage[key]->frameHeight * currentFrameY + _mImage[key]->frameHeight);
    //_rendTrg->DrawBitmap(_mImage[key]-> rect);
    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
    if (_mImage[key]->bitmap) {}
  
}

void D2DImageManager::render(string key, int x, int y, float ac1)
{
}

void D2DImageManager::render(string key, int x, int y, float ac1, float opacity)
{
}

HRESULT D2DImageManager::D2DInit(HWND hwnd, int width, int height, ID2D1Factory** factory, ID2D1DCRenderTarget** rt)
{
    HRESULT hr;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factory);

    if (SUCCEEDED(hr)) {
        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(
                DXGI_FORMAT_B8G8R8A8_UNORM,
                D2D1_ALPHA_MODE_IGNORE),
            0,
            0,
            D2D1_RENDER_TARGET_USAGE_NONE,
            D2D1_FEATURE_LEVEL_DEFAULT
        );

        RECT rc;
        GetClientRect(hwnd, &rc);
        hr = (*factory)->CreateDCRenderTarget(&props, rt);
    }
    return hr;
}

HRESULT D2DImageManager::WICInit(IWICImagingFactory** factory)
{
    CoInitialize(0);

    return CoCreateInstance(CLSID_WICImagingFactory,
        0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(factory));
}

HRESULT D2DImageManager::D2DLoadBitmap(LPCWSTR fileName, ID2D1DCRenderTarget* target,
    IWICImagingFactory* factory, ID2D1Bitmap** bitmap)
{
    HRESULT hr;

    // IWICBitmapDecoder 초기화
    IWICBitmapDecoder* decoder = 0;
    hr = factory->CreateDecoderFromFilename(fileName,
        0,
        GENERIC_READ,
        WICDecodeMetadataCacheOnDemand,
        &decoder
    );

    if (FAILED(hr))
        return hr;

    // IWICBitmapFrameDecode 초기화
    IWICBitmapFrameDecode* frameDecode = 0;

    hr = decoder->GetFrame(0, &frameDecode);
    if (FAILED(hr))
    {
        decoder->Release();
        return hr;
    }

    // IWICFormatConverter 초기화
    IWICFormatConverter* converter = 0;
    hr = factory->CreateFormatConverter(&converter);
    if (FAILED(hr))
    {
        decoder->Release();
        return hr;
    }

    hr = converter->Initialize(
        frameDecode,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        NULL, 0.0f, WICBitmapPaletteTypeCustom
    );

    if (FAILED(hr))
    {
        decoder->Release();
        frameDecode->Release();
        converter->Release();

        return hr;
    }

    // WIC 비트맵으로부터 D2D 비트맵 생성
    hr = target->CreateBitmapFromWicBitmap(converter, 0, bitmap);

    // 자원 해제
    decoder->Release();
    frameDecode->Release();
    converter->Release();

    _pBitmap = *bitmap;
    return hr;

}

D2DImageManager::D2DImageManager() : _factory(NULL),
_rendTrg(NULL),
_pBitmap(NULL),
_imagingFactory(NULL)
{
}
