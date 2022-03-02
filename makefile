# 
# FILE          : makefile
# PROJECT       : EncryptDecrypt
# PROGRAMMER    : Elizabeth deVries
# FIRST VERSION : 2022-01-21
# DESCRIPTION   : This is the makefile for EncryptDecrypt
#

# Final target

./bin/EncryptDecrypt: ./obj/encryptDecrypt.o ./obj/translate.o
	cc ./obj/encryptDecrypt.o ./obj/translate.o -o ./bin/EncryptDecrypt
	

# Dependencies

./obj/encryptDecrypt.o: ./src/encryptDecrypt.c ./inc/encryptDecrypt.h
	cc -c ./src/encryptDecrypt.c -o ./obj/encryptDecrypt.o

./obj/translate.o: ./src/translate.c ./inc/encryptDecrypt.h
	cc -c ./src/translate.c -o ./obj/translate.o
	

# Other Targets

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
