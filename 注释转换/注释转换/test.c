#define _CRT_SECURE_NO_WARNINGS 0
#include "exchange.h"
#include <io.h>

void openfile(char *input_fname, char* output_fname) {
	FILE* pfread = fopen(input_fname, "r");
	FILE* pfwrite = fopen(output_fname, "w");
	if (pfread == NULL) {
		perror("open file for read");
		exit(EXIT_FAILURE);
	}

	if (pfwrite == NULL) {
		perror("open file for write");
		fclose(pfread);
		exit(EXIT_FAILURE);
	}
	exchange(pfread, pfwrite);
	fclose(pfread);
	fclose(pfwrite);
}

int main() {
	
	long Handle;
	struct _finddata_t FileInfo;
	if ((Handle = _findfirst("d:\\test\\*.c", &FileInfo)) == -1L)
		printf("File not found\n");
	else
	{
		printf("%s\n", FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0) 
		{
			int i = 0;
			char temp[100] = {0}; 
			strcpy(temp, FileInfo.name);
			while (i<100)
			{
				if (temp[i] != '.')
				{
					i++;
					continue;
				}
					temp[i] = '\0';
					break;
			}
			strcat(temp+(i-1), "转换之后的文件.c");
			char *ptemp = temp;
			printf("%s\n", ptemp);
			FILE* pfread = fopen(FileInfo.name, "r");
			FILE* pfwrite = fopen(*ptemp, "a");
			if (pfread == NULL) {
				perror("open file for read");
				exit(EXIT_FAILURE);
			}

			if (pfwrite == NULL) {
				perror("open file for write");
				fclose(pfread);
				exit(EXIT_FAILURE);
			}
			exchange(pfread, pfwrite);
			fclose(pfread);
			fclose(pfwrite);
			
		}
			
		_findclose(Handle);
	}
	
	/*
	FILE* pfread = fopen("input.c", "r");
	FILE* pfwrite = fopen("output.c", "w");
	if (pfread == NULL) {
		perror("open file for read");
		exit(EXIT_FAILURE);
	}

	if (pfwrite == NULL) {
		perror("open file for write");
		fclose(pfread);
		exit(EXIT_FAILURE);
	}
	exchange(pfread, pfwrite);
	fclose(pfread);
	fclose(pfwrite);
	*/
	return 0;
}