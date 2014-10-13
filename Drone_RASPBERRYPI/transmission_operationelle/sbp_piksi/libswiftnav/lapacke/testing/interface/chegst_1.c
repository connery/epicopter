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
* chegst_1 is the test program for the C interface to LAPACK
* routine chegst
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

static void init_scalars_chegst( lapack_int *itype, char *uplo, lapack_int *n,
                                 lapack_int *lda, lapack_int *ldb );
static void init_a( lapack_int size, lapack_complex_float *a );
static void init_b( lapack_int size, lapack_complex_float *b );
static int compare_chegst( lapack_complex_float *a, lapack_complex_float *a_i,
                           lapack_int info, lapack_int info_i, lapack_int lda,
                           lapack_int n );

int main(void)
{
    /* Local scalars */
    lapack_int itype, itype_i;
    char uplo, uplo_i;
    lapack_int n, n_i;
    lapack_int lda, lda_i;
    lapack_int lda_r;
    lapack_int ldb, ldb_i;
    lapack_int ldb_r;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_complex_float *a = NULL, *a_i = NULL;
    lapack_complex_float *b = NULL, *b_i = NULL;
    lapack_complex_float *a_save = NULL;
    lapack_complex_float *a_r = NULL;
    lapack_complex_float *b_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_chegst( &itype, &uplo, &n, &lda, &ldb );
    lda_r = n+2;
    ldb_r = n+2;
    itype_i = itype;
    uplo_i = uplo;
    n_i = n;
    lda_i = lda;
    ldb_i = ldb;

    /* Allocate memory for the LAPACK routine arrays */
    a = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    b = (lapack_complex_float *)
        LAPACKE_malloc( ldb*n * sizeof(lapack_complex_float) );

    /* Allocate memory for the C interface function arrays */
    a_i = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    b_i = (lapack_complex_float *)
        LAPACKE_malloc( ldb*n * sizeof(lapack_complex_float) );

    /* Allocate memory for the backup arrays */
    a_save = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );

    /* Allocate memory for the row-major arrays */
    a_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+2) * sizeof(lapack_complex_float) );
    b_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+2) * sizeof(lapack_complex_float) );

    /* Initialize input arrays */
    init_a( lda*n, a );
    init_b( ldb*n, b );

    /* Backup the ouptut arrays */
    for( i = 0; i < lda*n; i++ ) {
        a_save[i] = a[i];
    }

    /* Call the LAPACK routine */
    chegst_( &itype, &uplo, &n, a, &lda, b, &ldb, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < ldb*n; i++ ) {
        b_i[i] = b[i];
    }
    info_i = LAPACKE_chegst_work( LAPACK_COL_MAJOR, itype_i, uplo_i, n_i, a_i,
                                  lda_i, b_i, ldb_i );

    failed = compare_chegst( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to chegst\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to chegst\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < ldb*n; i++ ) {
        b_i[i] = b[i];
    }
    info_i = LAPACKE_chegst( LAPACK_COL_MAJOR, itype_i, uplo_i, n_i, a_i, lda_i,
                             b_i, ldb_i );

    failed = compare_chegst( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to chegst\n" );
    } else {
        printf( "FAILED: column-major high-level interface to chegst\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < ldb*n; i++ ) {
        b_i[i] = b[i];
    }

    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, b_i, ldb, b_r, n+2 );
    info_i = LAPACKE_chegst_work( LAPACK_ROW_MAJOR, itype_i, uplo_i, n_i, a_r,
                                  lda_r, b_r, ldb_r );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, n, a_r, n+2, a_i, lda );

    failed = compare_chegst( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to chegst\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to chegst\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < ldb*n; i++ ) {
        b_i[i] = b[i];
    }

    /* Init row_major arrays */
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, b_i, ldb, b_r, n+2 );
    info_i = LAPACKE_chegst( LAPACK_ROW_MAJOR, itype_i, uplo_i, n_i, a_r, lda_r,
                             b_r, ldb_r );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, n, a_r, n+2, a_i, lda );

    failed = compare_chegst( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to chegst\n" );
    } else {
        printf( "FAILED: row-major high-level interface to chegst\n" );
    }

    /* Release memory */
    if( a != NULL ) {
        LAPACKE_free( a );
    }
    if( a_i != NULL ) {
        LAPACKE_free( a_i );
    }
    if( a_r != NULL ) {
        LAPACKE_free( a_r );
    }
    if( a_save != NULL ) {
        LAPACKE_free( a_save );
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

    return 0;
}

/* Auxiliary function: chegst scalar parameters initialization */
static void init_scalars_chegst( lapack_int *itype, char *uplo, lapack_int *n,
                                 lapack_int *lda, lapack_int *ldb )
{
    *itype = 1;
    *uplo = 'L';
    *n = 4;
    *lda = 8;
    *ldb = 8;

    return;
}

/* Auxiliary functions: chegst array parameters initialization */
static void init_a( lapack_int size, lapack_complex_float *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    a[0] = lapack_make_complex_float( -7.360000134e+000, 0.000000000e+000 );
    a[8] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[16] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[24] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[1] = lapack_make_complex_float( 7.699999809e-001, 4.300000072e-001 );
    a[9] = lapack_make_complex_float( 3.490000010e+000, 0.000000000e+000 );
    a[17] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[25] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[2] = lapack_make_complex_float( -6.399999857e-001, 9.200000167e-001 );
    a[10] = lapack_make_complex_float( 2.190000057e+000, -4.449999809e+000 );
    a[18] = lapack_make_complex_float( 1.199999973e-001, 0.000000000e+000 );
    a[26] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[3] = lapack_make_complex_float( 3.009999990e+000, 6.969999790e+000 );
    a[11] = lapack_make_complex_float( 1.899999976e+000, -3.730000019e+000 );
    a[19] = lapack_make_complex_float( 2.880000114e+000, 3.170000076e+000 );
    a[27] = lapack_make_complex_float( -2.539999962e+000, 0.000000000e+000 );
}
static void init_b( lapack_int size, lapack_complex_float *b ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        b[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    b[0] = lapack_make_complex_float( 1.797220111e+000, 0.000000000e+000 );
    b[8] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    b[16] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    b[24] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    b[1] = lapack_make_complex_float( 8.401864767e-001, 1.068316579e+000 );
    b[9] = lapack_make_complex_float( 1.316353440e+000, 0.000000000e+000 );
    b[17] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    b[25] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    b[2] = lapack_make_complex_float( 1.057188272e+000, -4.673885107e-001 );
    b[10] = lapack_make_complex_float( -4.701749086e-001, 3.130658567e-001 );
    b[18] = lapack_make_complex_float( 1.560392976e+000, 0.000000000e+000 );
    b[26] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    b[3] = lapack_make_complex_float( 2.336942554e-001, -1.391037226e+000 );
    b[11] = lapack_make_complex_float( 8.335255086e-002, 3.676066548e-002 );
    b[19] = lapack_make_complex_float( 9.359616637e-001, 9.899691939e-001 );
    b[27] = lapack_make_complex_float( 6.603333950e-001, 0.000000000e+000 );
}

/* Auxiliary function: C interface to chegst results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_chegst( lapack_complex_float *a, lapack_complex_float *a_i,
                           lapack_int info, lapack_int info_i, lapack_int lda,
                           lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < lda*n; i++ ) {
        failed += compare_complex_floats(a[i],a_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
