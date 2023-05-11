#pragma once 
#include "gui.h"

namespace engine::ui
{
	class EnvironmentGui :public Gui
	{
	public:
		EnvironmentGui();
		~EnvironmentGui();
		
		EnvironmentGui(const EnvironmentGui& other) = delete;
		EnvironmentGui& operator=(const EnvironmentGui& other) = delete;
		
		void render()override;
	private:

	};
}