if [ $1 = "linux" ] 
then
	mkdir appLinuxDir
	cp scripts/initConfigLinux.sh appLinuxDir/

	make clean appliLinux
	cp appliLinux.exe appLinuxDir/

	tar cfzv appLinux.zip appLinuxDir

	make clean
	rm -rf appLinuxDir
elif [ $1 = "windows" ]
then



fi

