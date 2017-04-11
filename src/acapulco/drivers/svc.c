
ROM_START( svc__OFF )
	ROM_REGION( 0x600000, REGION_CPU1, 0 )
	ROM_LOAD16_WORD_SWAP( "269-p1.bin", 0x000000, 0x600000, CRC(882a1791) )

	NEO_SFIX_128K( "269-s1.bin", CRC(aaef740c) )

	NEO_BIOS_SOUND_128K( "269-m1.bin", CRC(7F01DAC5) )

	ROM_REGION( 0x1000000, REGION_SOUND1, ROMREGION_SOUNDONLY )
	ROM_LOAD( "269-v1.bin", 0x000000, 0x400000, CRC(e7203930) )
	ROM_LOAD( "269-v2.bin", 0x400000, 0x400000, CRC(675159c3) )
	ROM_LOAD( "269-v3.bin", 0x800000, 0x400000, CRC(f8810665) )
	ROM_LOAD( "269-v4.bin", 0xc00000, 0x400000, CRC(b57b4ea3) )

	NO_DELTAT_REGION

	ROM_REGION( 0x4000000, REGION_GFX3, 0 )
	ROM_LOAD16_BYTE( "269-c1.bin", 0x0000000, 0x800000, CRC(465d473b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c2.bin", 0x0000001, 0x800000, CRC(3eb28f78) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c3.bin", 0x1000000, 0x800000, CRC(f4d4ab2b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c4.bin", 0x1000001, 0x800000, CRC(a69d523a) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c5.bin", 0x2000000, 0x800000, CRC(ba2a7892) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c6.bin", 0x2000001, 0x800000, CRC(37371ca1) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c7.bin", 0x3000000, 0x800000, CRC(56ac5fb9) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c8.bin", 0x3000001, 0x800000, CRC(de99e613) ) /* Plane 2,3 */
ROM_END

ROM_START( svcs )
	ROM_REGION( 0x600000, REGION_CPU1, 0 )
	ROM_LOAD16_WORD_SWAP( "svc_p1.rom", 0x000000, 0x600000, CRC(432cfdfc) )

	NEO_SFIX_128K( "269-s1.bin", CRC(8ded55a5) SHA1(27c8ffac16fbcc19c843d1b5b47ae8d8ef83d44a) )

	NEO_BIOS_SOUND_128K( "svc_m1.rom", CRC(fd4f0ff9) )

	ROM_REGION( 0x1000000, REGION_SOUND1, ROMREGION_SOUNDONLY )
	ROM_LOAD( "269-v1.bin", 0x000000, 0x400000, CRC(c659b34c) )
	ROM_LOAD( "269-v2.bin", 0x400000, 0x400000, CRC(dd903835) )
	ROM_LOAD( "269-v3.bin", 0x800000, 0x400000, CRC(a81da99a) )
	ROM_LOAD( "269-v4.bin", 0xc00000, 0x400000, CRC(a8dd6446) )

	NO_DELTAT_REGION

	ROM_REGION( 0x4000000, REGION_GFX3, 0 )
	ROM_LOAD16_BYTE( "269-c1.bin", 0x0000000, 0x800000, CRC(465d473b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c2.bin", 0x0000001, 0x800000, CRC(3eb28f78) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c3.bin", 0x1000000, 0x800000, CRC(f4d4ab2b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c4.bin", 0x1000001, 0x800000, CRC(a69d523a) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c5.bin", 0x2000000, 0x800000, CRC(ba2a7892) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c6.bin", 0x2000001, 0x800000, CRC(37371ca1) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c7.bin", 0x3000000, 0x800000, CRC(56ac5fb9) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c8.bin", 0x3000001, 0x800000, CRC(de99e613) ) /* Plane 2,3 */
ROM_END

ROM_START( svcss )
	ROM_REGION( 0x600000, REGION_CPU1, 0 )
	ROM_LOAD16_WORD_SWAP( "svc_p1.rom", 0x000000, 0x600000, CRC(432cfdfc) )

	NEO_SFIX_128K( "269-s1.bin", CRC(8ded55a5) SHA1(27c8ffac16fbcc19c843d1b5b47ae8d8ef83d44a) )

	NEO_BIOS_SOUND_128K( "svc_m1.rom", CRC(fd4f0ff9) )

	ROM_REGION( 0x1000000, REGION_SOUND1, ROMREGION_SOUNDONLY )
	ROM_LOAD( "269-v1.bin", 0x000000, 0x400000, CRC(c659b34c) )
	ROM_LOAD( "269-v2.bin", 0x400000, 0x400000, CRC(dd903835) )
	ROM_LOAD( "269-v3.bin", 0x800000, 0x400000, CRC(a81da99a) )
	ROM_LOAD( "269-v4.bin", 0xc00000, 0x400000, CRC(a8dd6446) )

	NO_DELTAT_REGION

	ROM_REGION( 0x4000000, REGION_GFX3, 0 )
	ROM_LOAD16_BYTE( "269-c1.bin", 0x0000000, 0x800000, CRC(465d473b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c2.bin", 0x0000001, 0x800000, CRC(3eb28f78) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c3.bin", 0x1000000, 0x800000, CRC(f4d4ab2b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c4.bin", 0x1000001, 0x800000, CRC(a69d523a) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c5.bin", 0x2000000, 0x800000, CRC(ba2a7892) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c6.bin", 0x2000001, 0x800000, CRC(37371ca1) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c7.bin", 0x3000000, 0x800000, CRC(56ac5fb9) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c8.bin", 0x3000001, 0x800000, CRC(de99e613) ) /* Plane 2,3 */
ROM_END

ROM_START( svcem )
	ROM_REGION( 0x600000, REGION_CPU1, 0 )
	ROM_LOAD16_WORD_SWAP( "269-p1.bin", 0x000000, 0x600000, CRC(432cfdfc) )

	NEO_SFIX_128K( "269-s1.bin", CRC(8ded55a5) SHA1(27c8ffac16fbcc19c843d1b5b47ae8d8ef83d44a) )

	NEO_BIOS_SOUND_128K( "269-m1.bin", CRC(fd4f0ff9) )

	ROM_REGION( 0x1000000, REGION_SOUND1, ROMREGION_SOUNDONLY )
	ROM_LOAD( "269-v1.bin", 0x000000, 0x400000, CRC(c659b34c) )
	ROM_LOAD( "269-v2.bin", 0x400000, 0x400000, CRC(dd903835) )
	ROM_LOAD( "269-v3.bin", 0x800000, 0x400000, CRC(a81da99a) )
	ROM_LOAD( "269-v4.bin", 0xc00000, 0x400000, CRC(a8dd6446) )

	NO_DELTAT_REGION

	ROM_REGION( 0x4000000, REGION_GFX3, 0 )
	ROM_LOAD16_BYTE( "269-c1.bin", 0x0000000, 0x800000, CRC(465d473b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c2.bin", 0x0000001, 0x800000, CRC(3eb28f78) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c3.bin", 0x1000000, 0x800000, CRC(f4d4ab2b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c4.bin", 0x1000001, 0x800000, CRC(a69d523a) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c5.bin", 0x2000000, 0x800000, CRC(ba2a7892) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c6.bin", 0x2000001, 0x800000, CRC(37371ca1) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c7.bin", 0x3000000, 0x800000, CRC(56ac5fb9) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c8.bin", 0x3000001, 0x800000, CRC(de99e613) ) /* Plane 2,3 */
ROM_END

ROM_START( svcb )
	ROM_REGION( 0x600000, REGION_CPU1, 0 )
	ROM_LOAD16_WORD_SWAP( "269d-p1.bin", 0x000000, 0x600000, CRC(432cfdfc) )

	NEO_SFIX_128K( "269-s1.bin", CRC(8ded55a5) SHA1(27c8ffac16fbcc19c843d1b5b47ae8d8ef83d44a) )

	NEO_BIOS_SOUND_128K( "269-m1.bin", CRC(fd4f0ff9) )

	ROM_REGION( 0x1000000, REGION_SOUND1, ROMREGION_SOUNDONLY )
	ROM_LOAD( "269-v1.bin", 0x000000, 0x400000, CRC(c659b34c) )
	ROM_LOAD( "269-v2.bin", 0x400000, 0x400000, CRC(dd903835) )
	ROM_LOAD( "269-v3.bin", 0x800000, 0x400000, CRC(a81da99a) )
	ROM_LOAD( "269-v4.bin", 0xc00000, 0x400000, CRC(a8dd6446) )

	NO_DELTAT_REGION

	ROM_REGION( 0x4000000, REGION_GFX3, 0 )
	ROM_LOAD16_BYTE( "269-c1.bin", 0x0000000, 0x800000, CRC(465d473b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c2.bin", 0x0000001, 0x800000, CRC(3eb28f78) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c3.bin", 0x1000000, 0x800000, CRC(f4d4ab2b) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c4.bin", 0x1000001, 0x800000, CRC(a69d523a) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c5.bin", 0x2000000, 0x800000, CRC(ba2a7892) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c6.bin", 0x2000001, 0x800000, CRC(37371ca1) ) /* Plane 2,3 */
	ROM_LOAD16_BYTE( "269-c7.bin", 0x3000000, 0x800000, CRC(56ac5fb9) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "269-c8.bin", 0x3000001, 0x800000, CRC(de99e613) ) /* Plane 2,3 */
ROM_END

