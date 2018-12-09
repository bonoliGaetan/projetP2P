#include "fenetre.h"

Fenetre::~Fenetre()
{
	std::cout << "END FENETRE" << std::endl;
}

Fenetre::Fenetre(Client* pclt)
{

	this->client = pclt;
	this->serveur = NULL;

	this->urlSelec = std::string("");

	this->set_title(client->configuration->myUrl);
	this->set_default_size(0,500);
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

Gtk::Grid* Fenetre::SetListPeer(std::vector<Peer> pl)
{
	Gtk::Grid* bret = new Gtk::Grid();
	//bret->set_row_homogeneous(true);
	bret->set_column_homogeneous(true);
	
	int i;
	std::vector<Peer>::iterator it;
	for(it = pl.begin(), i = 0; it != pl.end(); ++it, ++i)
	{
		Gtk::Label* lid = new Gtk::Label(it->url);
		std::string url = it->url;
		Gtk::Button* bgetpeerlist = new Gtk::Button("GetPeerList");
			bgetpeerlist->signal_clicked().connect([this,url]() { FBGetPeerList(url); } );
		Gtk::Button* bgetfilelist = new Gtk::Button("GetFileList");
			bgetfilelist->signal_clicked().connect([this,url]() { FBGetFileList(url); } );
		Gtk::Button* bafffilelist = new Gtk::Button("Display File");
			bafffilelist->signal_clicked().connect([this,url]() { FBDisplayFiles(url); } );
		Gtk::Button* bsendfile = new Gtk::Button("Send File");
			bsendfile->signal_clicked().connect([this,url]() { FBSendFile(url); } );
		Gtk::Button* bregister = new Gtk::Button("Register");
			bregister->signal_clicked().connect([this,url]() { FBRegister(url); } );
		Gtk::Button* bunregister = new Gtk::Button("Unregister");
			bunregister->signal_clicked().connect([this,url]() { FBUnregister(url); } );

		bret->attach(*lid,0,i,1,1);
		bret->attach(*bgetpeerlist,1,i,1,1);
		bret->attach(*bgetfilelist,2,i,1,1);
		bret->attach(*bregister,3,i,1,1);
		bret->attach(*bunregister,4,i,1,1);
		bret->attach(*bafffilelist,5,i,1,1);
		bret->attach(*bsendfile,6,i,1,1);

	}

	return bret;
}


Gtk::Grid* Fenetre::SetListFile(std::vector<File> fl)
{
	Gtk::Grid* bret = new Gtk::Grid();
	//bret->set_row_homogeneous(true);
	bret->set_column_homogeneous(true);

	int i;
	std::vector<File>::iterator it;
	for(it = fl.begin(), i = 0; it != fl.end(); ++it, ++i)
	{
		Gtk::Label* lid = new Gtk::Label(it->id);
		std::string id = it->id;
		Gtk::Label* lname = new Gtk::Label(it->name);
		Gtk::Label* lsize = new Gtk::Label(std::to_string(it->size));
		Gtk::Button* bgetfile = new Gtk::Button("GetFile");
			bgetfile->signal_clicked().connect([this,id]() { FBGetFile(id); } );
		Gtk::Button* bdeletefile = new Gtk::Button("Delete");
			bdeletefile->signal_clicked().connect([this,id]() { FBDeleteFile(id); } );

		bret->attach(*lid,0,i,1,1);
		bret->attach(*lname,1,i,1,1);
		bret->attach(*lsize,2,i,1,1);
		bret->attach(*bgetfile,3,i,1,1);
		bret->attach(*bdeletefile,4,i,1,1);
	}

	return bret;
}

void Fenetre::SetButtons()
{	
	this->BQuitter = new Gtk::Button("Quit");
		BQuitter->signal_clicked().connect([=]() {FBQuitter(); });
	this->BFindFile = new Gtk::Button("Find File");
		BFindFile->signal_clicked().connect([=]() {FBFindFile(); });
	this->BGetPeerListEntry = new Gtk::Button("GetPeerList");
		BGetPeerListEntry->signal_clicked().connect([=]() {
			std::string peer = this->ETextePeer->get_text();
			if(peer == "")
				return;
			this->FBGetPeerList(peer);
		});

	this->ScrollPeer = new Gtk::ScrolledWindow();
		ScrollPeer->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

	this->ScrollFile = new Gtk::ScrolledWindow();
		ScrollFile->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

	this->BFileList = NULL;
	this->BPeerList = NULL;

	this->ETextePeer = new Gtk::Entry();
		ETextePeer->set_max_length(22);

	this->ETexteFile = new Gtk::Entry();
		ETexteFile->set_max_length(256);

	this->BOpenServeur = new Gtk::Button("Open Serveur");
		BOpenServeur->signal_clicked().connect([=]() { FBOpenServeur(); });
	this->BCloseServeur = new Gtk::Button("Close Serveur");
		BCloseServeur->signal_clicked().connect([=]() { FBCloseServeur(); });


}

void Fenetre::AddButtons()
{
	Gtk::Grid* grid = new Gtk::Grid();
	grid->set_row_homogeneous(true);
	grid->set_column_homogeneous(true);
	
		Gtk::Frame* frameN2_1 = new Gtk::Frame("Peer");
			Gtk::HButtonBox* boiteN2_1 = new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER,10);
				boiteN2_1->pack_start(*this->ETextePeer);
				boiteN2_1->pack_start(*this->BGetPeerListEntry);
			frameN2_1->add(*boiteN2_1);
		grid->attach(*frameN2_1,0,0,3,1);

		Gtk::Frame* frameN3_3 = new Gtk::Frame("Import File");
			Gtk::HButtonBox* boiteN2_3 = new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER,10);
				boiteN2_3->pack_start(*this->ETexteFile);
				boiteN2_3->pack_start(*this->BFindFile);
			frameN3_3->add(*boiteN2_3);
		grid->attach(*frameN3_3,3,0,3,1);

		Gtk::Frame* frameN2_2 = new Gtk::Frame("Peer list");
				frameN2_2->add(*this->ScrollPeer);
		grid->attach(*frameN2_2,0,1,6,5);

		Gtk::Frame* frameN2_3 = new Gtk::Frame("File list");
			frameN2_3->add(*this->ScrollFile);
		grid->attach(*frameN2_3,0,6,6,5);

		grid->attach(*this->BQuitter,5,11,1,1);

		Gtk::Frame* frameN2_4 = new Gtk::Frame("My Server");
			Gtk::HButtonBox* boiteN3_1 = new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER,10);
				boiteN3_1->pack_start(*this->BOpenServeur);
				boiteN3_1->pack_start(*this->BCloseServeur);
			frameN2_4->add(*boiteN3_1);
		grid->attach(*frameN2_4,0,11,2,1);

	this->align->add(*grid);
}

void Fenetre::MajListFile(std::vector<File> fl)
{
	this->ScrollFile->remove_with_viewport();
	this->BFileList = SetListFile(fl);
	this->ScrollFile->add(*this->BFileList);

	this->show_all();
}

void Fenetre::MajListPeer(std::vector<Peer> pl)
{
	this->ScrollPeer->remove_with_viewport();
	this->BPeerList = SetListPeer(pl);
	this->ScrollPeer->add(*this->BPeerList);

	this->show_all();
}

void Fenetre::FBQuitter()
{
	Gtk::Main::quit();
}

void Fenetre::FBRegister(std::string url)
{
	std::string peer = this->ETextePeer->get_text();
	if(peer == "")
		return;

	this->client->enregistrer_pair_client(url,peer);

	FBGetPeerList(url);
}

void Fenetre::FBUnregister(std::string url)
{
	std::string peer = this->ETextePeer->get_text();
	if(peer == "")
		return;
	
	this->client->desenregistrer_pair_client(url,peer);

	FBGetPeerList(url);
}

    	
void Fenetre::FBGetPeerList(std::string peer)
{
	this->client->obtenir_liste_pair_client(peer);
	this->urlSelec = peer;
	MajListPeer(this->client->listePair);
}

void Fenetre::FBGetFileList(std::string peer)
{
	this->client->obtenir_liste_fichier_client(peer);
	MajListFile(this->client->obtenir_liste_fichier_d_un_pair(peer));
}


void Fenetre::FBGetFile(std::string id)
{
	this->client->obtenir_fichier_client(urlSelec,id);
}

void Fenetre::FBSendFile(std::string peer)
{
	try {

		std::string name = this->ETexteFile->get_text();
		if(name == "")
			return;

		std::ifstream sfile(name,std::ios::in);
		if(!sfile)
			return;
		sfile.close();

		if(name.rfind("/"))
			name = name.substr(name.rfind("/")+1,name.size());

		File f;
		f.name = name;
		f.body = this->ETexteFile->get_text();
		f.size = 0;

		this->client->sauvegarder_fichier_client(peer,f);

		FBGetFileList(peer);
	}catch(std::exception e)
	{

	}
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
	this->client->supprimer_fichier_client(urlSelec,id);
	FBGetFileList(urlSelec);
}

void Fenetre::FBDisplayFiles(std::string peer)
{
	MajListFile(this->client->obtenir_liste_fichier_d_un_pair(peer));
}

void Fenetre::FBOpenServeur()
{
	if(this->serveur == NULL)
		this->serveur = new Serveur(this->client->configuration);

	if(this->serveur != NULL)
		this->serveur->Open();
}

void Fenetre::FBCloseServeur()
{
	if(this->serveur != NULL)
		this->serveur->Close();
}