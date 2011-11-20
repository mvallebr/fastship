
all: 
	cd src && make all 


clean: 
	cd src && make clean 

purge:
	cd src && make purge && rm -f fastship*.stackdump
	
run: all
	./bin/fastship.exe