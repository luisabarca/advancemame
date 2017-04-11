
/* mslug3 */
ROM_START( mslug3 ) 
	ROM_REGION( 0x500000, REGION_CPU1, 0 )
	ROM_LOAD16_WORD_SWAP( "256-ph1.rom",  0x000000, 0x100000, CRC(b07edfd5) SHA1(dcbd9e500bfae98d754e55cdbbbbf9401013f8ee) )
	ROM_LOAD16_WORD_SWAP( "256-ph2.rom",  0x100000, 0x400000, CRC(6097c26b) SHA1(248ec29d21216f29dc6f5f3f0e1ad1601b3501b6) )

	LOAD_MS3_DATA	
ROM_END

ROM_START( ms3eh )	
	LOAD_MS3_HACK("eh-p1.bin")
ROM_END

ROM_START( ms3eh01 )	
	LOAD_MS3_HACK("eh01-p1.bin")
ROM_END

ROM_START( ms3eh02 )	
	LOAD_MS3_HACK("eh02-p1.bin")
ROM_END

ROM_START( ms3eh03 )	
	LOAD_MS3_HACK("eh03-p1.bin")
ROM_END

ROM_START( ms3eh04 )	
	LOAD_MS3_HACK("eh04-p1.bin")
ROM_END

ROM_START( ms3eh05 )	
	LOAD_MS3_HACK("eh05-p1.bin")
ROM_END

ROM_START( ms3eh06 )	
	LOAD_MS3_HACK("eh06-p1.bin")
ROM_END

ROM_START( ms3eh07 )	
	LOAD_MS3_HACK("eh07-p1.bin")
ROM_END

ROM_START( ms3eh08 )	
	LOAD_MS3_HACK("eh08-p1.bin")
ROM_END

ROM_START( ms3eh09 )	
LOAD_MS3_HACK("eh09-p1.bin")
ROM_END

ROM_START( ms3eh10 )
	LOAD_MS3_HACK("eh10-p1.bin")
ROM_END

ROM_START( ms3eh11 )	
	LOAD_MS3_HACK("eh11-p1.bin")
ROM_END

ROM_START( ms3eh12 )	
	LOAD_MS3_HACK("eh12-p1.bin")
ROM_END

ROM_START( ms3eh13 )	
	LOAD_MS3_HACK("eh13-p1.bin")
ROM_END

ROM_START( ms3eh14 )	
	LOAD_MS3_HACK("eh14-p1.bin")
ROM_END

ROM_START( ms3eh15 )	
	LOAD_MS3_HACK("eh15-p1.bin")
ROM_END

ROM_START( ms3eh16 )	
	LOAD_MS3_HACK("eh16-p1.bin")
ROM_END

ROM_START( ms3eh17 )	
	LOAD_MS3_HACK("eh17-p1.bin")
ROM_END

ROM_START( ms3eh18 )	
	LOAD_MS3_HACK("eh18-p1.bin")
ROM_END

ROM_START( ms3eh19 )	
	LOAD_MS3_HACK("eh19-p1.bin")
ROM_END

ROM_START( ms3eh20 )	
	LOAD_MS3_HACK("eh20-p1.bin")
ROM_END

ROM_START( ms3eh21 )	
	LOAD_MS3_HACK("eh21-p1.bin")
ROM_END

/* kof2000 */
ROM_START( kof2000 ) 
	ROM_REGION( 0x900000, REGION_CPU1, 0 )
	ROM_LOAD16_WORD_SWAP( "257-sma.bin", 0x0c0000, 0x040000, CRC(71c6e6bb) SHA1(1bd29ded4c6b29780db8e8b772c452189699ca89) )
	ROM_LOAD16_WORD_SWAP( "257-p1.bin",  0x100000, 0x400000, CRC(60947b4c) SHA1(5faa0a7ac7734d6c8e276589bd12dd574264647d) )
	ROM_LOAD16_WORD_SWAP( "257-p2.bin",  0x500000, 0x400000, CRC(1b7ec415) SHA1(f19fa44e9ee5b5a6eb4a051349d6bc4acc3bbbdb) )

	LOAD_KOF2000_DATA
ROM_END

ROM_START( kof2000e ) 
	LOAD_KOF2000_HACK("257eh-p1.bin", "257n-p2.rom")
ROM_END

ROM_START( kof2000o ) 
	LOAD_KOF2000_HACK("257eho-p1.bin", "257n-p2.rom")
ROM_END

ROM_START( kof2000r ) 
	LOAD_KOF2000_HACK("257ehr-p1.bin", "257n-p2.rom")
ROM_END

ROM_START( kof2000p ) 
	LOAD_KOF2000_HACK("257ehr-p1.bin", "257pjc-p2.bin")
ROM_END

ROM_START( kof2000j ) 
	LOAD_KOF2000_HACK("257bj-p1n.bin", "257n-p2.rom")
ROM_END

ROM_START( kof2000i ) 
	LOAD_KOF2000_HACK("257ehr-p1.bin", "257ice-p2.bin")
ROM_END

ROM_START( kof2000g ) 
	LOAD_KOF2000_HACK("257ehr-p1.bin", "257gold-p2.rom")
ROM_END

ROM_START( kof2000v ) 
	LOAD_KOF2000_HACK("257evo-p1.bin", "257n-p2.rom")
ROM_END

/* kof2002 */
ROM_START( kof2002 )
	LOAD_KOF2002_HACK("kof2k2_p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002b )
	LOAD_KOF2002_HACK("boss.bin", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002c )
	LOAD_KOF2002_HACK("kof2k2_p1.rom", "265cfc-p2.bin", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002e )
	LOAD_KOF2002_HACK("2k2m-p1.bin", "kof2k2_p2.rom", "2k2m-s1.bin")
ROM_END

ROM_START( kof2002f )
	LOAD_KOF2002_HACK("2k2_p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002g )
	LOAD_KOF2002_HACK("2k2_p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002h )
	LOAD_KOF2002_HACK("kof2k2_p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002i )
	LOAD_KOF2002_HACK("kof2k2_p1.rom", "265ice-p2.bin", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002l )
	LOAD_KOF2002_HACK("265ule-p1.bin", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002m )
	LOAD_KOF2002_HACK("kf02m-p1d.bin", "kf02m-p2d.bin", "kf02m-s1d.bin")
ROM_END

ROM_START( kof2002n )
	ROM_REGION( 0x600000, REGION_CPU1, 0 ) 
	ROM_LOAD16_WORD_SWAP( "k2k2m2p1.bin", 0x100000, 0x100000, CRC(61ac868a) SHA1(26577264aa72d6af272952a876fcd3775f53e3fa) ) 		
	ROM_LOAD16_WORD_SWAP( "k2k2m2p2.bin", 0x100000, 0x400000, CRC(980aba4c) SHA1(5e735929ec6c3ca5b2efae3c7de47bcbb8ade2c5) ) 	
	ROM_CONTINUE(						  0x000000, 0x100000 ) 
	
	NEO_SFIX_128K( "k2k2m2s1.bin", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) ) 
	
	LOAD_KOF2002_DATA
ROM_END

ROM_START( kof2002o )
	LOAD_KOF2002_HACK("kof2k2_p1h.rom", "kof2k2_p2.rom", "kof2k2_s1h.rom")
ROM_END

ROM_START( kof2002p )
	LOAD_KOF2002_HACK("kof2k2p_p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002r )
	LOAD_KOF2002_HACK("265ru-p1.bin", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002s )
	LOAD_KOF2002_HACK("kof2k2_p1h.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002x )
	LOAD_KOF2002_HACK("kof2k2_p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof2002z )
	LOAD_KOF2002_HACK("kof2k2p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof20021 )
	LOAD_KOF2002NE_HACK("kof2k2_p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

ROM_START( kof20022 )
	LOAD_KOF2002_HACK("2k2_p1.rom", "kof2k2_p2.rom", "kof2k2_s1.rom")
ROM_END

/*   */
ROM_START( lans2004 )
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


DRIVER_INIT( lans2004 )
{
	lans2004_decrypt_68k(); /* decrypt 68k + apply protection patches */
	lans2004_vx_decrypt();
	neogeo_bootleg_sx_decrypt(1);
	neogeo_bootleg_cx_decrypt();
	init_neogeo();
}

/*   */
static void sx_decrypt( void )
{
        int sx_size = memory_region_length( REGION_GFX1 );
        UINT8 *rom = memory_region( REGION_GFX1 );
        int i;
        
        if ((rom[0] == 0x11) || (rom[0] == 0x22))
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
        else
        if (rom[0] == 0x30)
        {
                for( i = 0; i < sx_size; i++ )
                        rom[ i ] = BITSWAP8( rom[ i ], 7, 6, 0, 4, 3, 2, 1, 5 );
        }
}


static void samsh5bl_cx_decrypt( void )
{
        int cx_size = memory_region_length( REGION_GFX3 );
        UINT8 *rom = memory_region( REGION_GFX3 );
        UINT8 *buf = malloc( cx_size );
        int i;

        memcpy( buf, rom, cx_size );

        for( i = 0; i < cx_size / 0x40; i++ )
                memcpy( &rom[ i * 0x40 ], &buf[ (i ^ 1) * 0x40 ], 0x40 );

        free( buf );
}



