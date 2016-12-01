/**
 * File: recover.c
 * ---------------
 *
 * Recovers deleted JPEGs.
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// CompactFlash card from which to recover JPEGs from.
static const char *kCF_CARD_FILE = "card.raw";

// JPEGs are stored contiguously on CF cards with a FAT file system, whose 
// block size is 512 bytes.
static const size_t kBUFSIZE = 512;

// E.g. 001.jpeg + '\0'.
static const size_t kFNAME_LEN = 9;

// JPEGS have signature patterns of bytes that distinguish them from other 
// file formats.
static const unsigned char kJPEG_BYTE_0 = 0xFF;
static const unsigned char kJPEG_BYTE_1 = 0xD8;
static const unsigned char kJPEG_BYTE_2 = 0xFF;
static const unsigned char kJPEG_BYTE_3_MIN = 0xE0;
static const unsigned char kJPEG_BYTE_3_MAX = 0xEF;


int main(void)
{

	// Open card file.
	FILE *inptr = fopen(kCF_CARD_FILE, "r");
	if (!inptr)
	{
		printf("Could not open %s.\n", kCF_CARD_FILE);

		return 1;
	}

	unsigned char buf[kBUFSIZE];
	bool recovering_jpeg = false;
	FILE *jpegptr;
	char *fname = (char *)malloc(kFNAME_LEN*sizeof(char));
	int i = 0;

	// Read card file until EOF.
	while (fread(&buf, sizeof(unsigned char), kBUFSIZE, inptr))
	{

		// If we've found a new JPEG.
		if (buf[0] == kJPEG_BYTE_0 && buf[1] == kJPEG_BYTE_1 && buf[2] == kJPEG_BYTE_2 && 
			(buf[3] >= kJPEG_BYTE_3_MIN && buf[3] <= kJPEG_BYTE_3_MAX))
		{
			recovering_jpeg = true;

			// Close previous JPEG.
			if (jpegptr)
			{
				fclose(jpegptr);
			}

			// Update new JPEG filename.
			sprintf(fname, "%03i.jpeg", i);

			// Create and open new JPEG file.
			jpegptr = fopen(fname, "w");
			if (!jpegptr)
			{
				fclose(jpegptr);
				fprintf(stderr, "Could not create %s.\n", fname);

				return 2;
			}

			i++;
		}

		if (recovering_jpeg)
		{
			fwrite(&buf, kBUFSIZE, 1, jpegptr);
		}
	}

	// Close card file.
	fclose(inptr);

	// Close last recovered JPEG file.
	if (jpegptr)
	{
		fclose(jpegptr);
	}

	// Free memory.
	free(fname);

	return 0;
}
