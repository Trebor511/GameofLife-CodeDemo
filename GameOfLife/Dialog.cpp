#include "Dialog.h"
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "Settings.h"


wxBEGIN_EVENT_TABLE(Dialog, wxDialog)
EVT_SPINCTRL(10644, Dialog::ChooseGridSize)
EVT_SPINCTRL(11232, Dialog::ChooseInterval)
EVT_COLOURPICKER_CHANGED(11225, Dialog::ChooseLiveColor)
EVT_COLOURPICKER_CHANGED(11231, Dialog::ChooseDeadColor)

wxEND_EVENT_TABLE()

Dialog::Dialog(wxWindow* parent, Settings* settings) : wxDialog(parent, wxID_ANY, "Da Settings")
{
	pSettings = settings;
	sText = new wxStaticText(this, wxID_ANY, "Change Grid Size	");
	nText = new wxStaticText(this, wxID_ANY, "Change Live Cell Color ");
	iText = new wxStaticText(this, wxID_ANY, "Change Speed of Universe ");
	dText = new wxStaticText(this, wxID_ANY, "Change Dead Cell Color ");

	numSelect = new wxSpinCtrl(this, 10644, "Select Grid Size",wxDefaultPosition, wxDefaultSize,16384L, 1, 200);
	speedSelect = new wxSpinCtrl(this, 11232, "Select Speed of Universe", wxDefaultPosition, wxDefaultSize, 16384L, 1, 2000);
	colSelect = new wxColourPickerCtrl(this, 11225, "Select Live Color");
	deadSelect = new wxColourPickerCtrl(this, 11231, "Select Dead Color");
	

	mainBox = new wxBoxSizer(wxVERTICAL);
	
	child1Box = new wxBoxSizer(wxHORIZONTAL);
	child2Box = new wxBoxSizer(wxHORIZONTAL);
	child3Box = new wxBoxSizer(wxHORIZONTAL);
	child4Box = new wxBoxSizer(wxHORIZONTAL);
	

	child1Box->Add(sText);
	child1Box->Add(numSelect);

	child4Box->Add(iText);
	child4Box->Add(speedSelect);

	child2Box->Add(nText);
	child2Box->Add(colSelect);

	child3Box->Add(dText);
	child3Box->Add(deadSelect);

	okCan = CreateButtonSizer(wxOK | wxCANCEL);

	mainBox->Add(child1Box);
	mainBox->Add(child2Box);
	mainBox->Add(child3Box);
	mainBox->Add(child4Box);

	mainBox->Add(okCan);
	SetSizer(mainBox);


	numSelect->SetValue(pSettings->gSize);
	speedSelect->SetValue(pSettings->timeSpeed);
	colSelect->SetColour(pSettings->GetLiveColor());
	deadSelect->SetColour(pSettings->GetDeadColor());
}

void Dialog::ChooseGridSize(wxSpinEvent& event)
{
	pSettings->gSize = event.GetValue();
	event.Skip();
}
void Dialog::ChooseLiveColor(wxColourPickerEvent& event)
{
	pSettings->SetLiveColor(colSelect->GetColour());
	event.Skip();
}

void Dialog::ChooseDeadColor(wxColourPickerEvent& event)
{
	pSettings->SetDeadColor(deadSelect->GetColour());
	event.Skip();
}

void Dialog::ChooseInterval(wxSpinEvent& event)
{
	pSettings->timeSpeed = speedSelect->GetValue();
	event.Skip();
}