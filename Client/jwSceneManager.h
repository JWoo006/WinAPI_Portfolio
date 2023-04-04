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
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetScene(eSceneType type) { return mScenes[(UINT)type]; }
		static void SetActiveScene(Scene* scene) { mActiveScene = scene; }

		static void SetNextSceneType(eSceneType scene) { mNextScene = scene; }
		static eSceneType getNextSceneType() { return mNextScene; }

	private:
		// ���� ����ȭ - �� �Լ����� �ٷ� ���ٰ���
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static eSceneType mNextScene;
	};
}
