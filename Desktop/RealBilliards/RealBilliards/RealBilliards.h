#pragma once

#include "resource.h"
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <vector>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Game.h"
#include "Table.h"

template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class DPIScale
{
	static float scaleX;
	static float scaleY;

public:
	static void Initialize(ID2D1Factory* pFactory)
	{
		FLOAT dpiX, dpiY;
		pFactory->GetDesktopDpi(&dpiX, &dpiY);
		scaleX = dpiX / 96.0f;
		scaleY = dpiY / 96.0f;
	}

	template <typename T>
	static D2D1_POINT_2F PixelsToDips(T x, T y)
	{
		return D2D1::Point2F(static_cast<float>(x) / scaleX, static_cast<float>(y) / scaleY);
	}
};

float DPIScale::scaleX = 1.0f;
float DPIScale::scaleY = 1.0f;

class RealBilliards
{
public:
	RealBilliards();
	~RealBilliards();

	// Register the window class and call methods for instantiating drawing resources
	HRESULT Initialize();

	// Process and dispatch messages
	void RunMessageLoop();

	void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
	void OnRButtonDown(int pixelX, int pixelY, DWORD flags);
	void OnLButtonUp();
	void OnMouseMove(int pixelX, int pixelY, DWORD flags);
	void OnMouseWheel(double delta);

	void RelocateBalls(int oldWid, int oldHeight, int newWid, int newHeight);

private:

	CGame mGame;

	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resource.
	void DiscardDeviceResources();

	// Draw content.
	HRESULT OnRender();

	// Load image
	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	ID2D1Bitmap* GetD2D1BMPFromFilename(const wchar_t* filename);

	void SetWoodBrush();

	void SetBallBrushes();


	// Resize the render target.
	void OnResize(
		UINT width,
		UINT height
	);


	// The windows procedure.
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* mFeltBrush;
	ID2D1SolidColorBrush* mPocketBrush;
	ID2D1SolidColorBrush* mCueBallBrush;
	ID2D1SolidColorBrush* mYellowBallBrush;
	ID2D1SolidColorBrush* mBlueBallBrush;
	ID2D1SolidColorBrush* mLRedBallBrush;
	ID2D1SolidColorBrush* mPurpleBallBrush;
	ID2D1SolidColorBrush* mOrangeBallBrush;
	ID2D1SolidColorBrush* mGreenBallBrush;
	ID2D1SolidColorBrush* mDRedBrush;
	ID2D1SolidColorBrush* mShaftBrush;
	ID2D1LinearGradientBrush* mPowerGradientBrush;

	ID2D1BitmapBrush* mWoodBrush;
	ID2D1BitmapBrush* mBackgroundBrush;

	ID2D1GeometrySink* mFeltSink;
	ID2D1PathGeometry* mFelt;
	ID2D1EllipseGeometry* baseGeo;
	ID2D1RectangleGeometry* stripeGeo;
	ID2D1PathGeometry* exclude;
	ID2D1GeometrySink* excludeSink;
	ID2D1EllipseGeometry* completeBallGeo;
	ID2D1Bitmap* mWoodImage;

	D2D1_BITMAP_BRUSH_PROPERTIES mBMPBrushProp;


	IDWriteFactory* mWriteFactory;
	IDWriteTextFormat* mBallTextFormat;
	IDWriteTextFormat* mSunkenBallTextFormat;
	IDWriteTextFormat* mLeftNameFormat;
	IDWriteTextFormat* mRightNameFormat;
	IDWriteTextFormat* mWinnerTextformat;

	D2D1_POINT_2F ptMouse;

	// Any item we are currently dragging
	std::shared_ptr<CGameItem> mGrabbedItem;

	HWND mWnd;

	// True until the first time we draw
	bool mFirstDraw = true;

	// Last time we read the timer
	long long mLastTime = 0;

	// Rate the timer updates
	double mTimeFreq = 0;

	std::pair<double, double> mP;

};