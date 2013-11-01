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


#ifdef T

#include "templates.h"

void
TEMPLATE(T, poly_factor_init)(TEMPLATE(T, poly_factor_t) fac, const TEMPLATE(T, ctx_t) ctx)
{
    slong i;

    fac->alloc = 5;
    fac->num = 0;
    fac->poly = flint_malloc(sizeof(TEMPLATE(T, poly_struct)) * 5);
    fac->exp = flint_malloc(sizeof(slong) * 5);

    for (i = 0; i < fac->alloc; i++)
        TEMPLATE(T, poly_init)(fac->poly + i, ctx);
}


#endif
