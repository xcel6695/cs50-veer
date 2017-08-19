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

    BITMAPFILEHEADER bf_1;
    BITMAPINFOHEADER bi_1;
    bf_1 = bf;
    bi_1 = bi;

    bi_1.biHeight = bi.biHeight * factor;
    bi_1.biWidth = bi.biWidth * factor;

    int old_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding =  (4 - (bi_1.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_1.biSizeImage = (bi_1.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(bi_1.biHeight); 
    bf_1.bfSize = bi_1.biSizeImage + 54;

    fwrite(&bf_1, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi_1, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    int old_h = abs(bi.biHeight);
    int old_w = bi.biWidth;
    
    for (int i = 0; i < old_h; i++)   
    {
        for (int l = 0; l < factor; l++)
        {
            for (int j = 0; j < old_w; j++)
            {
                RGBTRIPLE temp;
                fread(&temp, sizeof(RGBTRIPLE), 1, inptr);
                for (int r = 0; r < factor; r++){
                    fwrite(&temp, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            fseek(inptr, old_padding, SEEK_CUR);
    
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            if (l < factor - 1) 
            {
                long offset = old_w * sizeof(RGBTRIPLE) + old_padding;
                fseek(inptr, -offset, SEEK_CUR);
            }
        }
    }
    
    fclose(inptr);
    fclose(outptr);
    
    return 0;
}