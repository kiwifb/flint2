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

    Copyright (C) 2014 Abhinav Baid

******************************************************************************/

#include "fmpq_mat.h"

void fmpq_mat_gso(fmpq_mat_t B, const fmpq_mat_t A)
{
	slong i, j, k;
	fmpq_t num, den, mu;
	fmpq_init(num);
	fmpq_init(den);
	fmpq_init(mu);
	
	if(B->r != A->r || B->c != A->c) {
		flint_printf("Exception (fmpq_mat_gso). Incompatible dimensions.\n");
        abort();
	}
	
	if(B == A) {
		fmpq_mat_t t;
		fmpq_mat_init(t, B->r, B->c);
		fmpq_mat_gso(t, A);
		for(i = 0; i < B->r; i++) {
			for(j = 0; j < B->c; j++) {
				fmpq_swap(fmpq_mat_entry(B, i, j), 
                          fmpq_mat_entry(t, i, j));
			}
		}
		fmpq_mat_clear(t);
	}
	
	if(!A->r)
	{
		return;
	}
				
	for(i = 0; i < A->c; i++) {
		for(j = 0; j < A->r; j++) {
			fmpq_set(fmpq_mat_entry(B, j, i),
					 fmpq_mat_entry(A, j, i));
		}

		for(j = 0; j < i; j++) {
			fmpq_mul(num,
					 fmpq_mat_entry(A, 0, i),
					 fmpq_mat_entry(B, 0, j));
					 
			for(k = 1; k < A->r; k++) {
				fmpq_addmul(num,
							fmpq_mat_entry(A, k, i),
							fmpq_mat_entry(B, k, j));
			}
			
			fmpq_mul(den,
					 fmpq_mat_entry(B, 0, j),
					 fmpq_mat_entry(B, 0, j));
										
			for(k = 1; k < A->r; k++) {
				fmpq_addmul(den,
							fmpq_mat_entry(B, k, j),
							fmpq_mat_entry(B, k, j));
			}
			
			if(!fmpq_is_zero(den))
			{
				fmpq_div(mu, num, den);
			
				for(k = 0; k < A->r; k++) {
					fmpq_submul(fmpq_mat_entry(B, k, i),
								mu,
								fmpq_mat_entry(B, k, j));
				}
			}
		}
	}
	
	fmpq_clear(num);
	fmpq_clear(den);
	fmpq_clear(mu);
}