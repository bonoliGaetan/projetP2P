ADDR=`ip addr | grep 'state UP' -A2 | tail -n1 | awk -F'[/ ]+' '{print $3}'`

echo 'Repertoire_Client == SavedFileClient "' > listeOption.txt
echo 'Repertoire_Server == SavedFileServer "' >> listeOption.txt
echo "Taille_max_repertoire_Serveur = 1000000000" >> listeOption.txt
echo "Ip_init_Serveur = ${1}" >> listeOption.txt
echo 'Ip_address_client = ${ADDR}'
echo "Port_min = 5000" >> listeOption.txt
echo "Port_max = 5010" >> listeOption.txt
echo 'Nom == ${2} "'>> listeOption.txt





