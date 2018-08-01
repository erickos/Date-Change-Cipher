#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 6

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
        return;
    }
	
	char buffer[101]; // array to bufferize 100 characters of the original file content. The last one char is '\0'.
	char encryptedBuffer[101];  // array to bufferize 100 characters of the encrypted file content. The last one char is '\0'.
    while( fgets( buffer, 100, inputFile ) != NULL )
	{
		int i;
		for( i = 0; i < 100; i++ )
		{
			if( buffer[i] != ' ' )
			{
				encryptedBuffer[ i ] = buffer[ i ] + dataNumbers[ letterIndex % DATA_SIZE ];
				letterIndex++;
			} else 
			{
				encryptedBuffer[ i ] = buffer[ i ];
			}
		}
	}

}

/**
 *  \brief 
 *
 *  
 *  \param [in] argc Description for argc
 *  \param [in] argv Description for argv
 *  \return Return description
 *  
 *  \details More details
 */
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

    for( indexOriginalData = 0, indexDataOnlyNumbers = 0; *(data + indexOriginalData) != '\0', indexOriginalData++ )
    {
        if( *(data + indexOriginalData) != '/' )
        {
            *(dataOnlyNumbers + indexDataOnlyNumbers) = *(data + indexOriginalData) - '0';
            indexDataOnlyNumbers++;
        }
    }

    generateCipher( dataOnlyNumbers, argv[3] );
	
	free( data );
	free( dataOnlyNumbers );
	
	
	fclose( inputFile );
    return 0;
}