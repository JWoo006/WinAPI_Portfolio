#pragma once
#include "jwResource.h"

namespace jw
{
	class Image : public Resource
	{
	public:
		static Image* Create(const std::wstring& name, UINT widht, UINT height);
		static Image* Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb);

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		HDC GetHdc() { return mHdc; }
		HBITMAP GeBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

		Gdiplus::Bitmap* GetImage() { return mImage; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		Gdiplus::Bitmap* mImage;

		UINT mWidth;
		UINT mHeight;

	};
}



