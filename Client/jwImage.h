#pragma once
#include "jwResource.h"

namespace jw
{
	class Image : public Resource
	{
	public:
		static Image* Create(const std::wstring& name
			, UINT width, UINT height);

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;
		
		HDC GetHdc() { return mHdc; }
		HBITMAP GeBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;

	};
}



