#ifndef FENETRE_H
#define FENETRE_H

#include <iostream>
#include <gtkmm.h>

#define LARGEUR 1200
#define HAUTEUR 800


#include "../mDataClass/peer.h"
#include "../mDataClass/file.h"

#include "../mClient/client.h"




class Fenetre : public Gtk::Window
{
    public :
        Fenetre(Client pclt, std::string title);
        ~Fenetre();
        void afficherDialogue();
        

        static void FBQuitter();

        static void FBRegister();
    	static void FBUnregister();
    	
    	static void FBGetPeerList(std::string peer);
		static void FBGetFileList(std::string peer);

		static void FBGetFile(std::string id);
		static void FBSaveFile();
		static void FBDeleteFile(std::string id);

		static void PeerSelectChanged();

    private :

    	Client clt;

    	void SetModel();

    	void SetButtons();
    	void AddButtons();

    	Gtk::VBox* SetListPeer(std::vector<Peer> pl);
		Gtk::VBox* SetListFile(std::vector<File> fl);

		void FBDisplayFiles(std::string peer);

    	Gtk::Button* SetButton(std::string name, void fctClicked());

    	Gtk::Button* BQuitter;

    	Gtk::Button* BRegister;
    	Gtk::Button* BUnregister;
    	
    	Gtk::Button* BGetPeerList;
		Gtk::Button* BGetFileList;

		Gtk::Button* BGetFile;
		Gtk::Button* BSaveFile;
		Gtk::Button* BDeleteFile;
    	
		Gtk::Entry* ETextePeer;

		Gtk::ScrolledWindow* ScrollPeer;
		Gtk::ScrolledWindow* ScrollFile;
    	Gtk::VBox* BPeerList;
    	Gtk::VBox* BFileList;

};


#endif
