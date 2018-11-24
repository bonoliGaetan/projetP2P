#ifndef DEF_FENETRE
#define DEF_FENETRE

#include <iostream>

#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>


#include "../mClient/client.h"

class Fenetre : public Gtk::Window
{
    public :
        Fenetre(Client pclt, std::string title);
        ~Fenetre();
        void afficherDialogue();
        

        static void FBQuitter();
    private :

    	Client clt;

    	void SetButtons();
    	void AddButtons();
    	void AddButton();

    	Gtk::Button SetButton(std::string name, void fctClicked());

    	Gtk::Button BQuitter;

    	

        
};

#endif
