#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"


class DrawingPanel;
class Settings;
class Dialog : public wxDialog
{
public:
	Dialog(wxWindow* parent , Settings* settings);
	wxBoxSizer* mainBox;
	wxSizer* okCan;
	Settings* pSettings;

	wxBoxSizer* child1Box;
	wxBoxSizer* child2Box;
	wxBoxSizer* child3Box;
	wxBoxSizer* child4Box;

	wxStaticText* dText;
	wxStaticText* iText;
	wxStaticText* sText;
	wxStaticText* nText;
	
	wxMenuItem* showNeighborCount;

	wxSpinCtrl* numSelect;
	wxSpinCtrl* speedSelect;
	wxColourPickerCtrl* deadSelect;
	wxColourPickerCtrl* colSelect; 

	void ChooseGridSize(wxSpinEvent& event);
	void ChooseLiveColor(wxColourPickerEvent& event);
	void ChooseDeadColor(wxColourPickerEvent& event);
	void ChooseInterval(wxSpinEvent& event);
	

	wxDECLARE_EVENT_TABLE();
};

