/*
 * This file is part of the Advance project.
 *
 * Copyright (C) 2003, 2004 Andrea Mazzoleni
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * In addition, as a special exception, Andrea Mazzoleni
 * gives permission to link the code of this program with
 * the MAME library (or with modified versions of MAME that use the
 * same license as MAME), and distribute linked combinations including
 * the two.  You must obey the GNU General Public License in all
 * respects for all of the code used other than MAME.  If you modify
 * this file, you may extend this exception to your version of the
 * file, but you are not obligated to do so.  If you do not wish to
 * do so, delete this exception statement from your version.
 */

#ifndef __INTERP_H
#define __INTERP_H

/***************************************************************************/
/* Basic types */

typedef unsigned short interp_uint16;
typedef unsigned interp_uint32;

/***************************************************************************/
/* interpolation */

extern unsigned interp_mask[2];
extern unsigned interp_red_mask, interp_green_mask, interp_blue_mask;
extern int interp_red_shift, interp_green_shift, interp_blue_shift;
extern unsigned interp_near_mask;
extern unsigned interp_highnot_mask;

/**
 * Select which method to use for computing pixels.
 */
/* #define USE_INTERP_MASK_1 */
/* #define USE_INTERP_MASK_2 */
#define USE_INTERP_MASK_3

#define INTERP_16_MASK_1(v) ((v) & interp_mask[0])
#define INTERP_16_MASK_2(v) ((v) & interp_mask[1])
#define INTERP_16_UNMASK_1(v) ((v) & interp_mask[0])
#define INTERP_16_UNMASK_2(v) ((v) & interp_mask[1])
#define INTERP_16_HNMASK interp_highnot_mask

#define INTERP_16_GEN2(a,b) \
static inline interp_uint16 interp_16_##a##b(interp_uint16 p1, interp_uint16 p2) \
{ \
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*a + INTERP_16_MASK_1(p2)*b) / 16) \
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*a + INTERP_16_MASK_2(p2)*b) / 16); \
}

#define INTERP_16_GEN3(a,b,c) \
static inline interp_uint16 interp_16_##a##b##c(interp_uint16 p1, interp_uint16 p2, interp_uint16 p3) \
{ \
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*a + INTERP_16_MASK_1(p2)*b + INTERP_16_MASK_1(p3)*c) / 16) \
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*a + INTERP_16_MASK_2(p2)*b + INTERP_16_MASK_2(p3)*c) / 16); \
}

#define INTERP_32_MASK_1(v) ((v) & 0xFF00FFU)
#define INTERP_32_MASK_2(v) ((v) & 0x00FF00U)
#define INTERP_32_UNMASK_1(v) ((v) & 0xFF00FFU)
#define INTERP_32_UNMASK_2(v) ((v) & 0x00FF00U)
#define INTERP_32_HNMASK (~0x808080U)

#define INTERP_32_GEN2(a,b) \
static inline interp_uint32 interp_32_##a##b(interp_uint32 p1, interp_uint32 p2) \
{ \
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*a + INTERP_32_MASK_1(p2)*b) / 16) \
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*a + INTERP_32_MASK_2(p2)*b) / 16); \
}

#define INTERP_32_GEN3(a,b,c) \
static inline interp_uint32 interp_32_##a##b##c(interp_uint32 p1, interp_uint32 p2, interp_uint32 p3) \
{ \
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*a + INTERP_32_MASK_1(p2)*b + INTERP_32_MASK_1(p3)*c) / 16) \
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*a + INTERP_32_MASK_2(p2)*b + INTERP_32_MASK_2(p3)*c) / 16); \
}

static inline interp_uint16 interp_16_11(interp_uint16 p1, interp_uint16 p2)
{
#ifdef USE_INTERP_MASK_1
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1) + INTERP_16_MASK_1(p2)) / 2)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1) + INTERP_16_MASK_2(p2)) / 2);
#else
	/*
	 * This function compute (a + b) / 2 for any rgb nibble, using the
	 * the formula (a + b) / 2 = ((a ^ b) >> 1) + (a & b).
	 * To extend this formula to a serie of packed nibbles the formula is
	 * implemented as (((v0 ^ v1) >> 1) & MASK) + (v0 & v1) where MASK
	 * is used to clear the high bit of all the packed nibbles.
	 */
	return (((p1 ^ p2) >> 1) & INTERP_16_HNMASK) + (p1 & p2);
#endif
}

static inline interp_uint16 interp_16_211(interp_uint16 p1, interp_uint16 p2, interp_uint16 p3)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*2 + INTERP_16_MASK_1(p2) + INTERP_16_MASK_1(p3)) / 4)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*2 + INTERP_16_MASK_2(p2) + INTERP_16_MASK_2(p3)) / 4);
#else
	return interp_16_11(p1, interp_16_11(p2, p3));
#endif
}

static inline interp_uint16 interp_16_31(interp_uint16 p1, interp_uint16 p2)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*3 + INTERP_16_MASK_1(p2)) / 4)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*3 + INTERP_16_MASK_2(p2)) / 4);
#else
	return interp_16_11(p1, interp_16_11(p1, p2));
#endif
}

static inline interp_uint16 interp_16_521(interp_uint16 p1, interp_uint16 p2, interp_uint16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*5 + INTERP_16_MASK_1(p2)*2 + INTERP_16_MASK_1(p3)) / 8)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*5 + INTERP_16_MASK_2(p2)*2 + INTERP_16_MASK_2(p3)) / 8);
#else
	return interp_16_11(p1, interp_16_11(p2, interp_16_11(p1, p3)));
#endif
}

static inline interp_uint16 interp_16_431(interp_uint16 p1, interp_uint16 p2, interp_uint16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*4 + INTERP_16_MASK_1(p2)*3 + INTERP_16_MASK_1(p3)) / 8)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*4 + INTERP_16_MASK_2(p2)*3 + INTERP_16_MASK_2(p3)) / 8);
#else
	return interp_16_11(p1, interp_16_11(p2, interp_16_11(p2, p3)));
#endif
}

static inline interp_uint16 interp_16_53(interp_uint16 p1, interp_uint16 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*5 + INTERP_16_MASK_1(p2)*3) / 8)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*5 + INTERP_16_MASK_2(p2)*3) / 8);
#else
	return interp_16_11(p1, interp_16_11(p2, interp_16_11(p1, p2)));
#endif
}

static inline interp_uint16 interp_16_332(interp_uint16 p1, interp_uint16 p2, interp_uint16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*3 + INTERP_16_MASK_1(p2)*3 + INTERP_16_MASK_1(p3)*2) / 8)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*3 + INTERP_16_MASK_2(p2)*3 + INTERP_16_MASK_2(p3)*2) / 8);
#else
	interp_uint16 t = interp_16_11(p1, p2);
	return interp_16_11(t, interp_16_11(p3, t));
#endif
}

static inline interp_uint16 interp_16_611(interp_uint16 p1, interp_uint16 p2, interp_uint16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*6 + INTERP_16_MASK_1(p2) + INTERP_16_MASK_1(p3)) / 8)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*6 + INTERP_16_MASK_2(p2) + INTERP_16_MASK_2(p3)) / 8);
#else
	return interp_16_11(p1, interp_16_11(p1, interp_16_11(p2, p3)));
#endif
}

static inline interp_uint16 interp_16_71(interp_uint16 p1, interp_uint16 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_UNMASK_1((INTERP_16_MASK_1(p1)*7 + INTERP_16_MASK_1(p2)) / 8)
		| INTERP_16_UNMASK_2((INTERP_16_MASK_2(p1)*7 + INTERP_16_MASK_2(p2)) / 8);
#else
	return interp_16_11(p1, interp_16_11(p1, interp_16_11(p1, p2)));
#endif
}

INTERP_16_GEN3(6,5,5)
INTERP_16_GEN3(7,5,4)
INTERP_16_GEN3(7,6,3)
INTERP_16_GEN3(7,7,2)
INTERP_16_GEN3(8,5,3)
INTERP_16_GEN3(9,4,3)
INTERP_16_GEN3(9,6,1)
INTERP_16_GEN3(10,3,3)
INTERP_16_GEN3(10,5,1)
INTERP_16_GEN3(11,3,2)
INTERP_16_GEN2(11,5)
INTERP_16_GEN3(12,3,1)
INTERP_16_GEN2(13,3)
INTERP_16_GEN3(14,1,1)
INTERP_16_GEN2(15,1)
INTERP_16_GEN2(9,7)

static inline interp_uint32 interp_32_11(interp_uint32 p1, interp_uint32 p2)
{
#ifdef USE_INTERP_MASK_1
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1) + INTERP_32_MASK_1(p2)) / 2)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1) + INTERP_32_MASK_2(p2)) / 2);
#else
	/*
	 * This function compute (a + b) / 2 for any rgb nibble, using the
	 * the formula (a + b) / 2 = ((a ^ b) >> 1) + (a & b).
	 * To extend this formula to a serie of packed nibbles the formula is
	 * implemented as (((v0 ^ v1) >> 1) & MASK) + (v0 & v1) where MASK
	 * is used to clear the high bit of all the packed nibbles.
	 */
	return (((p1 ^ p2) >> 1) & INTERP_32_HNMASK) + (p1 & p2);
#endif
}

static inline interp_uint32 interp_32_211(interp_uint32 p1, interp_uint32 p2, interp_uint32 p3)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*2 + INTERP_32_MASK_1(p2) + INTERP_32_MASK_1(p3)) / 4)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*2 + INTERP_32_MASK_2(p2) + INTERP_32_MASK_2(p3)) / 4);
#else
	return interp_32_11(p1, interp_32_11(p2, p3));
#endif
}

static inline interp_uint32 interp_32_31(interp_uint32 p1, interp_uint32 p2)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*3 + INTERP_32_MASK_1(p2)) / 4)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*3 + INTERP_32_MASK_2(p2)) / 4);
#else
	return interp_32_11(p1, interp_32_11(p1, p2));
#endif
}

static inline interp_uint32 interp_32_521(interp_uint32 p1, interp_uint32 p2, interp_uint32 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*5 + INTERP_32_MASK_1(p2)*2 + INTERP_32_MASK_1(p3)) / 8)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*5 + INTERP_32_MASK_2(p2)*2 + INTERP_32_MASK_2(p3)) / 8);
#else
	return interp_32_11(p1, interp_32_11(p2, interp_32_11(p1, p3)));
#endif
}

static inline interp_uint32 interp_32_431(interp_uint32 p1, interp_uint32 p2, interp_uint32 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*4 + INTERP_32_MASK_1(p2)*3 + INTERP_32_MASK_1(p3)) / 8)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*4 + INTERP_32_MASK_2(p2)*3 + INTERP_32_MASK_2(p3)) / 8);
#else
	return interp_32_11(p1, interp_32_11(p2, interp_32_11(p2, p3)));
#endif
}

static inline interp_uint32 interp_32_53(interp_uint32 p1, interp_uint32 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*5 + INTERP_32_MASK_1(p2)*3) / 8)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*5 + INTERP_32_MASK_2(p2)*3) / 8);
#else
	return interp_32_11(p1, interp_32_11(p2, interp_32_11(p1, p2)));
#endif
}

static inline interp_uint32 interp_32_332(interp_uint32 p1, interp_uint32 p2, interp_uint32 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*3 + INTERP_32_MASK_1(p2)*3 + INTERP_32_MASK_1(p3)*2) / 8)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*3 + INTERP_32_MASK_2(p2)*3 + INTERP_32_MASK_2(p3)*2) / 8);
#else
	interp_uint32 t = interp_32_11(p1, p2);
	return interp_32_11(t, interp_32_11(p3, t));
#endif
}

static inline interp_uint32 interp_32_611(interp_uint32 p1, interp_uint32 p2, interp_uint32 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*6 + INTERP_32_MASK_1(p2) + INTERP_32_MASK_1(p3)) / 8)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*6 + INTERP_32_MASK_2(p2) + INTERP_32_MASK_2(p3)) / 8);
#else
	return interp_32_11(p1, interp_32_11(p1, interp_32_11(p2, p3)));
#endif
}

static inline interp_uint32 interp_32_71(interp_uint32 p1, interp_uint32 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_UNMASK_1((INTERP_32_MASK_1(p1)*7 + INTERP_32_MASK_1(p2)) / 8)
		| INTERP_32_UNMASK_2((INTERP_32_MASK_2(p1)*7 + INTERP_32_MASK_2(p2)) / 8);
#else
	return interp_32_11(p1, interp_32_11(p1, interp_32_11(p1, p2)));
#endif
}

INTERP_32_GEN3(6,5,5)
INTERP_32_GEN3(7,5,4)
INTERP_32_GEN3(7,6,3)
INTERP_32_GEN3(7,7,2)
INTERP_32_GEN3(8,5,3)
INTERP_32_GEN3(9,4,3)
INTERP_32_GEN3(9,6,1)
INTERP_32_GEN3(10,3,3)
INTERP_32_GEN3(10,5,1)
INTERP_32_GEN3(11,3,2)
INTERP_32_GEN2(11,5)
INTERP_32_GEN3(12,3,1)
INTERP_32_GEN2(13,3)
INTERP_32_GEN3(14,1,1)
INTERP_32_GEN2(15,1)
INTERP_32_GEN2(9,7)

int interp_16_diff(interp_uint16 p1, interp_uint16 p2);
int interp_32_diff(interp_uint32 p1, interp_uint32 p2);

void interp_set(unsigned color_def);

#endif

