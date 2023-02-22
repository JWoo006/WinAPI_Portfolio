#pragma once
#include "jwEntity.h"

namespace jw
{
	// �߻� Ŭ���� - ���������Լ��� �ϳ��� �����ϰ��ִٸ� �߻�Ŭ������ ��
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		//  = 0; <- ������ �������̵� �޾Ƽ� ����϶�� �� ���������Լ�   
		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }
		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mKey; //Ű��
		std::wstring mPath; //������ ���
	};

	/*class Image : public Resource
	{

	};

	class Sound : public Resource
	{

	};*/

}


