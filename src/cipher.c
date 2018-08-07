#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE 6
#define BUFFER_LIMIT 100000

/**
 * @brief      	Converts a character of the original message in a ciphered character
 *
 * @param 	 	coefficient   The coefficient is a number to plus on char value
 * @param  		originalChar  The original character is the character to be ciphered.
 *
 * @return     	The ciphered char
 */
char generateCharacter( int coefficient, char originalChar )
{
	char newChar = originalChar + coefficient;
	if( originalChar >= 'a' && originalChar <= 'z' )
	{
		if( newChar > 'z' )
		{
			int diff = newChar - 'z';
			newChar = 'a' + diff - 1; 
		}
	}
	else if( originalChar >= 'A' && originalChar <= 'Z' ) 
	{
		if( newChar > 'Z' )
		{
			int diff = newChar - 'Z';
			newChar = 'A' + diff - 1; 
		}
	} else 
	{
		newChar = originalChar;
	}

	return newChar;
}

/**
 * @brief 		Generate and saves in the output file the encrypted message.
 *  
 * @param 		dataNumbers array with the digits of input date
 * @param 		inputFile pointer for input file to read the original message
 * @param 		outputFilename string name of the output file on system
 * 
 * @return 		0 in sucess, 1 in otherwise
 */
int generateCipher( int* dataNumbers, FILE * inputFile, char * outputFilename )
{
    int letterIndex = 0;
   	FILE * outputFile = fopen( outputFilename, "w" ); // opens a new file to save de coded message
 
    if( outputFile == NULL )
    {
        	printf( "Não foi possível criar arquivo de saída" );
        	return 1;
   	}
	
	char buffer[BUFFER_LIMIT]; // array to bufferize 100 characters of the original file content. The last one char is '\0'.
	char encryptedBuffer[BUFFER_LIMIT];  // array to bufferize 100 characters of the encrypted file content. The last one char is '\0'.
    while( fscanf( inputFile, "%s", buffer ) > 0 )
	{
		int i;
		for( i = 0; buffer[ i ] != '\0'; i++ )
		{
			if( buffer[ i ] != ' ' )
			{
				encryptedBuffer[ i ] = generateCharacter( dataNumbers[ letterIndex % DATA_SIZE ], buffer[ i ] );
				letterIndex++;
			} else 
			{
				encryptedBuffer[ i ] = buffer[ i ];
			}
		}
		encryptedBuffer[ i ] = '\0';
		fprintf( outputFile, "%s ", encryptedBuffer ); 
		
	}
	fprintf( outputFile, "\n" );
	fclose( outputFile );
	return 0;

}


int main( int argc, char ** argv )
{
     if( argc != 4 )
    {
        printf( "Invalid Arguments!\n" );
        return 1;
    }

    FILE * inputFile =  fopen( argv[2], "r" );

    if( inputFile == NULL )
    {
        printf( "Invalid or inexistent file!!\nEnding execution!!\n" );
        return 1;
    }

    char * data = (char *) calloc( 9, sizeof(char) ); // string to save the date string

    strcpy( data, argv[1] );

    int * dataOnlyNumbers = (int *) calloc( DATA_SIZE, sizeof(int) ); // int array to guard the digits of the date

    int indexOriginalData; // index to go through the original date
    int indexDataOnlyNumbers; // index to go through the digits array

    for( indexOriginalData = 0, indexDataOnlyNumbers = 0; *(data + indexOriginalData) != '\0'; indexOriginalData++ )
    {
        if( *(data + indexOriginalData) != '/' ) // eliminates the char '/' and saves the value of the digit
        {
            *(dataOnlyNumbers + indexDataOnlyNumbers) = *(data + indexOriginalData) - '0';
            indexDataOnlyNumbers++;
        }
    }
 
    int success = generateCipher( dataOnlyNumbers, inputFile, argv[3] ); // success receive the return of generateCipher to deteminate if had been a successfull cipher
	
	if( success == 0 )
	{
		printf( ">>> Successfull encrypt of the message! <<<\n" );
	} else 
	{
		printf( ">>> Error in encryptation! <<<\n" );
	}

	free( data );
	free( dataOnlyNumbers );
	
	
	fclose( inputFile );
    return 0;
}
