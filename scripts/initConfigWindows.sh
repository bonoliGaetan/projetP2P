if ! test -f config.json
then

	#Les valeurs du JSON suivant sont modifiables par l'utilisateur 
	# /!\ la structure du JSON doit être respecté
	REP_CLIENT=SavedFileClient
	REP_SERVER=SavedFileServer

	echo '{' > config.json
	echo '"Repertoire_Client":' "\"${REP_CLIENT}\"," >> config.json
	echo '"Repertoire_Server":' "\"${REP_SERVER}\"," >> config.json
	echo '"Taille_max_repertoire_Serveur":10000000,' >> config.json
	echo '"Ip_init_Serveur":"",' >> config.json
	echo '"Ip_address_client":"",' >> config.json
	echo '"Port_min":5000,' >> config.json
	echo '"Port_max":5010,' >> config.json
	echo '"Nom":""'>> config.json
	echo '}' >> config.json
fi

if ! test -d ${REP_CLIENT}
then
	mkdir ${REP_CLIENT}
fi

if ! test -d ${REP_SERVER}
then
	mkdir ${REP_SERVER}
fi

if ! test -d tmpP2P
then
	mkdir tmpP2P
fi

if ! test -d logs
then
	mkdir logs
fi


