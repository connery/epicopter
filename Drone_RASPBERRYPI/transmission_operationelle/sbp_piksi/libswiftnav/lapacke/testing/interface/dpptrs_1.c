/*****************************************************************************
  Copyright (c) 2010, Intel Corp.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/
/*  Contents: test routine for C interface to LAPACK
*   Author: Intel Corporation
*   Created in March, 2010
*
* Purpose
*
* dpptrs_1 is the test program for the C interface to LAPACK
* routine dpptrs
* The program doesn't require an input, the input data is hardcoded in the
* test program.
* The program tests the C interface in the four combinations:
*   1) column-major layout, middle-level interface
*   2) column-major layout, high-level interface
*   3) row-major layout, middle-level interface
*   4) row-major layout, high-level interface
* The output of the C interface function is compared to those obtained from
* the corresponiding LAPACK routine with the same input data, and the
* comparison diagnostics is then printed on the standard output having PASSED
* keyword if the test is passed, and FAILED keyword if the test isn't passed.
*****************************************************************************/
#include <stdio.h>
#include "lapacke.h"
#include "lapacke_utils.h"
#include "test_utils.h"

static void init_scalars_dpptrs( char *uplo, lapack_int *n, lapack_int *nrhs,
                                 lapack_int *ldb );
static void init_ap( lapack_int size, double *ap );
static void init_b( lapack_int size, double *b );
static int compare_dpptrs( double *b, double *b_i, lapack_int info,
                           lapack_int info_i, lapack_int ldb, lapack_int nrhs );

int main(void)
{
    /* Local scalars */
    char uplo, uplo_i;
    lapack_int n, n_i;
    lapack_int nrhs, nrhs_i;
    lapack_int ldb, ldb_i;
    lapack_int ldb_r;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    double *ap = NULL, *ap_i = NULL;
    double *b = NULL, *b_i = NULL;
    double *b_save = NULL;
    double *ap_r = NULL;
    double *b_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_dpptrs( &uplo, &n, &nrhs, &ldb );
    ldb_r = nrhs+2;
    uplo_i = uplo;
    n_i = n;
    nrhs_i = nrhs;
    ldb_i = ldb;

    /* Allocate memory for the LAPACK routine arrays */
    ap = (double *)LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(double) );
    b = (double *)LAPACKE_malloc( ldb*nrhs * sizeof(double) );

    /* Allocate memory for the C interface function arrays */
    ap_i = (double *)LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(double) );
    b_i = (double *)LAPACKE_malloc( ldb*nrhs * sizeof(double) );

    /* Allocate memory for the backup arrays */
    b_save = (double *)LAPACKE_malloc( ldb*nrhs * sizeof(double) );

    /* Allocate memory for the row-major arrays */
    ap_r = (double *)LAPACKE_malloc( n*(n+1)/2 * sizeof(double) );
    b_r = (double *)LAPACKE_malloc( n*(nrhs+2) * sizeof(double) );

    /* Initialize input arrays */
    init_ap( (n*(n+1)/2), ap );
    init_b( ldb*nrhs, b );

    /* Backup the ouptut arrays */
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_save[i] = b[i];
    }

    /* Call the LAPACK routine */
    dpptrs_( &uplo, &n, &nrhs, ap, b, &ldb, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b_save[i];
    }
    info_i = LAPACKE_dpptrs_work( LAPACK_COL_MAJOR, uplo_i, n_i, nrhs_i, ap_i,
                                  b_i, ldb_i );

    failed = compare_dpptrs( b, b_i, info, info_i, ldb, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to dpptrs\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to dpptrs\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b_save[i];
    }
    info_i = LAPACKE_dpptrs( LAPACK_COL_MAJOR, uplo_i, n_i, nrhs_i, ap_i, b_i,
                             ldb_i );

    failed = compare_dpptrs( b, b_i, info, info_i, ldb, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to dpptrs\n" );
    } else {
        printf( "FAILED: column-major high-level interface to dpptrs\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b_save[i];
    }

    LAPACKE_dpp_trans( LAPACK_COL_MAJOR, uplo, n, ap_i, ap_r );
    LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, nrhs, b_i, ldb, b_r, nrhs+2 );
    info_i = LAPACKE_dpptrs_work( LAPACK_ROW_MAJOR, uplo_i, n_i, nrhs_i, ap_r,
                                  b_r, ldb_r );

    LAPACKE_dge_trans( LAPACK_ROW_MAJOR, n, nrhs, b_r, nrhs+2, b_i, ldb );

    failed = compare_dpptrs( b, b_i, info, info_i, ldb, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to dpptrs\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to dpptrs\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b_save[i];
    }

    /* Init row_major arrays */
    LAPACKE_dpp_trans( LAPACK_COL_MAJOR, uplo, n, ap_i, ap_r );
    LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, nrhs, b_i, ldb, b_r, nrhs+2 );
    info_i = LAPACKE_dpptrs( LAPACK_ROW_MAJOR, uplo_i, n_i, nrhs_i, ap_r, b_r,
                             ldb_r );

    LAPACKE_dge_trans( LAPACK_ROW_MAJOR, n, nrhs, b_r, nrhs+2, b_i, ldb );

    failed = compare_dpptrs( b, b_i, info, info_i, ldb, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to dpptrs\n" );
    } else {
        printf( "FAILED: row-major high-level interface to dpptrs\n" );
    }

    /* Release memory */
    if( ap != NULL ) {
        LAPACKE_free( ap );
    }
    if( ap_i != NULL ) {
        LAPACKE_free( ap_i );
    }
    if( ap_r != NULL ) {
        LAPACKE_free( ap_r );
    }
    if( b != NULL ) {
        LAPACKE_free( b );
    }
    if( b_i != NULL ) {
        LAPACKE_free( b_i );
    }
    if( b_r != NULL ) {
        LAPACKE_free( b_r );
    }
    if( b_save != NULL ) {
        LAPACKE_free( b_save );
    }

    return 0;
}

/* Auxiliary function: dpptrs scalar parameters initialization */
static void init_scalars_dpptrs( char *uplo, lapack_int *n, lapack_int *nrhs,
                                 lapack_int *ldb )
{
    *uplo = 'L';
    *n = 4;
    *nrhs = 2;
    *ldb = 8;

    return;
}

/* Auxiliary functions: dpptrs array parameters initialization */
static void init_ap( lapack_int size, double *ap ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        ap[i] = 0;
    }
    ap[0] = 2.03960780543711410e+000;
    ap[1] = -1.52970585407783540e+000;
    ap[2] = 2.74562589193457660e-001;
    ap[3] = -4.90290337845460110e-002;
    ap[4] = 1.64012194668567270e+000;
    ap[5] = -2.49981411948373810e-001;
    ap[6] = 6.73730390738910060e-001;
    ap[7] = 7.88748805574805310e-001;
    ap[8] = 6.61657563374256520e-001;
    ap[9] = 5.34689426929868320e-001;
}
static void init_b( lapack_int size, double *b ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        b[i] = 0;
    }
    b[0] = 8.69999999999999930e+000;  /* b[0,0] */
    b[8] = 8.30000000000000070e+000;  /* b[0,1] */
    b[1] = -1.33500000000000000e+001;  /* b[1,0] */
    b[9] = 2.12999999999999990e+000;  /* b[1,1] */
    b[2] = 1.88999999999999990e+000;  /* b[2,0] */
    b[10] = 1.61000000000000010e+000;  /* b[2,1] */
    b[3] = -4.13999999999999970e+000;  /* b[3,0] */
    b[11] = 5.00000000000000000e+000;  /* b[3,1] */
}

/* Auxiliary function: C interface to dpptrs results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_dpptrs( double *b, double *b_i, lapack_int info,
                           lapack_int info_i, lapack_int ldb, lapack_int nrhs )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < ldb*nrhs; i++ ) {
        failed += compare_doubles(b[i],b_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
