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
* chetrd_3 is the test program for the C interface to LAPACK
* routine chetrd
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

static void init_scalars_chetrd( char *uplo, lapack_int *n, lapack_int *lda,
                                 lapack_int *lwork );
static void init_a( lapack_int size, lapack_complex_float *a );
static void init_d( lapack_int size, float *d );
static void init_e( lapack_int size, float *e );
static void init_tau( lapack_int size, lapack_complex_float *tau );
static void init_work( lapack_int size, lapack_complex_float *work );
static int compare_chetrd( lapack_complex_float *a, lapack_complex_float *a_i,
                           float *d, float *d_i, float *e, float *e_i,
                           lapack_complex_float *tau,
                           lapack_complex_float *tau_i, lapack_int info,
                           lapack_int info_i, lapack_int lda, lapack_int n );

int main(void)
{
    /* Local scalars */
    char uplo, uplo_i;
    lapack_int n, n_i;
    lapack_int lda, lda_i;
    lapack_int lda_r;
    lapack_int lwork, lwork_i;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_complex_float *a = NULL, *a_i = NULL;
    float *d = NULL, *d_i = NULL;
    float *e = NULL, *e_i = NULL;
    lapack_complex_float *tau = NULL, *tau_i = NULL;
    lapack_complex_float *work = NULL, *work_i = NULL;
    lapack_complex_float *a_save = NULL;
    float *d_save = NULL;
    float *e_save = NULL;
    lapack_complex_float *tau_save = NULL;
    lapack_complex_float *a_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_chetrd( &uplo, &n, &lda, &lwork );
    lda_r = n+2;
    uplo_i = uplo;
    n_i = n;
    lda_i = lda;
    lwork_i = lwork;

    /* Allocate memory for the LAPACK routine arrays */
    a = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    d = (float *)LAPACKE_malloc( n * sizeof(float) );
    e = (float *)LAPACKE_malloc( (n-1) * sizeof(float) );
    tau = (lapack_complex_float *)
        LAPACKE_malloc( (n-1) * sizeof(lapack_complex_float) );
    work = (lapack_complex_float *)
        LAPACKE_malloc( lwork * sizeof(lapack_complex_float) );

    /* Allocate memory for the C interface function arrays */
    a_i = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    d_i = (float *)LAPACKE_malloc( n * sizeof(float) );
    e_i = (float *)LAPACKE_malloc( (n-1) * sizeof(float) );
    tau_i = (lapack_complex_float *)
        LAPACKE_malloc( (n-1) * sizeof(lapack_complex_float) );
    work_i = (lapack_complex_float *)
        LAPACKE_malloc( lwork * sizeof(lapack_complex_float) );

    /* Allocate memory for the backup arrays */
    a_save = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    d_save = (float *)LAPACKE_malloc( n * sizeof(float) );
    e_save = (float *)LAPACKE_malloc( (n-1) * sizeof(float) );
    tau_save = (lapack_complex_float *)
        LAPACKE_malloc( (n-1) * sizeof(lapack_complex_float) );

    /* Allocate memory for the row-major arrays */
    a_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+2) * sizeof(lapack_complex_float) );

    /* Initialize input arrays */
    init_a( lda*n, a );
    init_d( n, d );
    init_e( (n-1), e );
    init_tau( (n-1), tau );
    init_work( lwork, work );

    /* Backup the ouptut arrays */
    for( i = 0; i < lda*n; i++ ) {
        a_save[i] = a[i];
    }
    for( i = 0; i < n; i++ ) {
        d_save[i] = d[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        e_save[i] = e[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_save[i] = tau[i];
    }

    /* Call the LAPACK routine */
    chetrd_( &uplo, &n, a, &lda, d, e, tau, work, &lwork, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        d_i[i] = d_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        e_i[i] = e_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_i[i] = tau_save[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_chetrd_work( LAPACK_COL_MAJOR, uplo_i, n_i, a_i, lda_i,
                                  d_i, e_i, tau_i, work_i, lwork_i );

    failed = compare_chetrd( a, a_i, d, d_i, e, e_i, tau, tau_i, info, info_i,
                             lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to chetrd\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to chetrd\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        d_i[i] = d_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        e_i[i] = e_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_i[i] = tau_save[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_chetrd( LAPACK_COL_MAJOR, uplo_i, n_i, a_i, lda_i, d_i,
                             e_i, tau_i );

    failed = compare_chetrd( a, a_i, d, d_i, e, e_i, tau, tau_i, info, info_i,
                             lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to chetrd\n" );
    } else {
        printf( "FAILED: column-major high-level interface to chetrd\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        d_i[i] = d_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        e_i[i] = e_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_i[i] = tau_save[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }

    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    info_i = LAPACKE_chetrd_work( LAPACK_ROW_MAJOR, uplo_i, n_i, a_r, lda_r,
                                  d_i, e_i, tau_i, work_i, lwork_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, n, a_r, n+2, a_i, lda );

    failed = compare_chetrd( a, a_i, d, d_i, e, e_i, tau, tau_i, info, info_i,
                             lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to chetrd\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to chetrd\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        d_i[i] = d_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        e_i[i] = e_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_i[i] = tau_save[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }

    /* Init row_major arrays */
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    info_i = LAPACKE_chetrd( LAPACK_ROW_MAJOR, uplo_i, n_i, a_r, lda_r, d_i,
                             e_i, tau_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, n, a_r, n+2, a_i, lda );

    failed = compare_chetrd( a, a_i, d, d_i, e, e_i, tau, tau_i, info, info_i,
                             lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to chetrd\n" );
    } else {
        printf( "FAILED: row-major high-level interface to chetrd\n" );
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
    if( d != NULL ) {
        LAPACKE_free( d );
    }
    if( d_i != NULL ) {
        LAPACKE_free( d_i );
    }
    if( d_save != NULL ) {
        LAPACKE_free( d_save );
    }
    if( e != NULL ) {
        LAPACKE_free( e );
    }
    if( e_i != NULL ) {
        LAPACKE_free( e_i );
    }
    if( e_save != NULL ) {
        LAPACKE_free( e_save );
    }
    if( tau != NULL ) {
        LAPACKE_free( tau );
    }
    if( tau_i != NULL ) {
        LAPACKE_free( tau_i );
    }
    if( tau_save != NULL ) {
        LAPACKE_free( tau_save );
    }
    if( work != NULL ) {
        LAPACKE_free( work );
    }
    if( work_i != NULL ) {
        LAPACKE_free( work_i );
    }

    return 0;
}

/* Auxiliary function: chetrd scalar parameters initialization */
static void init_scalars_chetrd( char *uplo, lapack_int *n, lapack_int *lda,
                                 lapack_int *lwork )
{
    *uplo = 'L';
    *n = 4;
    *lda = 8;
    *lwork = 512;

    return;
}

/* Auxiliary functions: chetrd array parameters initialization */
static void init_a( lapack_int size, lapack_complex_float *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    a[0] = lapack_make_complex_float( 6.019999981e+000, 0.000000000e+000 );
    a[8] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[16] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[24] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[1] = lapack_make_complex_float( -4.499999881e-001, -2.500000000e-001 );
    a[9] = lapack_make_complex_float( 2.910000086e+000, 0.000000000e+000 );
    a[17] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[25] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[2] = lapack_make_complex_float( -1.299999952e+000, -1.740000010e+000 );
    a[10] = lapack_make_complex_float( 5.000000075e-002, -1.559999943e+000 );
    a[18] = lapack_make_complex_float( 3.289999962e+000, 0.000000000e+000 );
    a[26] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[3] = lapack_make_complex_float( 1.450000048e+000, 6.600000262e-001 );
    a[11] = lapack_make_complex_float( -1.039999962e+000, -1.269999981e+000 );
    a[19] = lapack_make_complex_float( 1.400000006e-001, -1.700000048e+000 );
    a[27] = lapack_make_complex_float( 4.179999828e+000, 0.000000000e+000 );
}
static void init_d( lapack_int size, float *d ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        d[i] = 0;
    }
}
static void init_e( lapack_int size, float *e ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        e[i] = 0;
    }
}
static void init_tau( lapack_int size, lapack_complex_float *tau ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        tau[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
}
static void init_work( lapack_int size, lapack_complex_float *work ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        work[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
}

/* Auxiliary function: C interface to chetrd results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_chetrd( lapack_complex_float *a, lapack_complex_float *a_i,
                           float *d, float *d_i, float *e, float *e_i,
                           lapack_complex_float *tau,
                           lapack_complex_float *tau_i, lapack_int info,
                           lapack_int info_i, lapack_int lda, lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < lda*n; i++ ) {
        failed += compare_complex_floats(a[i],a_i[i]);
    }
    for( i = 0; i < n; i++ ) {
        failed += compare_floats(d[i],d_i[i]);
    }
    for( i = 0; i < (n-1); i++ ) {
        failed += compare_floats(e[i],e_i[i]);
    }
    for( i = 0; i < (n-1); i++ ) {
        failed += compare_complex_floats(tau[i],tau_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
