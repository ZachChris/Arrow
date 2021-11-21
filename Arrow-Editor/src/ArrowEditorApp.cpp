#include <Arrow.h>
#include <Arrow/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Arrow {

	class ArrowEditor : public Application {
	public:
		ArrowEditor() {
			PushLayer(new EditorLayer);
		}
	};

	Application* CreateApplication() {
		return new ArrowEditor();
	}

}