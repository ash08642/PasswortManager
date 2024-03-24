#include "AppSetting.h"

AppSetting::AppSetting()
{
	selected_language = english;
}

AppSetting::~AppSetting()
{
	delete order1;
	delete order2;
	delete order3;
	delete order4;
	delete order5;
	delete order6;
}

void AppSetting::changeLanguage(Languages choice)
{
	switch (choice)
	{
	case AppSetting::English:
		selected_language = english;
		break;
	case AppSetting::German:
		selected_language = german;
		break;
	default:
		break;
	}
}
