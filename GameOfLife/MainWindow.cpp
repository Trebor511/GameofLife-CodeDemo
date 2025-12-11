#include "MainWindow.h"
#include "Settings.h"
#include "wx/wx.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "Dialog.h"
#include "wx/numdlg.h"
#include "wx/filedlg.h"



wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(10511, MainWindow::PlayButton)
EVT_MENU(10113, MainWindow::PauseButton)
EVT_MENU(10674, MainWindow::NextButton)
EVT_MENU(10101, MainWindow::TrashButton)
EVT_TIMER(19662, MainWindow::TimeTicker)
EVT_MENU(10478, MainWindow::OnOptionsClick)
EVT_MENU(10633, MainWindow::OnRandomize)
EVT_MENU(10634, MainWindow::OnRandomSeed)
EVT_MENU(11221, MainWindow::OnNew)
EVT_MENU(11222, MainWindow::OnOpen)
EVT_MENU(11223, MainWindow::OnSave)
EVT_MENU(11224, MainWindow::OnSaveAs)
EVT_MENU(wxID_EXIT, MainWindow::OnExit)
EVT_MENU(11226, MainWindow::NeighborsCheck)
EVT_MENU(11227, MainWindow::OnFinite)
EVT_MENU(11228, MainWindow::OnTorodial)
EVT_MENU(11229, MainWindow::OnReset)
EVT_MENU(11230, MainWindow::OnImport)
EVT_MENU(11231, MainWindow::ShowGrid)
EVT_MENU(11232, MainWindow::ShowThickGrid)
EVT_MENU(11233,MainWindow::ShowHUD)

wxEND_EVENT_TABLE()

MainWindow::~MainWindow()
{
}

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game Of Life", wxPoint(0, 0), wxSize(600, 600))
{
	settings.LoadData();
	wxBitmap playIcon(play_xpm);
	wxBitmap pauseIcon(pause_xpm);
	wxBitmap nextIcon(next_xpm);
	wxBitmap trashIcon(trash_xpm);

	status = CreateStatusBar();
	tool = CreateToolBar();

	tool->AddTool(10511, "Begin", playIcon);
	tool->AddTool(10113, "Stop", pauseIcon);
	tool->AddTool(10674, "Next", nextIcon);
	tool->AddTool(10101, "Trash", trashIcon);
	tool->Realize();

	pDrawingPanel = new DrawingPanel(this, boardState, _neighbors, &settings);
	menu = new wxMenuBar();
	wxMenu* fileMenu = new wxMenu();
	wxMenu* optionsMenu = new wxMenu();
	wxMenu* viewMenu = new wxMenu();

	showNeighborCount = new wxMenuItem(viewMenu, 11226, "Show Neighbor Count", "", wxITEM_CHECK);
	finiteMode = new wxMenuItem(viewMenu, 11227, "Enter Finite Mode", "", wxITEM_CHECK);
	torodialMode = new wxMenuItem(viewMenu, 11228, "Enter Torodial Mode", "", wxITEM_CHECK);
	resetMode = new wxMenuItem(optionsMenu, 11229, "Reset All Options", "", wxITEM_CHECK);
	showGrid = new wxMenuItem(viewMenu, 11231, "Hide Grid", "", wxITEM_CHECK);
	showThickGrid = new wxMenuItem(viewMenu, 11232, "Show 10x10 Grid", "", wxITEM_CHECK);
	showHUD = new wxMenuItem(viewMenu, 11233, "Show HUD", "", wxITEM_CHECK);

	finiteMode->SetCheckable(true);
	torodialMode->SetCheckable(true);
	showGrid->SetCheckable(true);
	showHUD->SetCheckable(true);
	

	fileMenu->Append(11230, "Import");
	fileMenu->Append(11222, "Open");
	fileMenu->Append(11223, "Save");
	fileMenu->Append(11224, "Save As");
	fileMenu->Append(11221, "New");
	fileMenu->Append(wxID_EXIT, "Exit");

	optionsMenu->Append(10478, "Settings");
	optionsMenu->Append(10633, "Randomize");
	optionsMenu->Append(10634, "Ramdomize With Seed");
	optionsMenu->Append(11229, "Reset Options");

	viewMenu->Append(showHUD);
	viewMenu->Append(showNeighborCount);
	viewMenu->Append(showGrid);
	viewMenu->Append(showThickGrid);
	viewMenu->Append(finiteMode);
	viewMenu->Append(torodialMode);

	finiteMode->Check(settings.IsFinite);
	torodialMode->Check(settings.IsTorodial);
	showNeighborCount->Check(settings.ShowNeighborCount);
	showGrid->Check(settings.ShowGrid);
	showThickGrid->Check(settings.ShowThickGrid);
	showHUD->Check(settings.ShowHUD);

	menu->Append(fileMenu, "&File");
	menu->Append(viewMenu, "&View");
	menu->Append(optionsMenu, "&Options");
	SetMenuBar(menu);



	timer = new wxTimer(this, 19662);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(pDrawingPanel, 1, wxEXPAND | wxALL);

	this->SetSizer(sizer);
	this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
	InitializeGrid();
	UpdateStatusBar();
	this->Layout();
	
}
void MainWindow::OnSizeChange(wxSizeEvent& event)
{
	wxSize wSize = GetSize();

	if (pDrawingPanel != nullptr)
	{
		pDrawingPanel->SetSize(wSize);
		pDrawingPanel->Refresh();
		event.Skip();
	}

}

void MainWindow::InitializeGrid()
{
	boardState.resize(settings.gSize);
	_neighbors.resize(settings.gSize);
	for (int i = 0; i < settings.gSize; i++)
	{
		boardState[i].resize(settings.gSize);
		_neighbors[i].resize(settings.gSize);
	}
	pDrawingPanel->SetGridSize(settings.gSize);

}
void MainWindow::UpdateStatusBar()
{
	status->SetStatusText("Generation: " + std::to_string(settings.generation) + "  Living Cells: " + std::to_string(settings.liveCells));

}

int MainWindow::CalculateNeighbors(int x, int y)
{
	int neighbors = 0;



	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{

			if (settings.IsFinite)
			{
				if ((x + i >= 0 && x + i <= settings.gSize - 1) && (y + j >= 0 && y + j <= settings.gSize - 1))
				{

					if (i == 0 && j == 0)
					{

					}
					else if (boardState[x + i][y + j] == true)

					{
						neighbors++;
					}

				}
			}
			else if (settings.IsTorodial)
			{
				int tempx = x;
				int tempy = y;

				if ((i + x) < 0)
				{
					tempx = settings.gSize;
				}
				else if ((i + x) >= settings.gSize)
				{
					tempx = -1;
				}


				if ((j + y) < 0)
				{
					tempy = settings.gSize;
				}
				else if ((j + y) >= settings.gSize)
				{
					tempy = -1;
				}

				if (i == 0 && j == 0)
				{

				}
				else if (boardState[tempx + i][tempy + j] == true)

				{
					neighbors++;
				}


			}


		}
	}


	return neighbors;
}

void MainWindow::NextGen()
{
	std::vector <std::vector<bool>> sandbox;
	sandbox.resize(settings.gSize);
	_neighbors.resize(settings.gSize);

	for (int i = 0; i < settings.gSize; i++)
	{
		sandbox[i].resize(settings.gSize);
		_neighbors[i].resize(settings.gSize);
	}


	for (int j = 0; j < settings.gSize; j++)
	{
		for (int i = 0; i < settings.gSize; i++)
		{

			if (boardState[i][j] == true && CalculateNeighbors(i, j) < 2) //less than 2
			{
				sandbox[i][j] = false;

			}
			else if (boardState[i][j] == true && CalculateNeighbors(i, j) > 3) //more than 3
			{
				sandbox[i][j] = false;

			}
			else if (boardState[i][j] == true && (CalculateNeighbors(i, j) == 2 || CalculateNeighbors(i, j) == 3)) //2 or 3
			{
				sandbox[i][j] = true;

			}
			else if (boardState[i][j] == false && CalculateNeighbors(i, j) == 3) //exactly 3
			{
				sandbox[i][j] = true;

			}
		}
	}

	settings.liveCells = 0;
	for (int j = 0; j < settings.gSize; j++) //Counts living cells
	{
		for (int i = 0; i < settings.gSize; i++)
		{
			if (sandbox[i][j] == true)
			{
				settings.liveCells++;
			}
		}
	}
	swap(boardState, sandbox);

	for (int j = 0; j < settings.gSize; j++)
	{
		for (int i = 0; i < settings.gSize; i++)
		{
			int count = CalculateNeighbors(i, j);
			_neighbors[i][j] = count;
		}
	}
	settings.generation++;
	UpdateStatusBar();
	pDrawingPanel->Refresh();
}

void MainWindow::PlayButton(wxCommandEvent& event)
{
	timer->Start(settings.timeSpeed);
}
void MainWindow::PauseButton(wxCommandEvent& event)
{
	timer->Stop();
}
void MainWindow::NextButton(wxCommandEvent& event)
{
	timer->Stop();
	NextGen();
}
void MainWindow::TrashButton(wxCommandEvent& event)
{
	timer->Stop();
	settings.generation = 0;
	settings.liveCells = 0;
	for (int j = 0; j < settings.gSize; j++)
	{
		for (int i = 0; i < settings.gSize; i++)
		{
			boardState[i][j] = false;
		}
	}

	UpdateStatusBar();
	pDrawingPanel->Refresh();
	Refresh();
}
void MainWindow::TimeTicker(wxTimerEvent& event)
{
	NextGen();
}

void MainWindow::OnOptionsClick(wxCommandEvent& event)
{
	Dialog* poptions = new Dialog(this, &settings);

	if (poptions->ShowModal() == wxID_OK)
	{
		settings.SaveData();
		InitializeGrid();
		//pDrawingPanel->Refresh();
	}
	else
	{
		settings.LoadData();
	}
	Refresh();
}

void MainWindow::OnRandomize(wxCommandEvent& event)
{
	srand(time(NULL));

	for (int i = 0; i < settings.gSize; i++)
	{
		for (int j = 0; j < settings.gSize; j++)
		{
			int num = rand();
			if (num % 2 == 0)
			{
				boardState[i][j] = true;
			}
			else
			{
				boardState[i][j] = false;
			}
		}
	}
	pDrawingPanel->Refresh();
}
void MainWindow::OnRandomSeed(wxCommandEvent& event)
{
	long number = wxGetNumberFromUser("Enter a Random Seed", "Seed:", "Seed Randomizer", 888, 0, LONG_MAX, this);
	srand(number);

	for (int i = 0; i < settings.gSize; i++)
	{
		for (int j = 0; j < settings.gSize; j++)
		{
			int random = rand();

			if (random % 2 == 0)
			{
				boardState[i][j] = true;
			}
			else
			{
				boardState[i][j] = false;
			}
		}
	}
	pDrawingPanel->Refresh();
}
void MainWindow::OnNew(wxCommandEvent& event)     //
{
	settings.generation = 0;
	settings.liveCells = 0;
	for (int j = 0; j < settings.gSize; j++)
	{
		for (int i = 0; i < settings.gSize; i++)
		{
			boardState[i][j] = false;
		}
	}

	settings.saveFile = "";
	UpdateStatusBar();
	pDrawingPanel->Refresh();
}
void MainWindow::OnOpen(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Open the Game of Life", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);
	if (fileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}
	for (int i = 0; i < boardState.size(); i++)
	{
		boardState[i].clear();
		boardState.resize(0);

	}
	boardState.clear();
	boardState.resize(0);

	std::string buffer;
	std::ifstream fileStream;
	int index = 0;

	fileStream.open((std::string)fileDialog.GetPath());

	if (fileStream.is_open())
	{
		while (!fileStream.eof())
		{
			std::getline(fileStream, buffer);
			if (buffer.size() == 0)
			{
				continue;
			}
			if (boardState.size() == 0)
			{
				boardState.resize(buffer.size());
			}
			boardState[index].resize(buffer.size());

			for (int i = 0; i < buffer.size(); i++)
			{
				if (buffer[i] == '*')
				{
					boardState[index][i] = true;
				}
				else
				{
					boardState[index][i] = false;
				}
			}
			index++;
		}

		fileStream.close();
		settings.gSize = index;
	}
	Refresh();
	event.Skip();
}


void MainWindow::OnSave(wxCommandEvent& event)
{
	if (settings.saveFile == "")
	{
		wxFileDialog fileDialog(this, "Save the Game of Life", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (fileDialog.ShowModal() == wxID_OK)
		{
			settings.saveFile = (std::string)fileDialog.GetPath();
			return;
		}
	}

	std::ofstream fileStream;
	fileStream.open(settings.saveFile);
	if (fileStream.is_open())
	{
		for (int i = 0; i < boardState.size(); i++)
		{
			for (int j = 0; j < boardState[i].size(); j++)
			{
				if (boardState[i][j] == true)
				{
					fileStream << "*";
				}
				else
				{
					fileStream << ".";
				}
			}
			fileStream << "\n";
		}

		fileStream.close();
	}
	event.Skip();
}
void MainWindow::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Save the Game of Life", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (fileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}
	std::ofstream fileStream;
	settings.saveFile = (std::string)fileDialog.GetPath();
	fileStream.open((std::string)fileDialog.GetPath());
	if (fileStream.is_open())
	{
		for (int i = 0; i < boardState.size(); i++)
		{
			for (int j = 0; j < boardState[i].size(); j++)
			{
				if (boardState[i][j] == true)
				{
					fileStream << "*";
				}
				else
				{
					fileStream << ".";
				}
			}
			fileStream << "\n";
		}

		fileStream.close();
	}
	event.Skip();

}
void MainWindow::OnExit(wxCommandEvent& event)
{
	Close();
}

void MainWindow::NeighborsCheck(wxCommandEvent& event)
{
	settings.ShowNeighborCount = !settings.ShowNeighborCount;
	showNeighborCount->Check(settings.ShowNeighborCount);
	Refresh();
	event.Skip();
}

void MainWindow::OnFinite(wxCommandEvent& event)
{
	settings.IsTorodial = false;
	settings.IsFinite = true;
	finiteMode->Check(settings.IsFinite);
	torodialMode->Check(settings.IsTorodial);
	Refresh();
	event.Skip();
}

void MainWindow::OnTorodial(wxCommandEvent& event)
{
	settings.IsFinite = false;
	settings.IsTorodial = true;
	finiteMode->Check(settings.IsFinite);
	torodialMode->Check(settings.IsTorodial);
	Refresh();
	event.Skip();
}

void MainWindow::OnReset(wxCommandEvent& event)
{
	settings.gSize = 15;
	settings.timeSpeed = 50;

	settings.lRed = 128;
	settings.lBlue = 128;
	settings.lGreen = 128;
	settings.lAlpha = 255;

	settings.dRed = 255;
	settings.dBlue = 255;
	settings.dGreen = 255;
	settings.dAlpha = 255;

	settings.SaveData();
	Refresh();
	event.Skip();
}

void MainWindow::OnImport(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Open the Game of Life", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);
	if (fileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	std::string buffer;
	std::ifstream fileStream;
	std::vector <std::vector<bool>> sandbox;

	int index = 0;

	fileStream.open((std::string)fileDialog.GetPath());

	if (fileStream.is_open())
	{
		while (!fileStream.eof())
		{
			std::getline(fileStream, buffer);
			if (buffer.size() == 0)
			{
				continue;
			}
			if (sandbox.size() == 0)
			{
				sandbox.resize(buffer.size());
			}
			sandbox[index].resize(buffer.size());

			for (int i = 0; i < buffer.size(); i++)
			{

				if (buffer[i] == '*')
				{
					sandbox[index][i] = true;
				}
				else
				{
					sandbox[index][i] = false;
				}
			}
			index++;
		}

		fileStream.close();
	}
	if (boardState.size() < sandbox.size())
	{
		for (int i = 0; i < boardState.size(); i++)
		{
			for (int j = 0; j < boardState[i].size() - 1; j++)
			{
				if (j <= boardState.size())
				{

					boardState[i][j] = sandbox[i][j];
				}
			}



		}

	}
	else if (sandbox.size() <  boardState.size())
	{
		
		for (int i = 0; i < sandbox.size(); i++)
		{
			for (int j = 0; j < sandbox[i].size() - 1; j++)
			{
				if (sandbox[i].size() == 0)
				{
					break;
				}
				if (j <= sandbox.size() || i <= sandbox.size())
				{

					boardState[i][j] = sandbox[i][j];
				}
			}
		}
	}
	Refresh();
	event.Skip();
}

void MainWindow::ShowGrid(wxCommandEvent& event)
{
	settings.ShowGrid = !settings.ShowGrid;
	showGrid->Check(settings.ShowGrid);
	Refresh();
	event.Skip();
}
void MainWindow::ShowThickGrid(wxCommandEvent& event)
{
	settings.ShowThickGrid = !settings.ShowThickGrid;
	showThickGrid->Check(settings.ShowThickGrid);
	Refresh();
	event.Skip();
}
void MainWindow::ShowHUD(wxCommandEvent& event)
{
	settings.ShowHUD = !settings.ShowHUD;
	showHUD->Check(settings.ShowHUD);
	Refresh();
	event.Skip();
}

