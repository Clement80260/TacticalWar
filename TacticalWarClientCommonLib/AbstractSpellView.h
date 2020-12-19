#pragma once
namespace tw
{
	class BaseCharacterModel;

	template<class ConcreteSpriteType>
	class AbstractSpellView
	{
		int x, y;

	public:
		AbstractSpellView(int x, int y);
		virtual ~AbstractSpellView();


		virtual ConcreteSpriteType getImageToDraw() = 0;
		virtual void update(float deltatime) = 0;

		inline int getX() { return x; }
		inline int getY() { return y; }
	};

	template<class ConcreteSpriteType>
	AbstractSpellView<ConcreteSpriteType>::AbstractSpellView(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	template<class ConcreteSpriteType>
	AbstractSpellView<ConcreteSpriteType>::~AbstractSpellView()
	{

	}
}