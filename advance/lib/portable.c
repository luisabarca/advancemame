/*
 * This file is part of the Advance project.
 *
 * Copyright (C) 1999-2002 Andrea Mazzoleni
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

/** \file
 * Implementation required for portability.
 */

#include "portable.h"

#include <stdio.h>

void sncpy(char* dst, size_t len, const char* src)
{
	if (len) {
		--len;
		while (len && *src) {
			*dst++ = *src++;
			--len;
		}
		*dst = 0;
#ifndef NDEBUG
		++dst;
		while (len) {
			*dst++ = 0;
			--len;
		}
#endif
	}
}

void sncat(char* dst, size_t len, const char* src)
{
	while (len && *dst) {
		++dst;
		--len;
	}
	sncpy(dst, len, src);
}

void sncatf(char* str, size_t count, const char* fmt, ...)
{
	unsigned l;
	va_list arg;
	va_start(arg, fmt);

	l = 0;
	while (l<count && str[l])
		++l;

	if (count > l)
		vsnprintf(str + l, count - l, fmt, arg);

	va_end(arg);
}

#ifdef __MSDOS__
int snprintf(char* str, size_t count, const char* fmt, ...)
{
	int r;

	/* Note that the snprintf implementation of "Patrick Powell 1995" has */
	/* various bugs on %f, %g and %e for example snprintf("%f",1.01) -> 1.1 */
	va_list arg;
	va_start(arg, fmt);
	r = vsprintf(str, fmt, arg);
	va_end(arg);

	return r;
}

int vsnprintf(char* str, size_t count, const char* fmt, va_list arg)
{
	return vsprintf(str, fmt, arg);
}
#endif
