#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* read_file_into_buffer (const char* filename, unsigned long* file_length);
void ascii_to_bin(const char* ascii, const char* filename);
void bin_to_ascii(const char* input_file, const char* output_file);

int main(int argc, char** argv) {
	
	if (argc < 3) {
		printf("usage:*.exe [input_file] [output_file]\n");
		return 1;
	}
	
	
	//bin_to_ascii(argv[1], argv[2]);
	
	ascii_to_bin(read_file_into_buffer(argv[1], NULL), argv[2]);
	

}


void bin_to_ascii(const char* input_file, const char* output_file) {
	
	unsigned long file_length[1];
	char *buffer = read_file_into_buffer(input_file, file_length);
	

	/*** CONVERT CHAR* TO HEX ASCII ***/
	
	
	FILE* file;
	file = fopen(output_file, "w");
	
	
	if (!file) {
		fprintf(stderr, "Can not create output file %s\n", output_file);
		return;
	}
	
	
	for (unsigned long i = 0; i < *file_length; i++) {

		char hex[3];
		unsigned char dec = buffer[i];
		sprintf(hex, "%x", dec);
		if (strlen(hex) < 2) {
			hex[1] = hex[0];
			hex[0] = '0';
			hex[2] = '\0';
		}
		fwrite(hex, strlen(hex), 1, file);
		
	}
	
	fclose(file);
	
	free(buffer);
	
}

void ascii_to_bin(const char* ascii, const char* filename) {
	
	FILE* file;
	file = fopen(filename, "wb");
	if (!file) {
		fprintf(stderr, "Can not create file %s\n", filename);
		return;
	}
	
	
	for (unsigned long i = 0; i < strlen(ascii); i += 2) {
		char hex[3];
		unsigned char c;
		hex[0] = ascii[i];
		hex[1] = ascii[i+1];
		hex[2] = '\0';
		
		sscanf(hex, "%x", &c);
		fwrite(&c, sizeof(char), 1, file);
		
	}
	
	fclose(file);
	
}


char* read_file_into_buffer (const char* filename, unsigned long* file_length) {
	
	/*** READ FILE INTO BUFFER ***/
	FILE *file;
	char *buffer;
	unsigned long fileLen;

	//Open file
	file = fopen(filename, "rb");
	if (!file) {
		fprintf(stderr, "Can not open file %s\n", filename);
		return NULL;
	}
	
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	if (file_length != NULL)
		*file_length = fileLen;
	
	fseek(file, 0, SEEK_SET);

	buffer=(char *)malloc(fileLen+1);

	if (!buffer) {
		fprintf(stderr, "Memory error!");
		fclose(file);
		return NULL;
	}

	fread(buffer, fileLen, 1, file);
	fclose(file);
	
	return buffer;
}
