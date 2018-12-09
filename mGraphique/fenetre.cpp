#include "fenetre.h"

Fenetre::~Fenetre()
{
	delete this->serveur;
}

Fenetre::Fenetre(Client* pclt)
{
	printf("INIT FENETRE\n");

	this->client = pclt;
	this->serveur = new Serveur(pclt->configuration);

	this->set_title(client->configuration->myUrl);
	this->set_default_size(0,1000);
	//this->set_default_size(LARGEUR, HAUTEUR);
	this->align = new Gtk::Alignment(Gtk::ALIGN_CENTER,Gtk::ALIGN_CENTER,0,1);
	this->add(*align);
	this->set_border_width(10);

	this->SetButtons();
	this->AddButtons();

	this->show_all();
}


Gtk::Button* Fenetre::SetButton(std::string name, void fctClicked())
{
	Gtk::Button* bret = new Gtk::Button(name);
	bret->signal_clicked().connect([=]() { fctClicked(); } );
	bret->show();

	return bret;
}

Gtk::HButtonBox* Fenetre::SetListPeer(std::vector<Peer> pl)
{
	Gtk::HButtonBox* bret = new Gtk::HButtonBox(Gtk::BUTTONBOX_SPREAD,2);

	Gtk::VButtonBox* col1 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);
	Gtk::VButtonBox* col2 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);
	Gtk::VButtonBox* col3 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);
	Gtk::VButtonBox* col4 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);
	Gtk::VButtonBox* col5 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);

	for(std::vector<Peer>::iterator it = pl.begin(); it != pl.end(); ++it)
	{
		Gtk::Label* lid = new Gtk::Label(it->url);
		std::string url = it->url;
		Gtk::Button* bgetpeerlist = new Gtk::Button("GetPeerList");
			bgetpeerlist->signal_clicked().connect([=]() { FBGetPeerList(url); } );
		Gtk::Button* bgetfilelist = new Gtk::Button("GetFileList");
			bgetfilelist->signal_clicked().connect([=]() { FBGetFileList(url); } );
		Gtk::Button* bafffilelist = new Gtk::Button("Display File");
			bafffilelist->signal_clicked().connect([=]() { FBDisplayFiles(url); } );
		Gtk::Button* bsendfile = new Gtk::Button("Send File");
			bsendfile->signal_clicked().connect([=]() { FBSendFile(url); } );

		col1->pack_start(*lid);
		col2->pack_start(*bgetpeerlist);
		col3->pack_start(*bgetfilelist);
		col4->pack_start(*bafffilelist);
		col5->pack_start(*bsendfile);
	}

	bret->pack_start(*col1);
	bret->pack_end(*col2);
	bret->pack_end(*col3);
	bret->pack_end(*col4);
	bret->pack_end(*col5);

	return bret;
}


Gtk::HButtonBox* Fenetre::SetListFile(std::vector<File> fl)
{
	Gtk::HButtonBox* bret = new Gtk::HButtonBox(Gtk::BUTTONBOX_SPREAD,2);

	Gtk::VButtonBox* col1 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);
	Gtk::VButtonBox* col2 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);
	Gtk::VButtonBox* col3 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);
	Gtk::VButtonBox* col4 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);
	Gtk::VButtonBox* col5 = new Gtk::VButtonBox(Gtk::BUTTONBOX_START,2);

	for(std::vector<File>::iterator it = fl.begin(); it != fl.end(); ++it)
	{
		Gtk::Label* lid = new Gtk::Label(it->id);
		std::string id;
		Gtk::Label* lname = new Gtk::Label(it->name);
		Gtk::Label* lsize = new Gtk::Label(std::to_string(it->size));
		Gtk::Button* bgetfile = new Gtk::Button("GetFile");
			bgetfile->signal_clicked().connect([=]() { FBGetFile(id); } );
		Gtk::Button* bdeletefile = new Gtk::Button("Delete");
			bdeletefile->signal_clicked().connect([=]() { FBDeleteFile(id); } );

		col1->pack_start(*lid);
		col2->pack_start(*lname);
		col3->pack_start(*lsize);
		col4->pack_start(*bgetfile);
		col5->pack_start(*bdeletefile);
	}

	bret->pack_start(*col1);
	bret->pack_start(*col2);
	bret->pack_start(*col3);
	bret->pack_end(*col4);
	bret->pack_end(*col5);
	

	return bret;
}

void Fenetre::SetButtons()
{	
	printf("INIT BUTTONS\n");

	this->BQuitter = new Gtk::Button("Quit");
		BQuitter->signal_clicked().connect([this]() {FBQuitter(); });
	this->BRegister = new Gtk::Button("Register");
		BRegister->signal_clicked().connect([this]() {FBRegister(); });
	this->BUnregister = new Gtk::Button("Unregister");
		BUnregister->signal_clicked().connect([this]() {FBUnregister(); });
	this->BFindFile = new Gtk::Button("Find File");
		BFindFile->signal_clicked().connect([this]() {FBFindFile(); });

	this->ScrollPeer = new Gtk::ScrolledWindow();
		ScrollPeer->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	this->BPeerList = SetListPeer(client->configuration->listePair);
		this->ScrollPeer->add(*this->BPeerList);

	this->ScrollFile = new Gtk::ScrolledWindow();
		ScrollFile->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	this->BFileList = SetListFile(serveur->listeFichier);
		this->ScrollFile->add(*this->BFileList);

	this->ETextePeer = new Gtk::Entry();
		this->ETextePeer->set_max_length(22);

	this->ETexteFile = new Gtk::Entry();
		this->ETexteFile->set_max_length(256);


}
void Fenetre::AddButtons()
{
	printf("INIT WINDOW\n");

	Gtk::Table* table = new Gtk::Table(6,16);
	
		Gtk::Frame* frameN2_1 = new Gtk::Frame("Pair");
			Gtk::HButtonBox* boiteN2_1 = new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER,10);
				boiteN2_1->pack_start(*this->ETextePeer);
				boiteN2_1->pack_start(*this->BRegister);
				boiteN2_1->pack_start(*this->BUnregister);
			frameN2_1->add(*boiteN2_1);
		table->attach(*frameN2_1,0,6,0,1,Gtk::FILL);

		Gtk::Frame* frameN3_3 = new Gtk::Frame("Fichier");
			Gtk::HButtonBox* boiteN2_3 = new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER,10);
				boiteN2_3->pack_start(*this->ETexteFile);
				boiteN2_3->pack_start(*this->BFindFile);
			frameN3_3->add(*boiteN2_3);
		table->attach(*frameN3_3,0,6,1,2,Gtk::FILL);

		Gtk::Frame* frameN2_2 = new Gtk::Frame("Liste des Pairs");
				frameN2_2->add(*this->ScrollPeer);
		table->attach(*frameN2_2,0,6,2,8,Gtk::FILL);

		Gtk::Frame* frameN2_3 = new Gtk::Frame("Liste des fichiers");
			frameN2_3->add(*this->ScrollFile);
		table->attach(*frameN2_3,0,6,8,15,Gtk::FILL);

		table->attach(*this->BQuitter,0,6,15,16,Gtk::FILL,Gtk::SHRINK);

	this->align->add(*table);
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

void Fenetre::FBSendFile(std::string peer)
{
	std::cout << peer << std::endl;
	std::string name = this->ETexteFile->get_text();
	name = name.substr(name.rfind("/")+1,name.size());
	
	File f;
	f.name = name;
	f.body = this->ETexteFile->get_text();
	f.size = 0;

	this->client->sauvegarder_fichier_client(peer,f);
}

void Fenetre::FBFindFile()
{
	
	Gtk::FileChooserDialog FCDial = Gtk::FileChooserDialog("Please choose a file",Gtk::FILE_CHOOSER_ACTION_OPEN);
	FCDial.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  	FCDial.add_button("_Open", Gtk::RESPONSE_OK);


  	int result = FCDial.run();

  	switch(result)
	{
	    case(Gtk::RESPONSE_OK):
	    {
		    this->ETexteFile->set_text(FCDial.get_filename());     
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
