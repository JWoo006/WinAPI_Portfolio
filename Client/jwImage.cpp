#include "jwImage.h"
#include "jwApplication.h"
#include "jwResources.h"

extern jw::Application application;

namespace jw
{
	Image* Image::Create(const std::wstring& name, UINT width, UINT height)
	{
		//if (width == 0 || height == 0)
		//{
		//	return nullptr;
		//}

		//Image* image = Resources::Find<Image>(name);
		//if (image != nullptr)
		//{
		//	return image;
		//}

		//image = new Image();
		//HDC mainHdc = application.GetHdc();

		//image->mBitmap = CreateCompatibleBitmap(mainHdc, width, height);
		//image->mHdc = CreateCompatibleDC(mainHdc);

		//HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		//DeleteObject(oldBitmap);

		//image->mWidth = width;
		//image->mHeight = height;

		//image->SetKey(name);
		//Resources::Insert<Image>(name, image);

		//// ¹è°æ »öÄ¥
		//HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), myBrush);
		//Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		//SelectObject(image->GetHdc(), oldBrush);
		//DeleteObject(myBrush);

		//return image;
		Image* image = Resources::Find<Image>(name);
		if (image != nullptr)
		{
			return nullptr;
		}
		image = new Image();
		Gdiplus::Bitmap* bmp1 = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
		image->mImage = bmp1;
		Gdiplus::Status status = bmp1->GetHBITMAP(Color(0, 0, 0), &(image->mBitmap));
		if (status != 0)
		{
			return nullptr;
		}
		HDC mainDC = application.GetHdc();
		image->mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = width;
		image->mHeight = height;

		image->SetKey(name);
		Resources::Insert<Image>(name, image);

		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), myBrush);
		Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldBrush);
		DeleteObject(myBrush);

		return image;
		
	}

	Image* Image::Create(const std::wstring& name
		, UINT width, UINT height, COLORREF rgb)
	{
		if (width == 0 || height == 0)
		{
			return nullptr;
		}

		Image* image = Resources::Find<Image>(name);
		if (image != nullptr)
		{
			return image;
		}

		image = new Image();
		HDC mainHdc = application.GetHdc();
		
		image->mBitmap = CreateCompatibleBitmap(mainHdc, width, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = width;
		image->mHeight = height;

		image->SetKey(name);
		Resources::Insert<Image>(name, image);

		// Setting Image Color
		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush2 = (HBRUSH)SelectObject(image->GetHdc(), brush);
		Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldBrush2);
		DeleteObject(oldBrush2);
		return image;
	}
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}
	Image::~Image()
	{
	}
	HRESULT Image::Load(const std::wstring& path)
	{
		/*mBitmap = (HBITMAP)LoadImage(nullptr, path.c_str()
			, IMAGE_BITMAP, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
		{
			return E_FAIL; 
		}

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = application.GetHdc();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);

		return S_OK;*/

		mImage = new Gdiplus::Bitmap(path.c_str());
		mBitmap = nullptr;
		Gdiplus::Status status = mImage->GetHBITMAP(Color(255, 0, 255), &mBitmap);
		if (status != 0)
		{
			MessageBox(nullptr, L"bitmap Load Failed!!!", L"Error", MB_OK);
			return E_FAIL;
		}
		if (mImage->GetLastStatus() != 0)
		{
			return E_FAIL;
		}
		mWidth = mImage->GetWidth();
		mHeight = mImage->GetHeight();
		HDC mainDC = application.GetHdc();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);

		return S_OK;
	}
}