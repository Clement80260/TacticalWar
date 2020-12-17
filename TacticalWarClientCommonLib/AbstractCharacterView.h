#pragma once

namespace tw
{
	class BaseCharacterModel;

	template<class ConcreteSpriteType>
	class AbstractCharacterView
	{
		BaseCharacterModel* model;

	public:
		AbstractCharacterView(BaseCharacterModel* model);
		virtual ~AbstractCharacterView();

		inline BaseCharacterModel* getModel() {
			return model;
		}

		virtual ConcreteSpriteType getImageToDraw() = 0;
		virtual ConcreteSpriteType getMaskToDraw() = 0;
		virtual void update(float deltatime) = 0;
	};

	template<class ConcreteSpriteType>
	AbstractCharacterView<ConcreteSpriteType>::AbstractCharacterView(BaseCharacterModel* model)
	{
		this->model = model;
	}

	template<class ConcreteSpriteType>
	AbstractCharacterView<ConcreteSpriteType>::~AbstractCharacterView()
	{

	}
}