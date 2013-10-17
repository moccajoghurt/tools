#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void ascii_to_bin(const char* ascii, const char* filename);
void bin_to_ascii(const char* input_file, const char* output_file);

int main(int argc, char** argv) {
    
    bin_to_ascii(argv[1], argv[1]);
    
    
}


void bin_to_ascii(const char* input_file, const char* output_file) {
    
    /***   READ FILE INTO BUFFER ***/
    FILE *file;
    char *buffer;
    unsigned long fileLen;

    //Open file
    file = fopen(input_file, "rb");
    if (!file) {
        fprintf(stderr, "Can not open file %s", input_file);
        return;
    }
    
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);
    
    buffer=(char *)malloc(fileLen+1);
    
    if (!buffer) {
        fprintf(stderr, "Memory error!");
        fclose(file);
        return;
    }
    
    fread(buffer, fileLen, 1, file);
    fclose(file);
    
    
    /*** CONVERT CHAR* TO HEX ASCII ***/
    
    for (unsigned long i = 0; i < fileLen; i++) {
        
        char hex[3];
        unsigned char dec = buffer[i];
        sprintf(hex, "%x", dec);
        if (strlen(hex) < 2) {
            hex[1] = hex[0];
            hex[0] = '0';
            hex[2] = '\0';
        }
        printf("%s   strlen: %d\n", hex, strlen(hex));
    }
    
    
    //Do what ever with buffer
    free(buffer);
}



void ascii_to_bin(const char* ascii, const char* filename) {
    
    
    
}
