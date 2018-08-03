#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE 6
#define BUFFER_LIMIT 100000

/**
 * @brief      { function_description }
 *
 * @param[in]  coefficient   The coefficient
 * @param[in]  originalChar  The original character
 *
 * @return     { description_of_the_return_value }
 */
char generateCharacter( int coefficient, char originalChar )
{
	char newChar = originalChar + coefficient;
	if( originalChar >= 'a' && originalChar <= 'z' )
	{
		if( newChar > 'z' )
		{
			int diff = newChar - 'z';
			newChar = 'a' + diff;
		}
	}
	else if( originalChar >= 'A' && originalChar <= 'Z' ) 
	{
		if( newChar > 'Z' )
		{
			int diff = newChar - 'Z';
			newChar = 'A' + diff;
		}
	} else 
	{
		newChar = originalChar;
	}

	return newChar;
}

/**
 *  Generate and saves in the output file the encrypted message.
 * @param dataNumbers array with the digits of input date
 * @param inputFile pointer for input file to read the original message
 * @param outputFilename string name of the output file on system
 * 
 * @return 0 in sucess, 1 in otherwise
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
        printf( "Argumentos inválidos!\n" );
        return 1;
    }

    FILE * inputFile =  fopen( argv[2], "r" );

    if( inputFile == NULL )
    {
        printf( "Arquivo não existente ou inválido!!\nEncerrando execução!!\n" );
        return 1;
    }

    char * data = (char *) calloc( 9, sizeof(char) );

    strcpy( data, argv[1] );

    int * dataOnlyNumbers = (int *) calloc( DATA_SIZE, sizeof(int) );

    int indexOriginalData;
    int indexDataOnlyNumbers;

    for( indexOriginalData = 0, indexDataOnlyNumbers = 0; *(data + indexOriginalData) != '\0'; indexOriginalData++ )
    {
        if( *(data + indexOriginalData) != '/' )
        {
            *(dataOnlyNumbers + indexDataOnlyNumbers) = *(data + indexOriginalData) - '0';
            indexDataOnlyNumbers++;
        }
    }

    int success = generateCipher( dataOnlyNumbers, inputFile, argv[3] );
	
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
