if $1 -eq "linux"
	mkdir applinux
	cp scripts/initConfigLinux.sh applinux/

	make clean client server
	cp client.exe appLinux/
	cp server.exe appLinux/

	zip -r appLinux

	make clean
elif $1 -eq "windows"





fi

