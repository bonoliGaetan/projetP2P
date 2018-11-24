#ifndef DEF_FENETRE
#define DEF_FENETRE

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/main.h>

#include "Dialogue.hpp"

class Fenetre : public Gtk::Window {
    public :
        Fenetre();
        void afficherDialogue();
        
    private :
        Gtk::VBox boiteV;
        Gtk::Button bouton;
        Gtk::Label etiquette;
};

#endif
