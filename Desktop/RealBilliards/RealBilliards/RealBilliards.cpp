// RealBilliards.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "RealBilliards.h"
#include <utility>
#include "WindowsX.h"
using namespace std;

#define MAX_LOADSTRING 100
#define PI 3.14159265

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_REALBILLIARDS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REALBILLIARDS));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REALBILLIARDS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_REALBILLIARDS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_MAX);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

RealBilliards::RealBilliards() :
	m_hwnd(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL),
	m_pLightSlateGrayBrush(NULL),
	mFeltBrush(NULL),
	mPocketBrush(NULL),
	mWoodBrush(NULL),
	mCueBallBrush(NULL),
	mYellowBallBrush(NULL),
	mBlueBallBrush(NULL),
	mLRedBallBrush(NULL),
	mPurpleBallBrush(NULL),
	mOrangeBallBrush(NULL),
	mGreenBallBrush(NULL),
	mDRedBrush(NULL),
	mShaftBrush(NULL),
	mPowerGradientBrush(NULL),
	mBackgroundBrush(NULL)


{
}


RealBilliards::~RealBilliards()
{
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&mFeltBrush);
	SafeRelease(&mPocketBrush);
	SafeRelease(&mWoodBrush);
	SafeRelease(&mCueBallBrush);
	SafeRelease(&mYellowBallBrush);
	SafeRelease(&mBlueBallBrush);
	SafeRelease(&mLRedBallBrush);
	SafeRelease(&mPurpleBallBrush);
	SafeRelease(&mOrangeBallBrush);
	SafeRelease(&mGreenBallBrush);
	SafeRelease(&mDRedBrush);
	SafeRelease(&mShaftBrush);
	SafeRelease(&mPowerGradientBrush);
	SafeRelease(&mBackgroundBrush);
	if (mWoodImage) mWoodImage->Release();

}

void RealBilliards::RunMessageLoop()
{
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		//TranslateMessage(&msg);
		//DispatchMessage(&msg);

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
		}
		else
		{
			if (mFirstDraw)
			{
				mFirstDraw = false;


				/*
				 * Initialize the elapsed time system
				 */
				LARGE_INTEGER time, freq;
				QueryPerformanceCounter(&time);
				QueryPerformanceFrequency(&freq);

				mLastTime = time.QuadPart;
				mTimeFreq = double(freq.QuadPart);
			}

			/*
			 * Compute the elapsed time since the last draw
			 */
			LARGE_INTEGER time;
			QueryPerformanceCounter(&time);
			long long diff = time.QuadPart - mLastTime;
			double elapsed = double(diff) / mTimeFreq;
			mLastTime = time.QuadPart;

			mGame.Update(elapsed);
			m_pRenderTarget->BeginDraw();
			m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
			m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
			mGame.OnDraw(m_pRenderTarget);


			m_pRenderTarget->EndDraw();

		}

	}
}


HRESULT RealBilliards::Initialize()
{
	HRESULT hr;

	// Initialize device-indpendent resources, such
	// as the Direct2D factory.
	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = RealBilliards::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"D2DDemoApp";

		RegisterClassEx(&wcex);


		// Because the CreateWindow function takes its size in pixels,
		// obtain the system DPI and use it to scale the window size.
		FLOAT dpiX, dpiY;

		// The factory returns the current system DPI. This is also the value it will use
		// to create its own windows.
		m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);


		// Create the window.
		m_hwnd = CreateWindow(
			L"D2DDemoApp",
			L"Real Biliards",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<UINT>(ceil(1280.f * dpiX / 96.f)),
			static_cast<UINT>(ceil(657.f * dpiY / 96.f)),
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
		);
		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
	}

	return hr;
}

int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
)
{
	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			RealBilliards app;

			if (SUCCEEDED(app.Initialize()))
			{
				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}

HRESULT RealBilliards::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 7;
	static const FLOAT name_font_size = 30;
	static const FLOAT sunken_ball_font_size = 20;
	static const FLOAT winner_font_size = 80;


	if (SUCCEEDED(hr))
	{

		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(mWriteFactory),
			reinterpret_cast<IUnknown * *>(&mWriteFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = mWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&mBallTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = mWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			sunken_ball_font_size,
			L"", //locale
			&mSunkenBallTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = mWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			name_font_size,
			L"", //locale
			&mLeftNameFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = mWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			name_font_size,
			L"", //locale
			&mRightNameFormat
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = mWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			winner_font_size,
			L"", //locale
			&mWinnerTextformat
		);
	}

	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		mBallTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		mBallTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		mSunkenBallTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		mSunkenBallTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		mLeftNameFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		mRightNameFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);

		mWinnerTextformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		mWinnerTextformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	mGame.SetBallTextFormat(mBallTextFormat);
	mGame.SetLeftTextFormat(mLeftNameFormat);
	mGame.SetRightTextFormat(mRightNameFormat);
	mGame.SetSunkenBallTextFormat(mSunkenBallTextFormat);
	mGame.SetWinnerTextFormat(mWinnerTextformat);



	return hr;
}

HRESULT RealBilliards::CreateDeviceResources()
{
	HRESULT hr = S_OK;
	mBMPBrushProp.extendModeX = D2D1_EXTEND_MODE_WRAP;
	mBMPBrushProp.extendModeY = D2D1_EXTEND_MODE_WRAP;
	mBMPBrushProp.interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
		);


		if (SUCCEEDED(hr))
		{
			// Create a gray brush.
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
				&m_pLightSlateGrayBrush
			);
		}
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(0x318039, 1.0f),
				&mFeltBrush
			);
			mGame.GetTable()->SetFeltBrush(mFeltBrush);
		}
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&mPocketBrush
			);
			mGame.GetTable()->SetPocketBrush(mPocketBrush);
		}
		if (SUCCEEDED(hr))
		{
			SetWoodBrush();
		}
		if (SUCCEEDED(hr))
		{
			SetBallBrushes();
		}
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(0xECE29A, 1.0f),
				&mShaftBrush
			);
			mGame.SetShaftBrush(mShaftBrush);
			mGame.SetHandleBrush(m_pLightSlateGrayBrush);
		}

		// Create an array of gradient stops to put in the gradient stop
		// collection that will be used in the gradient brush.
		ID2D1GradientStopCollection* pGradientStops = NULL;

		D2D1_GRADIENT_STOP gradientStops[2];
		gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Green, 1);
		gradientStops[0].position = 0.0f;
		gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Red, 1);
		gradientStops[1].position = 1.0f;
		// Create the ID2D1GradientStopCollection from a previously
		// declared array of D2D1_GRADIENT_STOP structs.
		hr = m_pRenderTarget->CreateGradientStopCollection(
			gradientStops,
			2,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			&pGradientStops
		);

		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(0, 0),
					D2D1::Point2F(150, 150)),
				pGradientStops,
				&mPowerGradientBrush
			);
			mGame.GetPowerBar()->SetPowerBrush(mPowerGradientBrush);
			mGame.GetPowerBar()->SetWoodBrush(mWoodBrush);
			mGame.GetPowerBar()->SetBackgroundBrush(mPocketBrush);
		}
		if (SUCCEEDED(hr))
		{
			const wchar_t* backgroundFile = L"C:/Users/Admin/Desktop/RealBilliards/images/hardwoodfloors.jpg";
			ID2D1Bitmap* bmp = GetD2D1BMPFromFilename(backgroundFile);

			hr = m_pRenderTarget->CreateBitmapBrush(
				bmp,
				&mBMPBrushProp,
				NULL,
				&mBackgroundBrush
			);
			mGame.SetBackgroundBrush(mBackgroundBrush);
		}
		
	}

	return hr;
}

void RealBilliards::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&mFeltBrush);
	SafeRelease(&mPocketBrush);
	SafeRelease(&mWoodBrush);
	SafeRelease(&mCueBallBrush);
	SafeRelease(&mYellowBallBrush);
	SafeRelease(&mBlueBallBrush);
	SafeRelease(&mLRedBallBrush);
	SafeRelease(&mPurpleBallBrush);
	SafeRelease(&mOrangeBallBrush);
	SafeRelease(&mGreenBallBrush);
	SafeRelease(&mDRedBrush);
	SafeRelease(&mShaftBrush);
	SafeRelease(&mPowerGradientBrush);
}

LRESULT CALLBACK RealBilliards::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		RealBilliards* pDemoApp = (RealBilliards*)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(pDemoApp)
		);
		pDemoApp->mWnd = hwnd;
		result = 1;
	}
	else
	{
		RealBilliards* pDemoApp = reinterpret_cast<RealBilliards*>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
			)));

		bool wasHandled = false;

		if (pDemoApp)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pDemoApp->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_PAINT:
			{
				pDemoApp->OnRender();
				ValidateRect(hwnd, NULL);
			}
			result = 0;

			wasHandled = true;
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}

			result = 1;
			wasHandled = true;
			break;
			case WM_MOUSEMOVE:
			{
				pDemoApp->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
				return 0;
			}

			result = 1;
			wasHandled = true;
			break;
			case WM_LBUTTONDOWN:
			{
				pDemoApp->OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
				return 1;
			}
			result = 1;
			wasHandled = true;
			break;
			case WM_LBUTTONUP:
			{
				pDemoApp->OnLButtonUp();
				return 1;
			}
			result = 1;
			wasHandled = true;
			break;
			case WM_RBUTTONDOWN:
			{
				pDemoApp->OnRButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
				return 1;
			}
			result = 1;
			wasHandled = true;
			break;
			case WM_MOUSEWHEEL:
			{
				pDemoApp->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
				return 1;
			}
			result = 1;
			wasHandled = true;
			break;
			}

		}


		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}

HRESULT RealBilliards::OnRender()
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();


	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
		mGame.SetFactory(m_pDirect2dFactory);
		mGame.SetRenderTarget(m_pRenderTarget);

		mGame.OnDraw(m_pRenderTarget);
		m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(mP.first, mP.second), 10, 10), mBlueBallBrush);

		hr = m_pRenderTarget->EndDraw();

		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}

	}


	return hr;
}

void RealBilliards::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		int oldWid = m_pRenderTarget->GetSize().width;
		int oldLength = m_pRenderTarget->GetSize().height;
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
		mGame.GetTable()->ConfigureTable();
		mGame.GetPowerBar()->SetLocation();
		mGame.GetScoreboard()->SetTextboxLocations();
		RelocateBalls(oldWid, oldLength, width, height);
		mGame.GetCue()->TransformPoints(0);
	}
}

HRESULT RealBilliards::LoadResourceBitmap(
	ID2D1RenderTarget* pRenderTarget,
	IWICImagingFactory* pIWICFactory,
	PCWSTR resourceName,
	PCWSTR resourceType,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap** ppBitmap
)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);
	HRESULT hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;

	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);

	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

ID2D1Bitmap* RealBilliards::GetD2D1BMPFromFilename(const wchar_t* filename)
{

	HRESULT hr = S_OK;
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)& wicFactory);

	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	ID2D1Bitmap* bmp;
	m_pRenderTarget->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp
	);
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
	return bmp;
/**
	m_pRenderTarget->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height));*/
}

/**
* Set the brush for the wood panneling on the table and power bar
*/
void RealBilliards::SetWoodBrush()
{
	HRESULT hr = S_OK;
	IWICImagingFactory* wicFactory = NULL;
	const wchar_t* woodFile = L"C:/Users/Admin/Desktop/RealBilliards/images/polishedwood.jpg";
	ID2D1Bitmap* bmp = GetD2D1BMPFromFilename(woodFile);

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)& wicFactory);
	
	hr = m_pRenderTarget->CreateBitmapBrush(
		bmp,
		&mBMPBrushProp,
		NULL,
		&mWoodBrush
	);
	mGame.GetTable()->SetWoodBrush(mWoodBrush);
	mGame.GetPowerBar()->SetWoodBrush(mWoodBrush);
}

void RealBilliards::SetBallBrushes()
{
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&mCueBallBrush
	);
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0xFDE903, 1.0f)),
		&mYellowBallBrush
	);
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0x0349FD, 1.0f)),
		&mBlueBallBrush
	);
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0xFD1003, 1.0f)),
		&mLRedBallBrush
	);
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0xAD03FD, 1.0f)),
		&mPurpleBallBrush
	);
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0xFD6703, 1.0f)),
		&mOrangeBallBrush
	);
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0x27653F, 1.0f)),
		&mGreenBallBrush
	);
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0x621111, 1.0f)),
		&mDRedBrush
	);


	vector<ID2D1SolidColorBrush*> ballBrushes =
	{ mCueBallBrush, mYellowBallBrush, mBlueBallBrush, mLRedBallBrush,
	mPurpleBallBrush, mOrangeBallBrush, mGreenBallBrush, mDRedBrush, mPocketBrush };
	mGame.SetBallBrushes(ballBrushes);
}

void RealBilliards::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
	const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);
	const float x1 = dips.x;
	const float y1 = dips.y;
	mP = pair<double, double>(x1, y1);
	this->mGame.GetCue()->SetPoint(D2D1::Point2F(x1, y1));

	if (this->mGame.GetAssistant() != nullptr)
	{
		this->mGame.GetAssistant()->SetPoint(D2D1::Point2F(x1, y1));
	}
	
	if (flags & MK_LBUTTON)
	{
		if (mGame.GetPowerBar()->GetAdjusting())
		{
			mGame.GetPowerBar()->SetPower(x1);
		}
	}
	
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{


		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (flags & MK_LBUTTON)
		{
			if (this->mGrabbedItem->GetId() == L"CUE")
			{
				this->mGame.GetCue()->SetDragged(true);
				this->mGame.GetCue()->SetPoint(D2D1::Point2F(x1, y1));
				mGame.GetCue()->Update(1);
			}

			else if (this->mGrabbedItem->GetId() == L"0" && this->mGame.IsBallInHand() || this->mGame.GetDevMode())
			{

				mGrabbedItem->SetX(x1);
				mGrabbedItem->SetY(y1);
			}

		}
		else
		{
			this->mGame.GetCue()->SetDragged(false);
			this->mGrabbedItem = nullptr;
		}
		InvalidateRect(m_hwnd, NULL, FALSE);
	}

		
}


void RealBilliards::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{

	const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);

	const float width = (dips.x - ptMouse.x) / 2;
	const float height = (dips.y - ptMouse.y) / 2;
	const float x1 = dips.x;
	const float y1 = dips.y;
	
	this->mGrabbedItem = mGame.HitTest(x1, y1);
	InvalidateRect(m_hwnd, NULL, TRUE);
}

void RealBilliards::OnRButtonDown(int pixelX, int pixelY, DWORD flags)
{
	if (mGame.GetPowerBar()->GetPower() > 0)
	{
		mGame.GetCue()->SetShooting();
	}
}

void RealBilliards::OnLButtonUp()
{
	mGame.GetPowerBar()->SetAdjusting(false);
}
void RealBilliards::OnMouseWheel(double delta)
{
	shared_ptr<CPowerBar> powerBar = mGame.GetPowerBar();
	if (delta > 0)
	{
		powerBar->ChangePower(powerBar->GetMaxPower() / 25);
	}
	else
	{
		powerBar->ChangePower(-powerBar->GetMaxPower() / 25);
	}
}

/**
* Relocate and resize the balls on the table based on the new window size
* \param width: The new width of the window
* \param length: The new length of the window
*/
void RealBilliards::RelocateBalls(int oldWid, int oldHeight, int newWid, int newHeight)
{
	for (shared_ptr<CBall> &ball : mGame.GetBalls())
	{
		double xRatio = ball->GetCenter().first / oldWid;
		double yRatio = ball->GetCenter().second / oldHeight;
		double sizeRatio = ball->GetDiameter() / oldWid;
		ball->SetCenter(xRatio * newWid, yRatio * newHeight);
		ball->SetDiameter(sizeRatio * newWid);
		ball->SetRadius(ball->GetDiameter() / 2);
		ball->ConfigureStripe();
	}
}