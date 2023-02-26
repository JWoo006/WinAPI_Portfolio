#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Cuphead_Stage : public GameObject
	{
	public:
		Cuphead_Stage();
		~Cuphead_Stage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		float mTime;
		int mIdx;
		
	};
}

