OSSYS=
ZIP=""
if [ $# = 1 ]
then
	OSSYS="${1}"
else
	OSSYS="linux"
fi

if [ ${OSSYS} = "linux" ] 
then
	if ! test -d appLinuxDir
	then
		mkdir appLinuxDir
	else
		rm -f appLinuxDir/*.exe appLinuxDir/*.sh
	fi

	cp scripts/initConfigLinux.sh appLinuxDir/

	
	make clean appliLinux OS=linux
	cp appliLinux.exe appLinuxDir/

	if [ ${ZIP} = "TRUE" ]
	then
		tar cfzv appLinux.zip appLinuxDir
		rm -rf appLinuxDir
	fi

	make clean
	
elif [ ${OSSYS} = "windows" ]
then

	cd .

fi

