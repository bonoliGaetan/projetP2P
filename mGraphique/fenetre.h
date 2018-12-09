#ifndef FENETRE_H
#define FENETRE_H

#include <iostream>
#include <gtkmm.h>

#define LARGEUR 1200
#define HAUTEUR 800

#include "../mClient/client.h"
#include "../mServeur/serveur.h"

#include "../mDataClass/peer.h"
#include "../mDataClass/file.h"



class Fenetre : public Gtk::Window
{
    public :

        ~Fenetre();

        Fenetre(Client*);

        void afficherDialogue();
        
        
         void FBQuitter();

         void FBRegister();
    	 void FBUnregister();
    	
    	 void FBGetPeerList(std::string peer);
		 void FBGetFileList(std::string peer);

		 void FBGetFile(std::string id);
		 void FBFindFile();
         void FBSendFile(std::string peer);
		 void FBDeleteFile(std::string id);

		 void PeerSelectChanged();

    private :

    	Client* client;
        Serveur* serveur;

    	void SetModel();

    	void SetButtons();
    	void AddButtons();

    	Gtk::HButtonBox* SetListPeer(std::vector<Peer> pl);
		Gtk::HButtonBox* SetListFile(std::vector<File> fl);

		void FBDisplayFiles(std::string peer);

    	Gtk::Button* SetButton(std::string name, void fctClicked());

    	Gtk::Button* BQuitter;

    	Gtk::Button* BRegister;
    	Gtk::Button* BUnregister;
    	
    	Gtk::Button* BGetPeerList;
		Gtk::Button* BGetFileList;

		Gtk::Button* BGetFile;
		Gtk::Button* BFindFile;
        Gtk::Button* BSendFile;
		Gtk::Button* BDeleteFile;
    	
		Gtk::Entry* ETextePeer;
        Gtk::Entry* ETexteFile;

		Gtk::ScrolledWindow* ScrollPeer;
		Gtk::ScrolledWindow* ScrollFile;
    	Gtk::HButtonBox* BPeerList;
    	Gtk::HButtonBox* BFileList;

        Gtk::Alignment* align;
};


#endif
