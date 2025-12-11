#pragma once
#include "wx/wx.h"
#include <fstream>
struct Settings
{
public:
	int gSize = 15;
	int timeSpeed = 50;
	int generation = 0;
	int liveCells = 0;

	unsigned int lRed = 128;
	unsigned int lBlue = 128;
	unsigned int lGreen = 128;
	unsigned int lAlpha = 255;

	unsigned int dRed = 255;
	unsigned int dBlue = 255;
	unsigned int dGreen = 255;
	unsigned int dAlpha = 255;

	bool ShowHUD = false;
	bool ShowGrid = true;
	bool ShowThickGrid = false;
	bool ShowNeighborCount = false;
	bool IsFinite = true;
	bool IsTorodial = false;

	std::string saveFile;

	void SetLiveColor(wxColor color)
	{
		lRed = color.GetRed();
		lBlue = color.GetBlue();
		lGreen = color.GetGreen();
		lAlpha = color.GetAlpha();
	}

	wxColor GetLiveColor()
	{
		wxColor color(lRed, lGreen, lBlue, lAlpha);
		return color;
	}

	void SetDeadColor(wxColor color)
	{
		dRed = color.GetRed();
		dBlue = color.GetBlue();
		dGreen = color.GetGreen();
		dAlpha = color.GetAlpha();
	}

	wxColor GetDeadColor()
	{
		wxColor color(dRed, dGreen, dBlue, dAlpha);
		return color;
	}

	void LoadData()
	{
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		file.read((char*)this, sizeof(Settings));
		file.close();
	}

	void SaveData()
	{
		std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
		file.write((char*)this, sizeof(Settings));
		file.close();
	}
};

