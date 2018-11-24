#include "Fenetre.hpp"

Fenetre::Fenetre() : bouton("Afficher le dialogue") {
    add(boiteV);
    
    bouton.set_can_focus(false);
    
    boiteV.pack_start(bouton);
    boiteV.pack_start(etiquette);
    
    bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::afficherDialogue));
    
    show_all();
}

void Fenetre::afficherDialogue() {
    //Création de la boîte de dialogue personnalisée.
    Dialogue dialogue("Boîte de dialogue personnalisée", this, "Veuillez entrer du texte :");
    //Modifier le texte de la zone de texte par celui de l'étiquette.
    dialogue.set_texte(etiquette.get_text());
    
    int reponse = dialogue.run(); //Lancer la boîte de dialogue.
    
    if(reponse == Gtk::RESPONSE_OK) { //Si l'utilisateur clique sur Valider.
        //Modification du texte de l'étiquette par le texte de la zone de texte de la boîte de dialogue.
        etiquette.set_text(dialogue.get_texte());
    }
}
