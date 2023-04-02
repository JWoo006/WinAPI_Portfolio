#include "jwImage.h"
#include "jwApplication.h"
#include "jwResources.h"

extern jw::Application application;

namespace jw
{
	Image::Image()
		:mHdc(NULL)
		, mImage(nullptr)
	{
	}
	Image::~Image()
	{
	}
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

		//// 배경 색칠
		//HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), myBrush);
		//Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		//SelectObject(image->GetHdc(), oldBrush);
		//DeleteObject(myBrush);

		//return image;
		
		Image* image = Resources::Find<Image>(name);
		if (image != nullptr)
		{
			return image;
		}

		image = new Image();
		HDC mainHdc = application.GetHdc();

		Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
		image->mImage = bmp;
		bmp->GetHBITMAP(Color(255, 0, 255), &(image->mBitmap));

		image->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = width;
		image->mHeight = height;

		image->SetKey(name);
		Resources::Insert<Image>(name, image);

		

		return image;
	}

	//카메라
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
	void Image::ImageFlipX()
	{
		mImage->RotateFlip(RotateFlipType::RotateNoneFlipX);
		/*mImage->GetHBITMAP(Color(255, 0, 255), &mBitmap);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);*/
		mbReverse = true;
	}
}