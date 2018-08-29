#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile \n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return 2;
    }

    char outfile[8];
    FILE *outptr;
    unsigned char *buffer = (unsigned char *)malloc(512);
    int counter = 0;
    // loop through all bytes in infile
    while(fread(buffer, 1, 512, inptr) == 512)
    {
        // find the beginning of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if the file is not the first file
            // close previous file before opening a new file
            if (counter != 0)
            {
                fclose(outptr);
            }
            sprintf(outfile, "%03d.jpg", counter);
            outptr = fopen(outfile,"w");
            counter++;
        }

        // write only when output file is defined
        if (outptr != NULL)
        {
            fwrite(buffer, 1, 512, outptr);
        }
    }
    fclose(outptr);
    free(buffer);
}