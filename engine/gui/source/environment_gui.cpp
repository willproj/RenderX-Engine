#include "include/environment_gui.h"


namespace engine::ui
{
	EnvironmentGui::EnvironmentGui()
	{
		isOpen = true;
		uiName = "Environment";
	}

	EnvironmentGui::~EnvironmentGui()
	{

	}
	
	void EnvironmentGui::render()
	{
		if (isOpen)
		{
			ImGui::Begin(uiName.c_str(), &isOpen);
			
			
			
			ImGui::End();
		}
	}

}