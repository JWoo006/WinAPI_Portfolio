#pragma once
#include "jwGameObject.h"
#include "jwImage.h"

namespace jw
{
	class Tile : public GameObject
	{
	public:
		Tile();
		Tile(Vector2 pos);
		~Tile();

		void InitializeTile(Image* atlas, int index);
		void SetIndex(int index);

		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		Image* mAtlas;
		int mIndex;
		int mX;
		int mY;
	};
}


