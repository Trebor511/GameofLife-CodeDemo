#pragma once
#include "wx/wx.h"
#include "Settings.h"
class MainWindow;
class DrawingPanel : public wxPanel
{



public:
	Settings* pSettings;
	std::vector<std::vector<bool>>& boardS;
	std::vector<std::vector<int>>& _neighbors;
	DrawingPanel(wxFrame* parent, std::vector < std::vector<bool>>& board, std::vector<std::vector<int>>& neighbors, Settings* settings);
	~DrawingPanel();
	void OnPaint(wxPaintEvent& event);
	void SetWindowSize(wxSize& size);
	void SetGridSize(int size);
	void OnMouseUp(wxMouseEvent& event);

	wxDECLARE_EVENT_TABLE();
};

