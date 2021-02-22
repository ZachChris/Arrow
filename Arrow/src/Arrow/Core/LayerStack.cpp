#include "arpch.h"

#include "LayerStack.h"

namespace Arrow {

	LayerStack::LayerStack() {
		m_LayerInsert = m_LayerStack.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_LayerStack)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_LayerInsert = m_LayerStack.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_LayerStack.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end()) {
			m_LayerStack.erase(it);
			m_LayerInsert--;
		}	
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), overlay);
		if (it != m_LayerStack.end()) {
			m_LayerStack.erase(it);
			m_LayerInsert--;
		}
	}

}