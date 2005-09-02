/*
 *  libfb - FreeBASIC's runtime library
 *	Copyright (C) 2004-2005 Andre V. T. Vicentini (av1ctor@yahoo.com.br) and others.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * strw_bin_lng.c -- binw$ routine for long long's
 *
 * chng: apr/2005 written [v1ctor]
 *
 */

#include "fb.h"
#include "fb_unicode.h"

#ifndef TARGET_WIN32
/*:::::*/
static void hToBin( unsigned long long num, FB_WCHAR *dst )
{
	int i;

	if( num == 0ULL )
		fb_wstr_PutChar( &dst, '0' );
	else
	{
		for( i = 0; i < sizeof( long long )*8; i++, num <<= 1 )
			if( num & 0x8000000000000000ULL )
				break;

		for( ; i < sizeof( long long )*8; i++, num <<= 1 )
			if( num & 0x8000000000000000ULL )
				fb_wstr_PutChar( &dst, '1' );
			else
				fb_wstr_PutChar( &dst, '0' );
	}

	/* add null-term */
	fb_wstr_PutChar( &dst, 0 );

}
#endif

/*:::::*/
FBCALL FB_WCHAR *fb_wStrBin_l ( unsigned long long num )
{
	FB_WCHAR *dst;

	/* alloc temp string */
    dst = fb_wstr_AllocTemp( sizeof( long long ) * 8 );
	if( dst != NULL )
	{
		/* convert */
#ifdef TARGET_WIN32
		_i64tow( num, dst, 2 );
#else
		hToBin( num, dst );
#endif
	}

	return dst;
}
