/**
 * resize.c
 *
 * Oussema Hidri
 * d.oussema.d@gmail.com
 *
 * This program takes a BMP file and makes it bigger.
 * It resizes an inputfile n-time, that the user must 
 * provide in command-line.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember factor
    int factor = atoi(argv[1]);
    if (factor <= 0 || factor > 100)
    {
        return 0;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bfIn;
    fread(&bfIn, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER biIn;
    fread(&biIn, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bfIn.bfType != 0x4d42 || bfIn.bfOffBits != 54 || biIn.biSize != 40 || 
        biIn.biBitCount != 24 || biIn.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create outfile's headers
    BITMAPFILEHEADER bfOut = bfIn;
    BITMAPINFOHEADER biOut = biIn;


    // change outfile's width and height
    biOut.biWidth *= factor;
    biOut.biHeight *= factor;

    // determine paddings for scanlines
    int inPadding =  (4 - (biIn.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding =  (4 - (biOut.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // change image's size
    biOut.biSizeImage = (abs(biOut.biWidth) * abs(biOut.biHeight) * 
        (biOut.biBitCount) / 8);
    
    // add size of paddings, if any
    biOut.biSizeImage += outPadding * (abs(biOut.biHeight));
    
    // change file's size
    bfOut.bfSize = 14 + 40 + biOut.biSizeImage;

    

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOut, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biOut, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    // create array of row pixels
    RGBTRIPLE* row = malloc(sizeof(RGBTRIPLE) * biIn.biWidth);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biIn.biHeight); i < biHeight; i++)
    {
        
        // iterate over pixels in scanline
        for (int j = 0; j < biIn.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            row[j] = triple;     
        }

        // skip over padding, if any
        fseek(inptr, inPadding, SEEK_CUR);

        // repeat row n-time
        int factRep = 0;
        while (factRep < factor)
        {
            for (int j = 0; j < biIn.biWidth; j++) 
            {
                // repeat pixel n-time
                for (int k = 0; k < factor; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&row[j], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // then add it back (to demonstrate how)
            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }

            factRep++;
        }
    }


    // free row array
    free(row);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
