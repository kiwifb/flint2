/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2013 Mike Hansen

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "nmod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    printf("gcdinv....");
    fflush(stdout);

    flint_randinit(state);

    /* Generic case, most likely co-prime arguments ******************************/

    /* Compare with result from XGCD */
    for (i = 0; i < 1000; i++)
    {
        mp_limb_t p;
        nmod_poly_t a, b, d, g, s, t, u;

        
        p = n_randtest_prime(state, 0);

        nmod_poly_init(a, p);
        nmod_poly_init(b, p);
        nmod_poly_init(d, p);
        nmod_poly_init(g, p);
        nmod_poly_init(s, p);
        nmod_poly_init(t, p);
        nmod_poly_init(u, p);

        nmod_poly_randtest(a, state, n_randint(state, 100));
        do 
            nmod_poly_randtest(b, state, n_randint(state, 100));
        while (b->length < 2);

        nmod_poly_gcdinv(d, u, a, b);
        nmod_poly_xgcd(g, s, t, a, b);

        result = ((nmod_poly_equal(d, g) && nmod_poly_equal(u, s))
                  || (nmod_poly_is_zero(d)));
        if (!result)
        {
            printf("FAIL:\n");
            printf("a = "), nmod_poly_print(a), printf("\n\n");
            printf("b = "), nmod_poly_print(b), printf("\n\n");
            printf("d = "), nmod_poly_print(d), printf("\n\n");
            printf("g = "), nmod_poly_print(g), printf("\n\n");
            printf("s = "), nmod_poly_print(s), printf("\n\n");
            printf("t = "), nmod_poly_print(t), printf("\n\n");
            printf("u = "), nmod_poly_print(u), printf("\n\n");
            abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(d);
        nmod_poly_clear(g);
        nmod_poly_clear(s);
        nmod_poly_clear(t);
        nmod_poly_clear(u);
   }

    /* Special case, arguments share a factor ********************************/

    /* Compare with result from XGCD */
    for (i = 0; i < 1000; i++)
    {
        mp_limb_t p;
        nmod_poly_t a, b, d, f, g, s, t, u;

        p = n_randtest_prime(state, 0);

        nmod_poly_init(a, p);
        nmod_poly_init(b, p);
        nmod_poly_init(d, p);
        nmod_poly_init(f, p);
        nmod_poly_init(g, p);
        nmod_poly_init(s, p);
        nmod_poly_init(t, p);
        nmod_poly_init(u, p);

        nmod_poly_randtest(a, state, n_randint(state, 100));
        do 
            nmod_poly_randtest(b, state, n_randint(state, 100));
        while (b->length < 2);
        nmod_poly_randtest_not_zero(f, state, n_randint(state, 20) + 1);
        nmod_poly_mul(a, f, a);
        nmod_poly_mul(b, f, b);

        nmod_poly_gcdinv(d, u, a, b);
        nmod_poly_xgcd(g, s, t, a, b);

        result = ((nmod_poly_equal(d, g) && nmod_poly_equal(u, s))
                  || (nmod_poly_is_zero(d)));
        if (!result)
        {
            printf("FAIL:\n");
            printf("a = "), nmod_poly_print(a), printf("\n\n");
            printf("b = "), nmod_poly_print(b), printf("\n\n");
            printf("d = "), nmod_poly_print(d), printf("\n\n");
            printf("f = "), nmod_poly_print(f), printf("\n\n");
            printf("g = "), nmod_poly_print(g), printf("\n\n");
            printf("s = "), nmod_poly_print(s), printf("\n\n");
            printf("t = "), nmod_poly_print(t), printf("\n\n");
            printf("u = "), nmod_poly_print(u), printf("\n\n");
            abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(d);
        nmod_poly_clear(f);
        nmod_poly_clear(g);
        nmod_poly_clear(s);
        nmod_poly_clear(t);
        nmod_poly_clear(u);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return 0;
}

