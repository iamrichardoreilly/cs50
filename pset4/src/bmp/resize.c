/**
 * File: resize.c
 * --------------
 *
 * Usage: ./resize n infile outfile
 *
 * Resizes 24-bit uncompressed BMPs by a factor of n.
 */


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int main(int argc, char **argv)
{

	// Ensure proper usage.
	if (argc != 4)
	{
		printf("Usage: ./resize n infile outfile\n");

		return 1;
	}

	// Ensure n is valid.
	int c = 0;
	while (argv[1][c] != '\0')
	{
		if (!isdigit(argv[1][c]))
		{
			printf("n must be a positive integer less than or equal to 100\n");

			return 2;
		}

		c++;
	}
	int n = atoi(argv[1]);
	if (!n || n > 100)
	{
		printf("n must be a positive integer less than or equal to 100\n");

		return 2;
	}

	char *infile = argv[2];
	char *outfile = argv[3];

	// Open input file.
	FILE *inptr = fopen(infile, "r");
	if (!inptr)
	{
		printf("Could not open %s.\n", infile);

		return 3;
	}

	// Open output file.
	FILE *outptr = fopen(outfile, "w");
	if (!outptr)
	{
		fclose(inptr);
		fprintf(stderr, "Could not create %s.\n", outfile);

		return 4;
	}

	// Read infile's BITMAPFILEHEADER.
	BITMAPFILEHEADER inbf;
	fread(&inbf, sizeof(BITMAPFILEHEADER), 1, inptr);

	// Read infile's BITMAPINFOHEADER.
	BITMAPINFOHEADER inbi;
	fread(&inbi, sizeof(BITMAPINFOHEADER), 1, inptr);

	// Ensure infile is (likely) a 24-bit uncompressed BMP 4.0.
	if (inbf.bfType != 0x4d42 || inbf.bfOffBits != 54 || inbi.biSize != 40 || 
			inbi.biBitCount != 24 || inbi.biCompression != 0)
	{
		fclose(outptr);
		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");

		return 5;
	}

	// Determine padding for infile's scanlines.
	int inpadding = (4 - (inbi.biWidth*sizeof(RGBTRIPLE))%4)%4;

	// Determine padding for outfile's scanlines.
	int outpadding = (4 - (inbi.biWidth*n*sizeof(RGBTRIPLE))%4)%4;

	// Update outfile's BITMAPINFOHEADER.
	BITMAPINFOHEADER outbi = inbi;
	outbi.biWidth*=n;
	outbi.biHeight*=n;
	outbi.biSizeImage = outbi.biWidth*abs(outbi.biHeight)*sizeof(RGBTRIPLE) + abs(outbi.biHeight)*outpadding;

	// Update outfile's BITMAPFILEHEADER.
	BITMAPFILEHEADER outbf = inbf;
	outbf.bfSize = outbi.biSizeImage + sizeof(outbf) + sizeof(outbi);

	// Write outfile's BITMAPFILEHEADER.
	fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

	// Write outfile's BITMAPINFOHEADER.
	fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

	// Iterate over infile's scanlines.
	for (int scanline = 0; scanline < abs(inbi.biHeight); scanline++)
	{

		// Do work for scanline n times.
		for (int i = 0; i < n; i++)
		{

			// Iterate over pixels in scanline.
			for (int pixel = 0; pixel < inbi.biWidth; pixel++)
			{

				// Read RGB triple from infile.
				RGBTRIPLE triple;
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

				// Write RGB triple to outfile n times.
				for (int j = 0; j < n; j++)
				{
					fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
				}
			}

			// Rewind outfile's file position indicator to the beginning of 
			// scanline if doing work again.
			if (i < n - 1)
			{
				fseek(inptr, -(inbi.biWidth*(int)sizeof(RGBTRIPLE)), SEEK_CUR);
			}

			// Write padding to outfile's scanline.
			for (int k = 0; k < outpadding; k++)
			{
				fputc(0x00, outptr);
			}
		}

		// Skip over infile's scanline padding.
		fseek(inptr, inpadding, SEEK_CUR);
	}

	// Close infile.
	fclose(inptr);

	// Close outfile.
	fclose(outptr);

	return 0;
}
