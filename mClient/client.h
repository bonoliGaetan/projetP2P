#include<iostream>
#include<string>
#include<vector>
#include<fstream>

#include"../mDataClass/peer.h"

class Client
{
	private:
	std::string url;
	std::vector<Peer> pairListe;
	// TODO => Liste d'option
	
	public:
	// MAYBY TODO => void sauvegarde_fichier(std::string param);
	std::vector<Peer> get_pair_liste(); // getter
	void init_pair_liste(); // Prend le fichier contenant la liste des pair, et remplie pairListe
	void ajout_pair_liste(std::vector<Peer> liste); // Ajoute tous ce qui est dans liste et qui n'est pas dans pairListe
	void ecriture_fichier_liste_pair();
};
