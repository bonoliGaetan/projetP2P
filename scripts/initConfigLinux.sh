if ! test -f listeOption.txt
then
	echo 'Repertoire_Client == SavedFileClient "' > listeOption.txt
	echo 'Repertoire_Server == SavedFileServer "' >> listeOption.txt
	echo "Taille_max_repertoire_Serveur = 10000000" >> listeOption.txt
	echo "Ip_init_Serveur = " >> listeOption.txt
	echo "Ip_address_client = " >> listeOption.txt
	echo "Port_min = 5000" >> listeOption.txt
	echo "Port_max = 5010" >> listeOption.txt
	echo 'Nom == "'>> listeOption.txt

fi

ADDR=`ip addr | grep 'state UP' -A2 | tail -n1 | awk -F'[/ ]+' '{print $3}'`

sed -i "s/Ip_address_client = .*/Ip_address_client = ${ADDR}/" listeOption.txt




