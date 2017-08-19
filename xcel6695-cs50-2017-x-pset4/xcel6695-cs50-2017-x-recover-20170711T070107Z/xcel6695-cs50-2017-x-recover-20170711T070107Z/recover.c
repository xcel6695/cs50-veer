#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE; 

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image");
        return 1;
    }
    
    FILE* inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    
    BYTE buffer[512];
    int count = 0; 
    int started = 0;

    FILE* outptr;

    while(fread(buffer, 512, 1, inptr) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            if (started)
            {
                fclose(outptr); 
            }
            else
            {
                started = 1;
            }
            
            char name[4];
            sprintf(name, "%03d.jpg", count);
            
            outptr = fopen(name, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", name);
                return 3;
            }
            count++;
        }
        if (started)
        {
            fwrite(&buffer, 512, 1, outptr);
        }
    }
    
    fclose(outptr);
    
    fclose(inptr);   
}