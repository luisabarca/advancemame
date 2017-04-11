
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <md5.h>

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


char *getascii( unsigned short in_data [], 
				unsigned short off_start, 
				unsigned short off_end
				);

void HDD_get_data( char chSerial[8] );

void CreateSignature( char *lpBuffer, 
					  const char *chSerial);

void MD5( unsigned char *lpBuffer, 
		  const char *chText);

void MD5_to_str( unsigned char *lpBuffer, 
				 const unsigned char *MD5_digest);

int ReadHDDSerial( );




