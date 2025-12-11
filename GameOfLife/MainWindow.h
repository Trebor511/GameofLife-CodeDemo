#pragma once
#include "wx/wx.h"
#include "Settings.h"
#include <vector>
class DrawingPanel;
class MainWindow : public wxFrame
{
	
private:
	
	DrawingPanel* pDrawingPanel = nullptr; 
	
	
public:
	Settings settings;
	wxStatusBar* status = nullptr;
	wxBoxSizer* sizer = nullptr;
	wxToolBar* tool = nullptr;
	wxTimer* timer = nullptr;
	wxMenuBar* menu = nullptr;
	wxMenuItem* showNeighborCount;
	wxMenuItem* finiteMode;
	wxMenuItem* torodialMode;
	wxMenuItem* resetMode;
	wxMenuItem* showGrid;
	wxMenuItem* showThickGrid;
	wxMenuItem* showHUD;
	MainWindow();

	~MainWindow();

	void OnSizeChange(wxSizeEvent& event);
	
	std::vector <std::vector<bool>> boardState;
	std::vector <std::vector<int>> _neighbors;

	void InitializeGrid();
	void UpdateStatusBar();
	void PlayButton(wxCommandEvent& event);
	void PauseButton(wxCommandEvent& event);
	void NextButton(wxCommandEvent& event);
	void TrashButton(wxCommandEvent& event);
	int CalculateNeighbors(int x, int y);
	void NextGen();
	void TimeTicker(wxTimerEvent& event);
	void OnOptionsClick(wxCommandEvent& event);
	void OnRandomize(wxCommandEvent& event);
	void OnRandomSeed(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void NeighborsCheck(wxCommandEvent& event);
	void OnTorodial(wxCommandEvent& event);
	void OnFinite(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	void OnImport(wxCommandEvent& event);
	void ShowGrid(wxCommandEvent& event);
	void ShowThickGrid(wxCommandEvent& event);
	void ShowHUD(wxCommandEvent& event);

	
	
	wxDECLARE_EVENT_TABLE();
};

