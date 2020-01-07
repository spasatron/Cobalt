#pragma once

#include "Cobalt/Core.h"
#include "Layer.h"
//Didn't know how to make use with the precompiled header
#include <vector>



namespace Cobalt {

	class COBALT_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();


		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }



	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layerInsert = 0;
	};

}