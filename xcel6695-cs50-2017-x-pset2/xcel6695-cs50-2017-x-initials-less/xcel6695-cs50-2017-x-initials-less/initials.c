#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4) {
        printf("Usage: ./copy resize-factor infile outfile\n");
        return 1;
    }

    int factor = atoi(argv[1]);

    if (factor < 0 || factor > 100) {
        printf("Resize factor must be between 0 and 100.\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0) 
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int prev_w = bi.biWidth;         
    bi.biWidth = bi.biWidth * factor;
    bi.biHeight = abs(bi.biWidth * factor);
    int curr_w = bi.biWidth;
    int curr_h = bi.biHeight;

    // get padding of infile
    // int padding = (4 - (oldwidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int padding =  (4 - (curr_w * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = curr_h * ((curr_w * sizeof(RGBTRIPLE)) + padding);
    bf.bfSize = bi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int row_size = sizeof(RGBTRIPLE) * prev_w;
    RGBTRIPLE* row = malloc(row_size);

    int flag = 0;
    int ind;
    int val;

    for (int i = 0; i < curr_h; i++) {
        ind = i / factor;

        if (i == 0 || ind > flag) {
            fseek(inptr, (54 + (row_size * ind)), SEEK_SET);
            for (int a = 0; a < prev_w; a++) {
                fread((row + a), sizeof(RGBTRIPLE), 1, inptr);
            }
        }

        for (int a = 0; a < curr_w; a++) {
            
            RGBTRIPLE tmp;   
            val = a / factor;
            tmp = row[val];
            fwrite(&tmp, sizeof(RGBTRIPLE), 1, outptr);
        }

        // add padding if we need it
        if (padding > 0) {
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr); // fputc(char to be written, FILE*)
            }
        }
        flag = ind;    // update old for the next iteration
    }
    free(row);

    // close files
    fclose(inptr);
    fclose(outptr);

    // adios
    return 0;
}