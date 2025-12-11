#pragma once
#include "wx/wx.h"
class MainWindow;
class App : public wxApp
{
private:

public:
	
	App();
	~App();
	MainWindow* ptr;
	virtual bool OnInit();
};

