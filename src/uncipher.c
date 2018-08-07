#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 6
#define BUFFER_LIMIT 100000

/**
 * @brief      	Converts the ciphered character to the original. 
 *
 * @param     	coefficient   The coefficient is the number to deduct of original
 * @param      	originalChar  The original character is the ciphered character to be unciphered.
 *
 * @return     	The unciphered character.
 */
char generateCharacter( int coefficient, char originalChar )
{
	char newChar = originalChar - coefficient;
	if( originalChar >= 'a' && originalChar <= 'z' )
	{
		if( newChar < 'a' )
		{
			int diff = 'a' - newChar + 1;
			newChar = 'z' - diff;
		}
	}
	else if( originalChar >= 'A' && originalChar <= 'Z' ) 
	{
		if( newChar < 'A' )
		{
			int diff = 'A' - newChar + 1;
			newChar = 'Z' - diff;
		}
	}
	else 
	{
		newChar = originalChar;
	}

	return newChar;
}

/**
 * @brief 		Generate and saves in a output file the uncipher message.
 * 
 * @param 		dateNumbers array with the digits of input date
 * @param 		inputFile pointer for input file to read the ciphered message
 * @param 		outputFilename string name of the output file on system
 * 
 * @return 		0 in sucess, 1 in otherwise
 */
int uncipher( int* dateNumbers, FILE * inputFile, char * outputFilename )
{
    int letterIndex = 0;
   	FILE * outputFile = fopen( outputFilename, "w" ); // opens a new file to save de coded message
 
    if( outputFile == NULL )
    {
        	printf( "Error in output file creation\n" );
        	return 1;
   	}
	
	char cipheredBuffer[BUFFER_LIMIT]; // array to cipheredBufferize 100 characters of the original file content. The last one char is '\0'.
	char uncipheredcipheredBuffer[BUFFER_LIMIT];  // array to cipheredBufferize 100 characters of the encrypted file content. The last one char is '\0'.
    while( fscanf( inputFile, "%s", cipheredBuffer ) > 0 )
	{
		int i;
		for( i = 0; cipheredBuffer[ i ] != '\0'; i++ )
		{
			if( cipheredBuffer[ i ] != ' ' )
			{
				uncipheredcipheredBuffer[ i ] = generateCharacter( dateNumbers[ letterIndex % DATE_SIZE ], cipheredBuffer[ i ] );
				letterIndex++;
			} else 
			{
				uncipheredcipheredBuffer[ i ] = cipheredBuffer[ i ];
			}
		}
		uncipheredcipheredBuffer[ i ] = '\0';
		fprintf( outputFile, "%s ", uncipheredcipheredBuffer ); 
		
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

    char * date = (char *) calloc( 9, sizeof(char) ); // string to save the date string

    strcpy( date, argv[1] );

    int * dateOnlyNumbers = (int *) calloc( DATE_SIZE, sizeof(int) ); // int array to guard the digits of the date

    int indexOriginalDate; // index to go through the original date
    int indexDateOnlyNumbers; // index to go through the digits array

    for( indexOriginalDate = 0, indexDateOnlyNumbers = 0; *(date + indexOriginalDate) != '\0'; indexOriginalDate++ )
    {
        if( *(date + indexOriginalDate) != '/' ) // eliminates the char '/' and saves the value of the digit
        {
            *(dateOnlyNumbers + indexDateOnlyNumbers) = *(date + indexOriginalDate) - '0';
            indexDateOnlyNumbers++;
        }
    }

    int success = uncipher( dateOnlyNumbers, inputFile, argv[3] ); // success receive the return of uncipher to deteminate if had been a successfull uncipher
	
	if( success == 0 )
	{
		printf( ">>> Successfull uncipher of the message! <<<\n" );
	} else 
	{
		printf( ">>> Error on uncipher! <<<\n" );
	}

	free( date );
	free( dateOnlyNumbers );
	
	
	fclose( inputFile );
    return 0;
}
