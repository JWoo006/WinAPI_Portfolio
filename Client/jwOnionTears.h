#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Animator;
	class OnionTears : public GameObject
	{
	public:
		enum class eCryState
		{
			introL,
			introR,
	
			End,
		};


		OnionTears();
		OnionTears(int state);
		~OnionTears();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AnimCompleteEvent();

		void CryStart_L_AnimCompleteEvent();
		void CryStart_R_AnimCompleteEvent();

		void SetLoopEnd(bool end) { mbLoopEnd = end; }

	private:
		Animator* mAnimator;
		eCryState mCryState;
		bool mbLoopEnd;
	};
}

