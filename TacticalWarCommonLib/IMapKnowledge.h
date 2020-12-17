#pragma once

#include <vector>
#include "Point2D.h"

namespace tw
{
	class BaseCharacterModel;

	class IMapKnowledge
	{
	public:
		virtual std::vector<tw::BaseCharacterModel*> getAliveCharactersInZone(std::vector<tw::Point2D> zone) = 0;
	};

}