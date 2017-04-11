/* LansQuenet  */

ROM_START( lans2004__OFF )
	ROM_REGION( 0x600000, REGION_CPU1, 0 )
	ROM_LOAD16_WORD_SWAP( "lnsq-p1.bin", 0x000000, 0x200000, CRC(b40a879a) )
	ROM_LOAD16_WORD_SWAP( "lnsq-p21.bin", 0x200000, 0x200000, CRC(ecdb2d42) )
	ROM_LOAD16_WORD_SWAP( "lnsq-p22.bin", 0x400000, 0x200000, CRC(fac5e2e7) )

	NEO_SFIX_128K( "lnsq-s1.bin", CRC(39e82897) )

	NEO_BIOS_SOUND_128K( "246-m1.bin", CRC(d0604ad1) )

	ROM_REGION( 0xA00000, REGION_SOUND1, 0 )
	ROM_LOAD( "lnsq-v1.bin", 0x000000, 0x400000, CRC(4408ebc3) )
	ROM_LOAD( "lnsq-v2.bin", 0x400000, 0x400000, CRC(3d953975) )
	ROM_LOAD( "lnsq-v3.bin", 0x800000, 0x200000, CRC(437d1d8e) )

	NO_DELTAT_REGION

	ROM_REGION( 0x3000000, REGION_GFX3, 0 )
	ROM_LOAD16_BYTE( "lnsq-c1.bin", 0x0000000, 0x800000, CRC(b83de59f) )
	ROM_LOAD16_BYTE( "lnsq-c2.bin", 0x0000001, 0x800000, CRC(e08969fd) )
	ROM_LOAD16_BYTE( "lnsq-c3.bin", 0x1000000, 0x800000, CRC(013f2cda) )
	ROM_LOAD16_BYTE( "lnsq-c4.bin", 0x1000001, 0x800000, CRC(d8c3a758) )
	ROM_LOAD16_BYTE( "lnsq-c5.bin", 0x2000000, 0x800000, CRC(75500b82) )
	ROM_LOAD16_BYTE( "lnsq-c6.bin", 0x2000001, 0x800000, CRC(670ac13b) )
ROM_END

/* Lans2004 (bootleg of Shock Troopers 2) */

void lans2004_vx_decrypt( void )
{
	int i;
	UINT8 *rom = memory_region( REGION_SOUND1 );

	for (i = 0; i < 0xA00000; i++){
		rom[i] = BITSWAP8(rom[i], 0, 1, 5, 4, 3, 2, 6, 7);
	}
}

void lans2004_decrypt_68k( void )
{
	/* Descrambling P ROMs - Thanks to Razoola for the info */
	int i;
	UINT8 *src = memory_region( REGION_CPU1 );
	UINT16 *rom = (UINT16*)memory_region( REGION_CPU1 );
	UINT8 *dst = malloc(0x600000);

	if (dst) {
		static const int sec[] = { 0x3, 0x8, 0x7, 0xC, 0x1, 0xA, 0x6, 0xD };

		for (i = 0; i < 8; i++)
			memcpy (dst + i * 0x20000, src + sec[i] * 0x20000, 0x20000);

		memcpy (dst + 0x0BBB00, src + 0x045B00, 0x001710);
		memcpy (dst + 0x02FFF0, src + 0x1A92BE, 0x000010);
		memcpy (dst + 0x100000, src + 0x200000, 0x400000);
		memcpy (src, dst, 0x600000);
		free (dst);
	}

	for (i = 0xBBB00/2; i < 0xBE000/2; i++) {
		if ((((rom[i]&0xFFBF)==0x4EB9) || ((rom[i]&0xFFBF)==0x43B9)) && (rom[i+1]==0x0000)) {
			rom[i + 1] = 0x000B;
			rom[i + 2] += 0x6000;
		}
	}

	rom[0x2D15C/2] = 0x000B;
	rom[0x2D15E/2] = 0xBB00;
	rom[0x2D1E4/2] = 0x6002;
	rom[0x2EA7E/2] = 0x6002;
	rom[0xBBCD0/2] = 0x6002;
	rom[0xBBDF2/2] = 0x6002;
	rom[0xBBE42/2] = 0x6002;
}


DRIVER_INIT( lans2004__OFF )
{
	lans2004_decrypt_68k(); /* decrypt 68k + apply protection patches */
	lans2004_vx_decrypt();
	neogeo_bootleg_sx_decrypt(1);
	neogeo_bootleg_cx_decrypt();
	init_neogeo();
}

