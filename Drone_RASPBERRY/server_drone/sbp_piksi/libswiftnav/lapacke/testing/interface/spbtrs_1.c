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
* spbtrs_1 is the test program for the C interface to LAPACK
* routine spbtrs
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

static void init_scalars_spbtrs( char *uplo, lapack_int *n, lapack_int *kd,
                                 lapack_int *nrhs, lapack_int *ldab,
                                 lapack_int *ldb );
static void init_ab( lapack_int size, float *ab );
static void init_b( lapack_int size, float *b );
static int compare_spbtrs( float *b, float *b_i, lapack_int info,
                           lapack_int info_i, lapack_int ldb, lapack_int nrhs );

int main(void)
{
    /* Local scalars */
    char uplo, uplo_i;
    lapack_int n, n_i;
    lapack_int kd, kd_i;
    lapack_int nrhs, nrhs_i;
    lapack_int ldab, ldab_i;
    lapack_int ldab_r;
    lapack_int ldb, ldb_i;
    lapack_int ldb_r;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    float *ab = NULL, *ab_i = NULL;
    float *b = NULL, *b_i = NULL;
    float *b_save = NULL;
    float *ab_r = NULL;
    float *b_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_spbtrs( &uplo, &n, &kd, &nrhs, &ldab, &ldb );
    ldab_r = n+2;
    ldb_r = nrhs+2;
    uplo_i = uplo;
    n_i = n;
    kd_i = kd;
    nrhs_i = nrhs;
    ldab_i = ldab;
    ldb_i = ldb;

    /* Allocate memory for the LAPACK routine arrays */
    ab = (float *)LAPACKE_malloc( ldab*n * sizeof(float) );
    b = (float *)LAPACKE_malloc( ldb*nrhs * sizeof(float) );

    /* Allocate memory for the C interface function arrays */
    ab_i = (float *)LAPACKE_malloc( ldab*n * sizeof(float) );
    b_i = (float *)LAPACKE_malloc( ldb*nrhs * sizeof(float) );

    /* Allocate memory for the backup arrays */
    b_save = (float *)LAPACKE_malloc( ldb*nrhs * sizeof(float) );

    /* Allocate memory for the row-major arrays */
    ab_r = (float *)LAPACKE_malloc( (kd+1)*(n+2) * sizeof(float) );
    b_r = (float *)LAPACKE_malloc( n*(nrhs+2) * sizeof(float) );

    /* Initialize input arrays */
    init_ab( ldab*n, ab );
    init_b( ldb*nrhs, b );

    /* Backup the ouptut arrays */
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_save[i] = b[i];
    }

    /* Call the LAPACK routine */
    spbtrs_( &uplo, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < ldab*n; i++ ) {
        ab_i[i] = ab[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b_save[i];
    }
    info_i = LAPACKE_spbtrs_work( LAPACK_COL_MAJOR, uplo_i, n_i, kd_i, nrhs_i,
                                  ab_i, ldab_i, b_i, ldb_i );

    failed = compare_spbtrs( b, b_i, info, info_i, ldb, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to spbtrs\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to spbtrs\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < ldab*n; i++ ) {
        ab_i[i] = ab[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b_save[i];
    }
    info_i = LAPACKE_spbtrs( LAPACK_COL_MAJOR, uplo_i, n_i, kd_i, nrhs_i, ab_i,
                             ldab_i, b_i, ldb_i );

    failed = compare_spbtrs( b, b_i, info, info_i, ldb, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to spbtrs\n" );
    } else {
        printf( "FAILED: column-major high-level interface to spbtrs\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < ldab*n; i++ ) {
        ab_i[i] = ab[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b_save[i];
    }

    LAPACKE_sge_trans( LAPACK_COL_MAJOR, kd+1, n, ab_i, ldab, ab_r, n+2 );
    LAPACKE_sge_trans( LAPACK_COL_MAJOR, n, nrhs, b_i, ldb, b_r, nrhs+2 );
    info_i = LAPACKE_spbtrs_work( LAPACK_ROW_MAJOR, uplo_i, n_i, kd_i, nrhs_i,
                                  ab_r, ldab_r, b_r, ldb_r );

    LAPACKE_sge_trans( LAPACK_ROW_MAJOR, n, nrhs, b_r, nrhs+2, b_i, ldb );

    failed = compare_spbtrs( b, b_i, info, info_i, ldb, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to spbtrs\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to spbtrs\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < ldab*n; i++ ) {
        ab_i[i] = ab[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b_save[i];
    }

    /* Init row_major arrays */
    LAPACKE_sge_trans( LAPACK_COL_MAJOR, kd+1, n, ab_i, ldab, ab_r, n+2 );
    LAPACKE_sge_trans( LAPACK_COL_MAJOR, n, nrhs, b_i, ldb, b_r, nrhs+2 );
    info_i = LAPACKE_spbtrs( LAPACK_ROW_MAJOR, uplo_i, n_i, kd_i, nrhs_i, ab_r,
                             ldab_r, b_r, ldb_r );

    LAPACKE_sge_trans( LAPACK_ROW_MAJOR, n, nrhs, b_r, nrhs+2, b_i, ldb );

    failed = compare_spbtrs( b, b_i, info, info_i, ldb, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to spbtrs\n" );
    } else {
        printf( "FAILED: row-major high-level interface to spbtrs\n" );
    }

    /* Release memory */
    if( ab != NULL ) {
        LAPACKE_free( ab );
    }
    if( ab_i != NULL ) {
        LAPACKE_free( ab_i );
    }
    if( ab_r != NULL ) {
        LAPACKE_free( ab_r );
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

/* Auxiliary function: spbtrs scalar parameters initialization */
static void init_scalars_spbtrs( char *uplo, lapack_int *n, lapack_int *kd,
                                 lapack_int *nrhs, lapack_int *ldab,
                                 lapack_int *ldb )
{
    *uplo = 'L';
    *n = 4;
    *kd = 1;
    *nrhs = 2;
    *ldab = 9;
    *ldb = 8;

    return;
}

/* Auxiliary functions: spbtrs array parameters initialization */
static void init_ab( lapack_int size, float *ab ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        ab[i] = 0;
    }
    ab[0] = 2.343074799e+000;  /* ab[0,0] */
    ab[9] = 2.078877211e+000;  /* ab[0,1] */
    ab[18] = 1.130612254e+000;  /* ab[0,2] */
    ab[27] = 1.146524668e+000;  /* ab[0,3] */
    ab[1] = 1.143796206e+000;  /* ab[1,0] */
    ab[10] = -1.149659038e+000;  /* ab[1,1] */
    ab[19] = -1.963537931e+000;  /* ab[1,2] */
    ab[28] = 0.000000000e+000;  /* ab[1,3] */
}
static void init_b( lapack_int size, float *b ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        b[i] = 0;
    }
    b[0] = 2.209000015e+001;  /* b[0,0] */
    b[8] = 5.099999905e+000;  /* b[0,1] */
    b[1] = 9.310000420e+000;  /* b[1,0] */
    b[9] = 3.080999947e+001;  /* b[1,1] */
    b[2] = -5.239999771e+000;  /* b[2,0] */
    b[10] = -2.581999969e+001;  /* b[2,1] */
    b[3] = 1.182999992e+001;  /* b[3,0] */
    b[11] = 2.289999962e+001;  /* b[3,1] */
}

/* Auxiliary function: C interface to spbtrs results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_spbtrs( float *b, float *b_i, lapack_int info,
                           lapack_int info_i, lapack_int ldb, lapack_int nrhs )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < ldb*nrhs; i++ ) {
        failed += compare_floats(b[i],b_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
