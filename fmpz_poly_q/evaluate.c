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

    Copyright (C) 2010, 2011 Sebastian Pancratz
   
******************************************************************************/

#include "fmpz_poly_q.h"

int fmpz_poly_q_evaluate(mpq_t rop, const fmpz_poly_q_t f, const mpq_t a)
{
    if (flint_mpz_cmp_si(mpq_denref(a), 1))  /* a is not an integer */
    {
        mpq_t mpqnum, mpqden;

        mpq_init(mpqden);
        fmpz_poly_evaluate_mpq(mpqden, f->den, a);
        if (mpq_sgn(mpqden) == 0)
        {
            mpq_clear(mpqden);
            return 1;
        }

        mpq_init(mpqnum);

        fmpz_poly_evaluate_mpq(mpqnum, f->num, a);
        mpq_div(rop, mpqnum, mpqden);

        mpq_clear(mpqnum);
        mpq_clear(mpqden);
        return 0;
    }
    else  /* a is an integer */
    {
        fmpz_t num, den, a2;

        fmpz_init(num);
        fmpz_init(den);
        fmpz_init(a2);

        fmpz_set_mpz(a2, mpq_numref(a));

        fmpz_poly_evaluate_fmpz(den, f->den, a2);
        if (fmpz_is_zero(den))
        {
            fmpz_clear(a2);
            fmpz_clear(num);
            fmpz_clear(den);
            return 1;
        }

        fmpz_poly_evaluate_fmpz(num, f->num, a2);

        fmpz_get_mpz(mpq_numref(rop), num);
        fmpz_get_mpz(mpq_denref(rop), den);
        mpq_canonicalize(rop);

        fmpz_clear(a2);
        fmpz_clear(num);
        fmpz_clear(den);
        return 0;
    }
}
