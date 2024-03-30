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
	wxColor* order21 = new wxColor(208, 214, 218);
	wxColor* order24 = new wxColor(168, 176, 180);
	wxColor* order3 = new wxColor(32, 33, 33);

	wxColor* order4 = new wxColor(126, 247, 217);
	wxColor* order5 = new wxColor(0, 251, 188);
	wxColor* order6 = new wxColor(255, 181, 52);
	wxColor* order61 = new wxColor(255, 225, 93);

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
		SignOut,
		Edit,
		Delete,
		Cancel,
		Confirm,
		AddNewAccount,
		MoreInfo,
		PleaseFillAllFields,
		PasswordsDoNotMatch,
		GeneratePasssword,
		InfoParagraph,
		PassIsWeak
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
		{TextKeys::SignOut, "Sign Out"},
		{TextKeys::Edit, "Edit"},
		{TextKeys::Delete, "Delete"},
		{TextKeys::Cancel, "Cancel"},
		{TextKeys::Confirm, "Confirm"},
		{TextKeys::AddNewAccount, "+ Add new Account"},
		{TextKeys::MoreInfo, "Info"},
		{TextKeys::PleaseFillAllFields, "Please fill all Fields"},
		{TextKeys::PasswordsDoNotMatch, "Passwords do not match"},
		{TextKeys::GeneratePasssword, "Generate strong Password"}
	};
	std::map<int, std::string> german = {
		{TextKeys::Username, "Benutzername"},
		{TextKeys::Email, "Email"},
		{TextKeys::Password, "Kennwort"},
		{TextKeys::ConfirmPassword, "Kennwort bestätigen "},
		{TextKeys::CreateNewAccount, "Konto erstellen"},
		{TextKeys::AlreadyHaveAnAccount, "Sie haben bereits ein Konto?"},
		{TextKeys::DontHaveAnAccount, "Haben Sie noch kein Konto?"},
		{TextKeys::Login, "Anmelden"},
		{TextKeys::SignOut, "Abmelden"},
		{TextKeys::Edit, "Bearbeiten"},
		{TextKeys::Delete, "Entfernen"},
		{TextKeys::Cancel, "Abbrechen"},
		{TextKeys::Confirm, "Bestätigen"},
		{TextKeys::AddNewAccount, "+ Neu Konto hinzufügen"},
		{TextKeys::MoreInfo, "Info"},
		{TextKeys::PleaseFillAllFields, "Bitte alle Feldern füllen"},
		{TextKeys::PasswordsDoNotMatch, "Passwörter stimmen nicht überein"},
		{TextKeys::GeneratePasssword, "Sicheres Passwort generieren"}
	};
	
	std::map<int, wxString> selected_language2;
	std::map<int, wxString> english2 = {
		{TextKeys::InfoParagraph, R"(This is a basic second generation password manager that
employs sophisticated algorithms to protect passwords with
a master password.
The master password is the key to unlock the vault. So only
the master password needs to be remembered to secure all
other passwords.

Authors:
	aa.ahsan@stud.fh-sm.de
	mm.ahsan@stud.fh-sm.de)"},
		{TextKeys::PassIsWeak, R"(Password is too weak. The security of your saved 
information depends on the strength of your master password.
The Master-Password must contain the following:
	- One lowercase charachter,
	- One uppercase character,
	- One digit(1-9),
	- One special-case character)"}
	};
	std::map<int, wxString> german2 = {
		{TextKeys::InfoParagraph, R"(Dies ist ein grundlegender Passwort-Manager der zweiten Generation,
der hochentwickelte Algorithmen zum Schutz von Passwörtern mit
einem Master-Passwort einsetzt.
Das Master-Kennwort ist der Schlüssel zum Aufschließen des Tresors.
Sie müssen sich also nur das Master-Passwort merken, um alle
anderen Passwörter zu sichern.

Authors:
	aa.ahsan@stud.fh-sm.de
	mm.ahsan@stud.fh-sm.de)"},
		{TextKeys::PassIsWeak, R"(Das Passwort ist zu schwach. Die Sicherheit Ihrer gespeicherten 
Informationen hängt von der Stärke Ihres Master-Passworts ab.
Das Master-Passwort muss Folgendes enthalten:
	- Ein Kleinbuchstabe,
	- Ein Großbuchstabe,
	- Eine Zahl (1-9),
	- Ein Sonderbuchstabe)"}
	};

	void changeLanguage(Languages choice);
};

