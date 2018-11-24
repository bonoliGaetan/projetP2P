#include "Dialogue.hpp"

Dialogue::Dialogue(std::string titre, Gtk::Window* parent, std::string message) : Gtk::Dialog(titre, *parent), boiteV(get_vbox()), etiquette(message) { //Récupération de la boîte verticale avec get_vbox().
    boiteV->pack_start(etiquette);
    boiteV->pack_start(zoneTexte);

    //Ajout de boutons à la boîte de dialogue.
    add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

    show_all();
}

std::string Dialogue::get_texte() {
    return zoneTexte.get_text();
}

void Dialogue::set_texte(std::string texte) {
    zoneTexte.set_text(texte);
}
