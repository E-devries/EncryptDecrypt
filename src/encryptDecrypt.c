/*
 * FILE          : encryptDecrypt.c
 * PROJECT       : EncryptDecrypt
 * PROGRAMMER    : Elizabeth deVries
 * FIRST VERSION : 2022-01-21
 * DESCRIPTION   : This file contains the main function for the encryptDecrypt project,
 *                 which encrypts files with the -encrypt [file] command line argument, 
 *                 and decrypts with -decrypt [file]. The encrypted file will always have a .crp
 *                 file extension, and the encryption manipulates all non-carriage return ascii characters.
*/
 
 
#include "../inc/encryptDecrypt.h"

// Constants

const char *TAB_ENCODE = "TT";      	// the special character sequence for encoding tabs

// command line constants
const char *USAGE = "USAGE:\t\t EncryptDecrypt -[switch] fileName\nUSAGE (encrypt):\t EncryptDecrypt fileName\n";
const char *SWITCHES = "SWITCHES:\n\tencrypt :\t encrypts the file and outputs as a .crp file\n\tdecrypt :\t decrypts the file and outputs as a .txt file\n";
const char *ENCRYPT_SWITCH = "-encrypt";
const char *DECRYPT_SWITCH = "-decrypt";

// bool constants
const bool ENCRYPT = true;
const bool DECRYPT = false;

// file extension constants
const char *ENCRYPT_EXT = ".crp";
const char *DECRYPT_EXT = ".txt";

 
int main (int argc, char *argv[])
{
	 // initialize main return code and bool to determine whether program is decrypting or encrypting
	 int returnCode = 0;
	 bool translationMode = ENCRYPT;

 	// check for 1 to 2 arguments not counting program name and exit if count is off
	if (argc == 1 || argc > 3)
	{
		printf("Incorrect number of command line arguments.\n\n%s%s", USAGE, SWITCHES);
		returnCode = -1;

	}
	// check for if 2 arguments, that first is one of the switches
	else if (argc == 3 && strcmp(argv[1], ENCRYPT_SWITCH) != 0 && strcmp(argv[1], DECRYPT_SWITCH) != 0)
	{
		printf("Incorrect switch usage.\n\n%s%s", USAGE, SWITCHES);
		returnCode = -2;
	}


	// if arguments okay, proceed to file I/O
 	else
	{

		char fileName[MAX_FILE_NAME] = {' '};

		// if 1 argument, copy filename from that arg 
		if (argc == 2)
		{
			strcpy(fileName, argv[1]);
		}
		// otherwise, copy filename from 2nd arg and check first arg for switch
		else
		{
			strcpy(fileName, argv[2]);

			// if switch is decode, change translation mode from default 'encrypt' to 'decrypt'
			if (strcmp(argv[1], DECRYPT_SWITCH) == 0)
			{
				translationMode = DECRYPT;
			}
		}

		// attempt to open input file
		FILE *inFile = fopen(fileName, "r");
		if (inFile == NULL)
		{
			// if null, return with error code
			printf("FILE I/O ERROR: input file failed to open.\n");
			returnCode = 1;
			return returnCode;
		}

		// get output file name by copying original file name and deleting extension if it exists
		char outFileName[256] = {' '};
		createOutFileName(outFileName, fileName, translationMode);

		// attempt to open output file based on translationMode
		FILE *outFile = fopen(outFileName, "w");
		if (outFile == NULL)
		{
			// if null, return with error code
			printf("FILE I/O ERROR: output file failed to open");
			returnCode = 1;
			return returnCode;
		}


		// Read file 1 line at a time from infile, decrypt/encrypt the line, then write to outfile
		while(feof(inFile) == 0)
		{
			char lineToTranslate[MAX_TRANSLATION_STRING] = {' '};
			// make sure line isn't null in the case of an empty file
			if (fgets(lineToTranslate, MAX_TRANSLATION_STRING, inFile) != NULL)
			{
				// convert line and write to output file
				char translatedLine[MAX_TRANSLATION_STRING] = {' '};
				translateString(translatedLine, lineToTranslate, translationMode);
				
				fprintf(outFile, "%s", translatedLine);
			}
		}


		// close files and end program
		if (fclose(inFile) != 0)
		{
			// if not 0, inform user and return with error code
			printf("FILE I/O ERROR: input file failed to close properly.\n");
			returnCode = 2;
		}
		if (fclose(outFile) != 0)
		{
			// not 0, so inform user and return error code
			printf("FILE I/O ERROR: output file failed to close properly\n");
			returnCode = 2;
		}

	}

 	return returnCode;
}



// FUNCTION    : createOutFileName
// PARAMETERS  : char *outFileName : the name to be used for the output file generated in this function
//               char *inFileName  : the name of the input file
//               bool translationMode : indicates whether the output file needs to be .txt for decryption (false) or .crp for encryption (true)
// RETURNS     : void
// DESCRIPTION : This function creates the filename to use for the output file based on the input file name and whether it is being encrypted or decrypted
void createOutFileName(char *outFileName, char *inFileName, bool translationMode)
{
    strcpy(outFileName, inFileName);

	// check if extension exists by looking for last '.'
	char *extensionDot = strrchr(outFileName, '.');
	if (extensionDot != NULL)
	{

		// delete extenstion from outFileName by replacing dot with null terminator
		*extensionDot = '\0';

	}

    // add new extentsion based on mode
    if (translationMode == ENCRYPT)
	{
        strcat(outFileName, ENCRYPT_EXT);
	}
	else
	{
        strcat(outFileName, DECRYPT_EXT);
	}

    return;
}
