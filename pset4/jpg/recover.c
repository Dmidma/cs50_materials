/**
 * recover.c
 *
 * Oussema Hidri
 * d.oussema.d@gmail.com
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t  BYTE;

int main(void)
{

	// open the .raw file
	FILE* file = fopen("card.raw", "r");
	if (file == NULL)
	{
		printf("Could not open card.raw\n");
		return 1;
	}

	// create buffer
	BYTE* buffer = malloc(sizeof(BYTE) * 512);

	// file's title
	char* title = malloc(sizeof(char) * 9);

	// file's counter
	int fiCount = 0;

	// JPEG images
	FILE* img;

	// encounter a serie of images
	int serie = 0;

	// go through the raw file
	while(fread(buffer, 1, 512, file) != 0)
	{
		// check if the buffer have encoutred a JPEG signature
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && 
			(buffer[3] == 0xe0 || buffer[3] == 0xe1) && serie == 0)
		{	
			// encountered a serie of JPEG images
			serie = 1;

			// title-format-conversion 
			snprintf(title, 9, "%.3d.jpg", fiCount);

			// open and write on a new JPEG file
			img = fopen(title, "a");
			if (img == NULL)
			{
				fclose(file);
				printf("Could not create %s\n", title);
			}
			fwrite(buffer, 512, 1, img);
		}
		else if (buffer[0] == 0xff && buffer[1] == 0xd8 && 
			buffer[2] == 0xff && 
			(buffer[3] == 0xe0 || buffer[3] == 0xe1) && serie == 1)
		{
			// close the previous JPEG file
			fclose(img);

			// increment the number of images
			fiCount++;

			// title-format-conversion 
			snprintf(title, 9, "%.3d.jpg", fiCount);

			// open and write on a new JPEG file
			img = fopen(title, "a");
			if (img == NULL)
			{
				fclose(file);
				printf("Could not create %s\n", title);
			}
			fwrite(buffer, 512, 1, img);
		}
		else if (serie == 1)
		{	
			// write on an opened file
			fwrite(buffer, 512, 1, img);
		}
	}

	// close any remaining file
	fclose(img);
	fclose(file);
	
	// free allocated memories
	free(buffer);
	free(title);

	return 0;
}
