#include <stdio.h>

/* int bitfilling() -> function to write:
    - unsigned char *stream -> Output stream of bits 
    - int bits_left         -> Number of bits left in current byte
    - int position          -> Current Byte position in output stream
    - int value             -> Value to be written
    - int size              -> Size of value in bits
   Returns the byte position
(beware with complements)*/

int bit_stream_write(unsigned char *stream, int *bits_left, int position, int value, int size){
	
    while (*bits_left <= size){
		
        size -= *bits_left;
		
        *bits_left = 8;
		
        stream[position] |= (value >> size);
		
        position++;
	
    }

	if (size){
		
        *bits_left -= size;
		
        stream[position] |= value << *bits_left;

	}

	return position;
}

/* int bit_stream_read() -> function to read:
    - unsigned char *stream -> Input stream of bits 
    - int *bits_left        -> Number of bits left in current byte
    - int *position         -> Current Byte position in input stream
    - int size              -> size of value in bits
   Returns the value*/

int bit_stream_read(unsigned char *stream, int *bits_left, int *position, int size){
    
    int value = 0;
    
    unsigned char mask = 255;

    while (*bits_left <= size){
        
        size -= *bits_left;
        
        value |= (((stream[*position] & (mask >> (8 - *bits_left)))) << size);
        
        *bits_left = 8;
        
        *position = *position + 1;
    
    }

    if (size){
        
        mask >>= (8 - *bits_left);
        
        *bits_left -= size;
        
        value |= (stream[*position] & mask) >> *bits_left;
    
    }

    return value;
}

void printBinary(unsigned char *stream, int nbytes) {
  	for (int i = 0; i < nbytes; i++) {
		for (int b = 0; b < 8; b++){
			if((stream[i] >> (7-b)) & 1)
				printf("1");
			else
				printf("0");
		}
		getchar();
  	}
}

int main(int argc, char const *argv[]){
    unsigned char stream[256] = {0};
    int position = 0, bits_left = 8;

    //Decimal | Binary | Size in bits
    //  30    | 11110  |      5
    //  14    |  1110  |      4
    //  30    |   110  |      3


    position = bit_stream_write(stream, &bits_left, position, 30, 5);
    position = bit_stream_write(stream, &bits_left, position, 14, 4);
    position = bit_stream_write(stream, &bits_left, position,  6, 3);

    position = 0;
    bits_left = 8;

	int value = bit_stream_read(stream, &bits_left, &position, 5);
    printf("-> %d\n", value);

    value = bit_stream_read(stream, &bits_left, &position, 4);
    printf("-> %d\n", value);

    value = bit_stream_read(stream, &bits_left, &position, 3);
    printf("-> %d\n", value);

    return 0;
}
