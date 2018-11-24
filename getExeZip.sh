OSSYS="linux"
ZIP="false"

if test $# -ge 1
then
	OSSYS="${1}"	
fi

if test $# -ge 2
then
	ZIP="${2}"
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

	if [ ${ZIP} = "true" ]
	then
		zip -r appLinux.zip appLinuxDir/
		rm -rf appLinuxDir
	fi

	make clean
	
elif [ ${OSSYS} = "windows" ]
then

	if ! test -d appWindowsDir
	then
		mkdir appWindowsDir
	else
		rm -f appWindowsDir/*.exe appWindowsDir/*.sh
	fi

	cp scripts/initConfigWindows.sh appWindowsDir/

	make clean appliWindows OS=windows
	cp appliWindows.exe appWindowsDir/
	
	cd appWindowsDir
	. initConfigWindows.sh
	rm -f initConfigWindows.sh
	cd ..

	if [ ${ZIP} = "true" ] 
	then
		7z a appWindows.zip appWindowsDir/
		rm -rf appWindowsDir
	fi

	make clean

fi

