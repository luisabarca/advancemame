

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "md5.h"

#define HDD_MASTER		0xA0
#define HDD_SLAVE		0xB0
#define HDD_GETINFO		0xEC
#define HDD_SERVICE		0x48
#define HDD_ERROR		0x01
#define HDD_TIMEOUT		0x01
#define HDD_WAIT		100000

#define IDE_1			0x1F0
#define IDE_2			0x1E8

#define CHD_MD5_BYTES	16
#define MD5_LEN			( (CHD_MD5_BYTES * 2) +1 )


/* Luis was here */
char *getascii ( unsigned short in_data [], 
				 unsigned short off_start, 
				 unsigned short off_end)
{
	static char ret_val [255];
	int loop, loop1;

	for (loop = off_start, loop1 = 0; loop <= off_end; loop++)
	{
		ret_val [loop1++] = (char) (in_data [loop] / 256);  /* Get High byte */
		ret_val [loop1++] = (char) (in_data [loop] % 256);  /* Get Low byte */
	}

	ret_val [loop1] = '\0';  /* Make sure it ends in a NULL character */

	return (ret_val);
}


void HDD_get_data( char chSerial[8] )
{
	unsigned short dd [256];   /* DiskData */
	unsigned short dd_off;     /* DiskData offset */
	unsigned short drive;      /* Loop variable */
	unsigned long  wait_loop;  /* Timeout loop */
	unsigned short base = 0;   /* Base address of drive controller */
	unsigned short in_val;

	for( drive = 0; drive < 4; drive++ )  /* Loop through drives */
	{		
		/* Get IDE Drive info */
		switch (drive / 2)
		{
		/* IDE 1 */
		case 0:
			base = IDE_1; 
			break; 

		/* IDE 2 */
		case 1: 
			base = IDE_2; 
			break;
		}
		

		/* Wait for controller not busy */
		wait_loop = HDD_WAIT;

		while( --wait_loop > 0 )
		{
		  in_val = inp( base + 7 );

		  if( ( (in_val & 0x40) == 0x40 ) || 
			  ( (in_val & 0x00) == 0x00 ) )
			  break;
		}

		if( wait_loop < 1 ) continue;

		if( (drive % 2) == 0 )
		{
			continue;
			//outp( base + 6, HDD_MASTER ); /* Get Master drive */
		}else{
			outp( base + 6, HDD_SLAVE ); /* Get Slave drive */
		}

		outp( base + 7, HDD_GETINFO );          /* Get drive info data */

		/* Wait for data ready */
		wait_loop = 100000;

		while( --wait_loop > 0 )
		{
		  in_val = inp (base + 7);

		  if ((in_val & HDD_SERVICE) == HDD_SERVICE) /* drive ready and needs service */
			  break;

		  if( (in_val & HDD_ERROR) == HDD_ERROR ) /* drive error */
			  break;
		}

		if( (wait_loop < 1) || 
			((in_val & HDD_TIMEOUT) == HDD_TIMEOUT) ) /* Timed Out or Error */
		{
			continue;
		}

		for( dd_off = 0; dd_off != 256; dd_off++ ) /* Read "sector" */
		{
			dd[dd_off] = inpw( base );
		}

		/* Copy HDD serial and exit */
		strcpy(chSerial, getascii(dd, 10, 19) );
		break;
	}
}

void CreateSignature( char *lpBuffer, const char *chSerial)
{
	int j;

	memset(lpBuffer, ' ', 16);

	/* Init the new signature based on HDD serial number */
	lpBuffer[0] = 'L';	lpBuffer[1] = 'a';
	lpBuffer[2] = 'A';	lpBuffer[3] = 'G';

	for( j = 0; j < 8; j++ )
	{
		lpBuffer[ 4 + j ] = chSerial[ j ];
	}

	lpBuffer[12] = '1';	lpBuffer[13] = '6';
	lpBuffer[14] = '0';	lpBuffer[15] = '4';
	lpBuffer[16] = '\0';
}

void MD5( unsigned char *lpBuffer, 
		  const char *chText)
{
	struct MD5Context md5;

	/* Get MD5 digest of signature */
	MD5Init(&md5);
    MD5Update(&md5, chText, CHD_MD5_BYTES );
	MD5Final(lpBuffer, &md5);
	/*
	printf( "Serial MD5 = %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
			lpBuffer[0], lpBuffer[1], lpBuffer[2], lpBuffer[3],
			lpBuffer[4], lpBuffer[5], lpBuffer[6], lpBuffer[7],
			lpBuffer[8], lpBuffer[9], lpBuffer[10], lpBuffer[11],
			lpBuffer[12], lpBuffer[13], lpBuffer[14], lpBuffer[15]
			);
	*/
}

void MD5_to_str( unsigned char *lpBuffer, 
				 const unsigned char *MD5_digest)
{
	/* Remplaza el contenido del buffer por la clave */
	snprintf( lpBuffer, 
			  MD5_LEN, 
			  "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
			  MD5_digest[0], MD5_digest[1], MD5_digest[2], MD5_digest[3],
			  MD5_digest[4], MD5_digest[5], MD5_digest[6], MD5_digest[7],
			  MD5_digest[8], MD5_digest[9], MD5_digest[10], MD5_digest[11],
			  MD5_digest[12], MD5_digest[13], MD5_digest[14], MD5_digest[15]
			 );
}

int ReadHDDSerial()
{
	FILE *fp;
	char chSerial[16], g_serial[8];
	unsigned char buffer[32], chFileSerial[32], md5[16];

	system("copy advmame.exe advmame.o");

	getch();

	/* Open advmame and check for serial */
	fp = fopen("advmame.o", "rb+");

	if( !fp )
		return 1;

	fseek( fp, 0x050, SEEK_SET);
	fread(chFileSerial, sizeof(char), 31, fp);

	fclose(fp);

	getch();

	remove("advmame.o");


	/* Get HDD serial number */
	HDD_get_data( g_serial );

	/* Build the new signature */
	CreateSignature((unsigned char *)chSerial, (const char *)g_serial);

	/* build md5 signature */
	MD5( (unsigned char *)md5, (const char *)chSerial);

	/* Convert md5 signature to string */
	MD5_to_str((unsigned char *)buffer, md5);

	printf("%s y %s\n", buffer, chFileSerial);

	/* Compare MD5 signatures */
	if( memcmp(buffer, chFileSerial, 31) == 0 )
	{		
		printf("Son identicos\n");
		return 0;
	}

	printf("No Son identicos\n");
	
	return 1;
}
