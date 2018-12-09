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

         void FBRegister(std::string url);
    	 void FBUnregister(std::string url);
    	
    	 void FBGetPeerList(std::string peer);
		 void FBGetFileList(std::string peer);

		 void FBGetFile(std::string id);
		 void FBFindFile();
         void FBSendFile(std::string peer);
		 void FBDeleteFile(std::string id);

		 void PeerSelectChanged();

         void FBOpenServeur();
         void FBCloseServeur();

    private :

    	Client* client;
        Serveur* serveur;

        std::string urlSelec;

    	void SetModel();

    	void SetButtons();
    	void AddButtons();

        void MajListFile(std::vector<File> fl);
        void MajListPeer(std::vector<Peer> pl);
    	Gtk::Grid* SetListPeer(std::vector<Peer> pl);
		Gtk::Grid* SetListFile(std::vector<File> fl);

		void FBDisplayFiles(std::string peer);

    	Gtk::Button* SetButton(std::string name, void fctClicked());

    	Gtk::Button* BQuitter;

        Gtk::Button* BFindFile;

        Gtk::Button* BGetPeerListEntry;

    	Gtk::Button* BGetPeerList;
		Gtk::Button* BGetFileList;
        Gtk::Button* BRegister;
        Gtk::Button* BUnregister;
        Gtk::Button* BSendFile;

		Gtk::Button* BGetFile;
		Gtk::Button* BDeleteFile;
    	
		Gtk::Entry* ETextePeer;
        Gtk::Entry* ETexteFile;

		Gtk::ScrolledWindow* ScrollPeer;
		Gtk::ScrolledWindow* ScrollFile;
        Gtk::Grid* BFileList;
        Gtk::Grid* BPeerList;

        Gtk::Alignment* align;

        Gtk::Button* BOpenServeur;
        Gtk::Button* BCloseServeur;
};


#endif
