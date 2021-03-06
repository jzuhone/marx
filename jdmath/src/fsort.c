/*
 Copyright (c) 2002,2013 John E. Davis

 This program is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the Free
 Software Foundation; either version 2 of the License, or (at your option)
 any later version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc., 675
 Mass Ave, Cambridge, MA 02139, USA.
*/
#include "config.h"

#include <stdio.h>

#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif

#include "jdmath.h"

static float *Sort_Array;
static int float_cmp (unsigned int *a, unsigned *b)
{
   float x, y;
   float *xp, *yp;

   x = *(xp = Sort_Array + *a);
   y = *(yp = Sort_Array + *b);
   if (x > y) return 1; else if (x < y) return -1;
   if (xp > yp) return 1;
   if (xp == yp) return 0;
   return -1;
}

unsigned int *JDMsort_floats (float *x, unsigned int n)
{
   /* This is a silly hack to make up for braindead compilers and the lack of
    * uniformity in prototypes for qsort.
    */
   void (*qsort_fun) (char *, unsigned int, int, int (*)(unsigned int *, unsigned int *));
   unsigned int *index_array;
   unsigned int i;

   if (NULL == (index_array = (unsigned int *) JDMinteger_vector (n)))
     return NULL;

   qsort_fun = (void (*)(char *, unsigned int, int, int (*)(unsigned int *,
							    unsigned int *)))
     qsort;
   for (i = 0; i < n; i++) index_array[i] = i;
   Sort_Array = x;
   (*qsort_fun) ((char *) index_array, n, sizeof (unsigned int), float_cmp);
   return index_array;
}
