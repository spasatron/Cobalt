
#include "cbpc.h"

#include "LayerStack.h"




namespace Cobalt {

	LayerStack::LayerStack() {
		m_layerInsert = 0;
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {

		m_layers.emplace(m_layers.begin() + m_layerInsert, layer);
		m_layerInsert++;
		
	}
	void LayerStack::PushOverlay(Layer* overlay) {
		m_layers.emplace_back(overlay);
	}
	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
			m_layers.erase(it);


	}
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			m_layerInsert--;
		}
	}



}
