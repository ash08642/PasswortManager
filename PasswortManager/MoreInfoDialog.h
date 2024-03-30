#pragma once

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "AppSetting.h"

class MoreInfoDialog : public wxDialog
{
public:
    MoreInfoDialog(wxWindow* parent, AppSetting* app_setting);
};

