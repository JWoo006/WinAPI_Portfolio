#pragma once
#include "jwEntity.h"

namespace jw
{
	// 추상 클래스 - 순수가상함수가 하나라도 포함하고있다면 추상클래스가 됨
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		//  = 0; <- 무조건 오버라이드 받아서 사용하라는 뜻 순수가상함수   
		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }
		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }
		void SetisFlipedX(bool b) { mbisFlipedX = b; }
		bool GetisFlipedX() { return mbisFlipedX; }
		void SetisFlipedY(bool b) { mbisFlipedY = b; }
		bool GetisFlipedY() { return mbisFlipedY; }

	private:
		std::wstring mKey; //키값
		std::wstring mPath; //파일의 경로
		bool mbisFlipedX;
		bool mbisFlipedY;
	};

	/*class Image : public Resource
	{

	};

	class Sound : public Resource
	{

	};*/

}



