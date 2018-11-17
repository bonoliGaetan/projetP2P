#include<iostream>
#include<string>
#include<list>

#include"../mDataClass/peer.h"
#include"../mDataClass/file.h"

class Client
{
	private:
	std::string url;
	std::list<Peer> pairListe;
	std::map<std::string,int> options;
	
	public:
	void sauvegarde_fichier(std::string param);
	std::list<Peer> get_pair_liste();
	void init_pair_liste();
	void ajout_pair_liste(std::list<Peer> liste);
	// TODO => Faire une fct qui prend un fichier texte, qui lit et qui ecrit le contenue du txt dans pairListe 
	// TODO => Faire une fct qui prend un pairListe puis une autre liste de pair, qui enregistre dans pairListe les 
	// nouveau pair, et qui met a jour la liste des pair dans le fichier texte (tous les nouveau pair sont ajoutes 
	// dans la liste du fichier texte).
};
