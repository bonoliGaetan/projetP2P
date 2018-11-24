#include "fenetre.h"

Fenetre::Fenetre(Client pclt, std::string title)
{
	this->set_title(title);
	this->set_default_size(LARGEUR, HAUTEUR);
	this->set_border_width(10);
	this->clt = pclt;

	this->SetButtons();
	this->AddButtons();

	this->show_all();
}



Fenetre::~Fenetre()
{



}


Gtk::Button* Fenetre::SetButton(std::string name, void fctClicked())
{
	Gtk::Button* bret = new Gtk::Button(name);
	bret->signal_clicked().connect([=]() { fctClicked(); } );
	bret->show();

	return bret;
}

Gtk::VBox* Fenetre::SetListPeer(std::vector<Peer> pl)
{
	Gtk::VBox* bret = new Gtk::VBox(false,2);

	for(std::vector<Peer>::iterator it = pl.begin(); it != pl.end(); ++it)
	{
		Gtk::Box* PeerBox = new Gtk::HBox(false,2);
		Gtk::Label* lid = new Gtk::Label(it->url);
		Gtk::Label* lname = new Gtk::Label(it->name);
		Gtk::Button* bgetpeerlist = new Gtk::Button("GetPeerList");
			bgetpeerlist->signal_clicked().connect([=]() { FBGetPeerList(it->url); } );
			bgetpeerlist->show();
		Gtk::Button* bgetfilelist = new Gtk::Button("GetFileList");
			bgetpeerlist->signal_clicked().connect([=]() { FBGetFileList(it->url); } );
			bgetpeerlist->show();
		Gtk::Button* bafffilelist = new Gtk::Button("Display File");
			bafffilelist->signal_clicked().connect([=]() { FBDisplayFiles(it->url); } );
			bafffilelist->show();
		
		PeerBox->pack_start(*lid);
		PeerBox->pack_start(*lname);
		PeerBox->pack_start(*bgetpeerlist);
		PeerBox->pack_start(*bgetfilelist);

		bret->pack_start(*PeerBox);
	}
	return bret;
}

Gtk::VBox* Fenetre::SetListFile(std::vector<File> fl)
{
	Gtk::VBox* bret = new Gtk::VBox(false,2);

	for(std::vector<File>::iterator it = fl.begin(); it != fl.end(); ++it)
	{
		Gtk::Box* FileBox = new Gtk::HBox(false,2);
		Gtk::Label* lid = new Gtk::Label(it->id);
		Gtk::Label* lname = new Gtk::Label(it->name);
		Gtk::Label* lsize = new Gtk::Label(std::to_string(it->size));

		Gtk::Button* bgetfile = new Gtk::Button("GetFile");
			bgetfile->signal_clicked().connect([it]() { FBGetFile(it->id); } );
			bgetfile->show();
		Gtk::Button* bdeletefile = new Gtk::Button("Delete");
			bdeletefile->signal_clicked().connect([it]() { FBDeleteFile(it->id); } );
			bdeletefile->show();
		
		FileBox->pack_start(*lid);
		FileBox->pack_start(*lname);
		FileBox->pack_start(*lsize);
		FileBox->pack_start(*bgetfile);
		FileBox->pack_start(*bdeletefile);

		bret->pack_start(*FileBox);
	}
	return bret;
}

void Fenetre::SetButtons()
{	
	this->BQuitter = SetButton("Quit",&(Fenetre::FBQuitter));
	this->BRegister = SetButton("Register",&(Fenetre::FBRegister));
	this->BUnregister = SetButton("Unregister",&(Fenetre::FBUnregister));

	this->BSaveFile = SetButton("Save File",&(Fenetre::FBSaveFile));
	this->ScrollPeer = new Gtk::ScrolledWindow();
		ScrollPeer->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	this->BFileList = SetListFile(clt.configuration.listeFichier);
	this->ScrollFile = new Gtk::ScrolledWindow();
		ScrollFile->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	this->BPeerList = SetListPeer(clt.configuration.listePair);

}
void Fenetre::AddButtons()
{

	Gtk::VBox* BoiteN1 = new Gtk::VBox(Gtk::PACK_SHRINK,10);
	
		Gtk::Frame* frameN2_1 = new Gtk::Frame("Pair");
			Gtk::HBox* boiteN2_1 = new Gtk::HBox(false,10);
			
				this->ETextePeer = new Gtk::Entry();
				this->ETextePeer->set_max_length(22);

				boiteN2_1->pack_start(*this->ETextePeer);
				boiteN2_1->pack_start(*this->BRegister);
				boiteN2_1->pack_start(*this->BUnregister);

			frameN2_1->add(*boiteN2_1);
		BoiteN1->pack_start(*frameN2_1);


		Gtk::HBox* boiteN2_2 = new Gtk::HBox(false,10);

			Gtk::Frame* frameN2_2 = new Gtk::Frame("Liste des Pairs");
				Gtk::HBox* boiteN3_2 = new Gtk::HBox(false,10);

					this->ScrollPeer->add(*this->BPeerList);

					boiteN3_2->pack_start(*this->ScrollPeer);

				frameN2_2->add(*boiteN3_2);

			boiteN2_2->pack_start(*frameN2_2);


			Gtk::Frame* frameN2_3 = new Gtk::Frame("Liste des fichiers");
				Gtk::HBox* boiteN3_1 = new Gtk::HBox(false,10);
					this->ScrollFile->add(*this->BFileList);
					boiteN3_1->pack_start(*this->ScrollFile);
				frameN2_3->add(*boiteN3_1);
			boiteN2_2->pack_start(*frameN2_3);


		BoiteN1->pack_start(*boiteN2_2);

		Gtk::HButtonBox* boiteN2_3 = new Gtk::HButtonBox(Gtk::BUTTONBOX_END,10);
			boiteN2_3->pack_end(*this->BQuitter);
		BoiteN1->pack_end(*boiteN2_3);

	this->add(*BoiteN1);
}


void Fenetre::FBQuitter()
{
	Gtk::Main::quit();
}

void Fenetre::FBRegister()
{
	
}

void Fenetre::FBUnregister()
{

}

    	
void Fenetre::FBGetPeerList(std::string peer)
{
	

}

void Fenetre::FBGetFileList(std::string peer)
{

}


void Fenetre::FBGetFile(std::string id)
{

}

void Fenetre::FBSaveFile()
{
	
	Gtk::FileChooserDialog FCDial = Gtk::FileChooserDialog("Please choose a file",Gtk::FILE_CHOOSER_ACTION_OPEN);

  	int result = FCDial.run();

  	switch(result)
	{
	    case(Gtk::RESPONSE_OK):
	    {
		    std::cout << FCDial.get_filename() << std::endl;     
			break;
		}
		case(Gtk::RESPONSE_CANCEL):
		{
		    break;
		}
		default:
		{
		    break;
	    }
  	}
}

void Fenetre::FBDeleteFile(std::string id)
{

}

void Fenetre::FBDisplayFiles(std::string peer)
{

}