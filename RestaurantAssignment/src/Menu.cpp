#include "Menu.h"

Menu* Menu::m_Menu = nullptr;
MenuDestroyer Menu::destroyer;

MenuDestroyer::MenuDestroyer(Menu *s)
{
	_singleton = s;
}

Menu::Menu()
{
	getMenuList();
}

Menu* Menu::getMenu() {
	if (!m_Menu)
	{
		m_Menu = new Menu;
		destroyer.SetSingleton(m_Menu);
	}
	return m_Menu;
}

Menu::~Menu()
{
}