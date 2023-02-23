#pragma once
#include "jwScene.h"

namespace jw
{
	class SceneManager
	{
	public:
		// ���� �Լ�ȭ - ��ü ���� ���
		// ���� �Ҹ��ڵ� ����
		// �ڵ� �������� ���� ��� -> ScenenManager::Update();
		// ������ update�Լ����� �˱�����
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();

		static void LoadScene(eSceneType type);

	private:
		// ���� ����ȭ - �� �Լ����� �ٷ� ���ٰ���
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}
