#pragma once
#include "jwScene.h"

namespace jw
{
	class SceneManager
	{
	public:
		// 전역 함수화 - 객체 없이 사용
		// 생성 소멸자도 없음
		// 코드 가독성을 위해 사용 -> ScenenManager::Update();
		// 누구의 update함수인지 알기위해
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
		// 전역 변수화 - 위 함수에서 바로 접근가능
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static eSceneType mNextScene;
	};
}
