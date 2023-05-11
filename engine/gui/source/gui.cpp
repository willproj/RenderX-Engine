#include "include/gui.h"

namespace engine::ui
{
	std::shared_ptr<scene::RenderData> Gui::s_renderData;

	Gui::Gui()
	{
	}


	Gui::~Gui()
	{

	}

	void Gui::set(std::shared_ptr<scene::RenderData> renderData)
	{
		s_renderData = renderData;
	}

	void Gui::render()
	{
		
	}

	std::string Gui::getUiName() const
	{
		return uiName;
	}

	bool* Gui::getIsOpenPtr()
	{
		return &isOpen;
	}

	
}