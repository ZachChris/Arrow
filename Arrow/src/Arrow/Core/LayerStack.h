#pragma once

#include "Layer.h"
#include <vector>

namespace Arrow {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
	
		std::vector<Layer*>::iterator begin() { return m_LayerStack.begin(); }
		std::vector<Layer*>::iterator end() { return m_LayerStack.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_LayerStack.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_LayerStack.rend(); }

		const std::vector<Layer*>::const_iterator begin() const { return m_LayerStack.begin(); }
		const std::vector<Layer*>::const_iterator end() const { return m_LayerStack.end(); }
		const std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_LayerStack.rbegin(); }
		const std::vector<Layer*>::const_reverse_iterator rend() const { return m_LayerStack.rend(); }

	private:
		std::vector<Layer*> m_LayerStack;
		unsigned int m_LayerInsertIndex = 0;
	};

}