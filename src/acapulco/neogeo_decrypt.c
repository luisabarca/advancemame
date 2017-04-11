/*
void neogeo_bootleg_cx_decrypt( void )
{
	int i;
	int cx_size = memory_region_length( REGION_GFX3 );
	UINT8 *rom = memory_region( REGION_GFX3 );
	UINT8 *buf = malloc( cx_size );

	memcpy( buf, rom, cx_size );

	for( i = 0; i < cx_size / 0x40; i++ ){
		memcpy( &rom[ i * 0x40 ], &buf[ (i ^ 1) * 0x40 ], 0x40 );
	}

	free( buf );
}
*/

/*
void neogeo_bootleg_sx_decrypt( int value )
{
	int sx_size = memory_region_length( REGION_GFX1 );
	UINT8 *rom = memory_region( REGION_GFX1 );
	int i;

	if (value == 1)
	{
		UINT8 *buf = malloc( sx_size );
		memcpy( buf, rom, sx_size );

		for( i = 0; i < sx_size; i += 0x10 )
		{
			memcpy( &rom[ i ], &buf[ i + 8 ], 8 );
			memcpy( &rom[ i + 8 ], &buf[ i ], 8 );
		}
		free( buf );
	}
	else if (value == 2)
	{
		for( i = 0; i < sx_size; i++ )
			rom[ i ] = BITSWAP8( rom[ i ], 7, 6, 0, 4, 3, 2, 1, 5 );
	}
}
*/

/* The King of Gladiator (The King of Fighters '97 bootleg) */
/*
void kog_px_decrypt( void )
{
	// the protection chip does some *very* strange things to the rom
	UINT8 *src = memory_region( REGION_CPU1 );
	UINT8 *dst = malloc(0x600000);
	UINT16 *rom = (UINT16*)memory_region( REGION_CPU1 );
	int i;
	static const int sec[] = { 0x3, 0x8, 0x7, 0xC, 0x1, 0xA, 0x6, 0xD };

	for (i = 0; i < 8; i++){
		memcpy (dst + i * 0x20000, src + sec[i] * 0x20000, 0x20000);
	}

	memcpy (dst + 0x0007A6, src + 0x0407A6, 0x000006);
	memcpy (dst + 0x0007C6, src + 0x0407C6, 0x000006);
	memcpy (dst + 0x0007E6, src + 0x0407E6, 0x000006);
	memcpy (dst + 0x090000, src + 0x040000, 0x004000);
	memcpy (dst + 0x100000, src + 0x200000, 0x400000);
	memcpy (src, dst, 0x600000);
	free (dst);

	for (i = 0x90000/2; i < 0x94000/2; i++){
		if (((rom[i]&0xFFBF) == 0x4EB9 || rom[i] == 0x43F9) && !rom[i + 1])
			rom[i + 1] = 0x0009;

		if (rom[i] == 0x4EB8)
			rom[i] = 0x6100;
	}

	rom[0x007A8/2] = 0x0009;
	rom[0x007C8/2] = 0x0009;
	rom[0x007E8/2] = 0x0009;
	rom[0x93408/2] = 0xF168;
	rom[0x9340C/2] = 0xFB7A;
	rom[0x924AC/2] = 0x0009;
	rom[0x9251C/2] = 0x0009;
	rom[0x93966/2] = 0xFFDA;
	rom[0x93974/2] = 0xFFCC;
	rom[0x93982/2] = 0xFFBE;
	rom[0x93990/2] = 0xFFB0;
	rom[0x9399E/2] = 0xFFA2;
	rom[0x939AC/2] = 0xFF94;
	rom[0x939BA/2] = 0xFF86;
	rom[0x939C8/2] = 0xFF78;
	rom[0x939D4/2] = 0xFA5C;
	rom[0x939E0/2] = 0xFA50;
	rom[0x939EC/2] = 0xFA44;
	rom[0x939F8/2] = 0xFA38;
	rom[0x93A04/2] = 0xFA2C;
	rom[0x93A10/2] = 0xFA20;
	rom[0x93A1C/2] = 0xFA14;
	rom[0x93A28/2] = 0xFA08;
	rom[0x93A34/2] = 0xF9FC;
	rom[0x93A40/2] = 0xF9F0;
	rom[0x93A4C/2] = 0xFD14;
	rom[0x93A58/2] = 0xFD08;
	rom[0x93A66/2] = 0xF9CA;
	rom[0x93A72/2] = 0xF9BE;

}
*/
