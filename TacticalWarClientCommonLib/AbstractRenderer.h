#pragma once

#include <vector>
#include "RendererEventListener.h"
#include "AbstractSpellView.h"

class SpellView;

namespace tw
{
	class Environment;
	class BaseCharacterModel;

	template <class T>
	class AbstractRenderer
	{
		std::vector<RendererEventListener *> listeners;

	protected:
		void notifyCellClicked(int x, int y);
		void notifyCellHover(int x, int y);
		void notifyCellMouseDown(int x, int y);
		void notifyEvent(void * e);

	public:
		AbstractRenderer();
		virtual ~AbstractRenderer();

		virtual void render(Environment* environment, std::vector<BaseCharacterModel*> & characters, std::vector<AbstractSpellView<T*> *> spells, float deltatime) = 0;
		void addEventListener(RendererEventListener * listener);
		bool removeEventListener(RendererEventListener * listener);
	};

	template <class T>
	AbstractRenderer<T>::AbstractRenderer()
	{
	}

	template <class T>
	AbstractRenderer<T>::~AbstractRenderer()
	{
	}

	template <class T>
	void AbstractRenderer<T>::notifyCellClicked(int x, int y)
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onCellClicked(x, y);
		}
	}

	template <class T>
	void AbstractRenderer<T>::notifyCellHover(int x, int y)
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onCellHover(x, y);
		}
	}

	template <class T>
	void AbstractRenderer<T>::notifyCellMouseDown(int x, int y)
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onCellMouseDown(x, y);
		}
	}

	template <class T>
	void AbstractRenderer<T>::notifyEvent(void * e)
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onEvent(e);
		}
	}

	template <class T>
	void AbstractRenderer<T>::addEventListener(RendererEventListener * listener)
	{
		std::vector<RendererEventListener*>::iterator it;
		if ((it = std::find(listeners.begin(), listeners.end(), listener)) == listeners.end())
		{
			listeners.push_back(listener);
		}
	}

	template <class T>
	bool AbstractRenderer<T>::removeEventListener(RendererEventListener * listener)
	{
		std::vector<RendererEventListener*>::iterator it;
		if ((it = std::find(listeners.begin(), listeners.end(), listener)) != listeners.end())
		{
			listeners.erase(it);
			return true;
		}

		return false;
	}
}
