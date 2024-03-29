#pragma once

#include <wx/wx.h>
#include <map>

class AppSetting
{
public:
	AppSetting();
	~AppSetting();

	wxColor* order1 = new wxColor(228, 233, 237);
	wxColor* order2 = new wxColor(189, 195, 199);
	wxColor* order3 = new wxColor(32, 33, 33);

	wxColor* order4 = new wxColor(126, 247, 217);
	wxColor* order5 = new wxColor(0, 251, 188);
	wxColor* order6 = new wxColor(2, 94, 71);

	enum Languages
	{
		English,
		German
	};

	enum TextKeys
	{
		Username,
		Email,
		Password,
		ConfirmPassword,
		CreateNewAccount,
		AlreadyHaveAnAccount,
		DontHaveAnAccount,
		Login,
		Edit,
		Delete,
		Cancel,
		Confirm,
		AddNewAccount,
		MoreInfo,
		PleaseFillAllFields,
		PasswordsDoNotMatch
	};

	std::map<int, std::string> selected_language;
	std::map<int, std::string> english = 
	{
		{TextKeys::Username, "Username"},
		{TextKeys::Email, "Email"},
		{TextKeys::Password, "Password"},
		{TextKeys::ConfirmPassword, "Confirm Password"},
		{TextKeys::CreateNewAccount, "Create account"},
		{TextKeys::AlreadyHaveAnAccount, "Already have an account?"},
		{TextKeys::DontHaveAnAccount, "Don't have an account?"},
		{TextKeys::Login, "Login"},
		{TextKeys::Edit, "Edit"},
		{TextKeys::Delete, "Delete"},
		{TextKeys::Cancel, "Cancel"},
		{TextKeys::Confirm, "Confirm"},
		{TextKeys::AddNewAccount, "Add new Account"},
		{TextKeys::MoreInfo, "Info"},
		{TextKeys::PleaseFillAllFields, "Please fill all Fields"},
		{TextKeys::PasswordsDoNotMatch, "Passwords do not match"}
	};
	std::map<int, std::string> german = {
		{TextKeys::Username, "Benutzername"},
		{TextKeys::Email, "Email"},
		{TextKeys::Password, "Kennwort"},
		{TextKeys::ConfirmPassword, "Kennwort bestätigen "},
		{TextKeys::CreateNewAccount, "Konto erstellen"},
		{TextKeys::AlreadyHaveAnAccount, "Sie haben bereits ein Konto?"},
		{TextKeys::DontHaveAnAccount, "Haben Sie noch kein Konto?"},
		{TextKeys::Login, "anmelden"},
		{TextKeys::Edit, "Bearbeiten"},
		{TextKeys::Delete, "Entfernen"},
		{TextKeys::Cancel, "Abbrechen"},
		{TextKeys::Confirm, "Bestätigen"},
		{TextKeys::AddNewAccount, "Neu Konto hinzufügen"},
		{TextKeys::MoreInfo, "Info"},
		{TextKeys::PleaseFillAllFields, "Bitte alle Feldern füllen"},
		{TextKeys::PasswordsDoNotMatch, "Passwörter stimmen nicht überein"}
	};
	
	void changeLanguage(Languages choice);
};

