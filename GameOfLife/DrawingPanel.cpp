#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "MainWindow.h"
#include "Settings.h"
#include "Dialog.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

//Creates a panel to render the game onto
DrawingPanel::DrawingPanel(wxFrame* parent, std::vector < std::vector<bool>>& board, std::vector<std::vector<int>>& neighbors, Settings* settings) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(600, 600)), boardS(board), _neighbors(neighbors)
{

	pSettings = settings;
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);
}

DrawingPanel::~DrawingPanel() {}

//Renders what we are seeing in the panel
void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context) { return; }


	context->SetBrush(*wxWHITE);

	if (pSettings->ShowGrid == false)
	{
		context->SetPen(wxColor(0,0,0,50));
	}
	else
	{
		context->SetPen(wxTransparentColor);
	}
	context->SetFont(wxFontInfo(10), *wxRED);

	int cHeight = GetSize().GetY() / (*pSettings).gSize;
	int cWidth = GetSize().GetX() / (*pSettings).gSize;
	for (int j = 0; j < (*pSettings).gSize; j++)
	{

		for (int i = 0; i < (*pSettings).gSize; i++)
		{
			if (boardS[i][j] == true)
			{
				context->SetBrush(pSettings->GetLiveColor());
			}
			else { context->SetBrush(pSettings->GetDeadColor()); }

			context->DrawRectangle(i * cWidth, j * cHeight, cWidth, cHeight);

			if (pSettings->ShowNeighborCount)
			{
				if (_neighbors[i][j] > 0)
				{
					wxString cellnum = std::to_string(_neighbors[i][j]);

					double textWidth, textHeight;
					context->GetTextExtent(cellnum, &textWidth, &textHeight);

					context->DrawText(cellnum, (i * cWidth) + (cWidth - textWidth) / 2, (j * cHeight) + (cHeight - textHeight) / 2);
				}

			}

		}
	}
	if (pSettings->ShowThickGrid)
	{
		for (int i = 0; i < pSettings->gSize / 10; i++)
		{
			wxPoint vStart(cWidth * 10 * (i + 1), 0);
			wxPoint vEnd(cWidth * 10 * (i + 1), cWidth * pSettings->gSize);
			
			dc.DrawLine(vStart, vEnd);
		}
		for (int i = 0; i < pSettings->gSize/ 10; i++)
		{
			wxPoint hStart(0, cHeight * 10 * (i + 1));
			wxPoint hEnd(this->GetSize().x, cHeight * 10 * (i + 1));

			dc.DrawLine(hStart, hEnd);
		}
	}

	if (pSettings->ShowHUD)
	{
		double X = this->GetSize().x;
		double Y = this->GetSize().y;
		double x = X;
		double y = Y;
		//make seperate variables
		wxString hud;

		if (pSettings->IsFinite)
		{
			hud = "Generation: " + std::to_string(pSettings->generation) + "\nLiving Cells: " + std::to_string(pSettings->liveCells) + '\n' + "Boundry Type: Finite \nUniverse Size: " + std::to_string(pSettings->gSize);
		}
		else
		{
			hud = "Generation: " + std::to_string(pSettings->generation) + "\nLiving Cells: " + std::to_string(pSettings->liveCells) + '\n' + "Boundry Type: Torodial \nUniverse Size: " + std::to_string(pSettings->gSize);
		}
		
		context->SetFont(wxFontInfo(16), *wxBLUE);
		context->GetTextExtent(hud,&X,&Y );
		context->DrawText(hud, x / 50 , y / 50);
	}
	delete context;

}

void DrawingPanel::SetWindowSize(wxSize& size)
{

wxPanel:SetSize(size);
	Refresh();

}

void DrawingPanel::SetGridSize(int size)
{
	(*pSettings).gSize = size;
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
	int _x = event.GetX();
	int _y = event.GetY();
	int cHeight = GetSize().GetY() / (*pSettings).gSize;
	int cWidth = GetSize().GetX() / (*pSettings).gSize;

	int xClick = _x / cWidth;
	int yClick = _y / cHeight;

	if (xClick < (*pSettings).gSize && yClick < (*pSettings).gSize) {

		if (boardS[xClick][yClick] == true)
		{
			boardS[xClick][yClick] = false;
			pSettings->liveCells--;
		}
		else {
			boardS[xClick][yClick] = true;
			pSettings->liveCells++;
		}
	}
	Refresh();

}