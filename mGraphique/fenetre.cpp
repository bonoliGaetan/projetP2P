#include "fenetre.h"

Fenetre::Fenetre(Client pclt, std::string title)
{
	this->set_title(title);

	this->clt = pclt;

	this->SetButtons();
	this->AddButtons();

}



Fenetre::~Fenetre()
{



}

Gtk::Button Fenetre::SetButton(std::string name, void fctClicked())
{
	Gtk::Button bret = Gtk::Button(name);
	bret.signal_clicked().connect([=]() { fctClicked(); } );
	bret.show();

	return bret;
}

void Fenetre::SetButtons()
{	
	this->BQuitter = SetButton("Quitter",&(Fenetre::FBQuitter));
}

void Fenetre::AddButton()
{
	this->add(this->BQuitter);
}

static void Fenetre::FBQuitter()
{
	Gtk::Main::quit();
}