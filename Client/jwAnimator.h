#pragma once
#include "jwComponent.h"
#include "jwAnimation.h"
#include "jwImage.h"

namespace jw
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
				{
					mEvent();
				}
			}

			//void(*name)(int, int);
			std::function<void()> mEvent; //void타입의 인자없는 함수포인터
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent; // 하나의 동작이 완료됬을때
			Event mEndEvent; // 애니메이션이 전환될때
		};

		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		// 스프라이트 시트
		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop
			, UINT coulmn, UINT row, UINT spriteLength
			, Vector2 offset, float duration);
		// 스프라이트로 애니메이션 제작하는 함수
		void CreateAnimations(); 

		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop);

		Events* FindEvents(const std::wstring& name);
		/*std::function<void>& GetStartEvent(const std::wstring& name);
		std::function<void>& GetCompleteEvent(const std::wstring& name);
		std::function<void>& GetEndEvent(const std::wstring& name);*/

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;

		Image* mSpriteSheet;
		bool mbLoop;
	};
}



