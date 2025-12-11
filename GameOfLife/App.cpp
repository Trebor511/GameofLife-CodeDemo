#include "App.h"
#include "MainWindow.h"
wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {

	ptr = new MainWindow();
	ptr->Show();
	return true;
}