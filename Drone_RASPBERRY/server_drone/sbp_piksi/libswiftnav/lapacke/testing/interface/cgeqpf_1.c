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
* cgeqpf_1 is the test program for the C interface to LAPACK
* routine cgeqpf
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

static void init_scalars_cgeqpf( lapack_int *m, lapack_int *n,
                                 lapack_int *lda );
static void init_a( lapack_int size, lapack_complex_float *a );
static void init_jpvt( lapack_int size, lapack_int *jpvt );
static void init_tau( lapack_int size, lapack_complex_float *tau );
static void init_work( lapack_int size, lapack_complex_float *work );
static void init_rwork( lapack_int size, float *rwork );
static int compare_cgeqpf( lapack_complex_float *a, lapack_complex_float *a_i,
                           lapack_int *jpvt, lapack_int *jpvt_i,
                           lapack_complex_float *tau,
                           lapack_complex_float *tau_i, lapack_int info,
                           lapack_int info_i, lapack_int lda, lapack_int m,
                           lapack_int n );

int main(void)
{
    /* Local scalars */
    lapack_int m, m_i;
    lapack_int n, n_i;
    lapack_int lda, lda_i;
    lapack_int lda_r;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_complex_float *a = NULL, *a_i = NULL;
    lapack_int *jpvt = NULL, *jpvt_i = NULL;
    lapack_complex_float *tau = NULL, *tau_i = NULL;
    lapack_complex_float *work = NULL, *work_i = NULL;
    float *rwork = NULL, *rwork_i = NULL;
    lapack_complex_float *a_save = NULL;
    lapack_int *jpvt_save = NULL;
    lapack_complex_float *tau_save = NULL;
    lapack_complex_float *a_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_cgeqpf( &m, &n, &lda );
    lda_r = n+2;
    m_i = m;
    n_i = n;
    lda_i = lda;

    /* Allocate memory for the LAPACK routine arrays */
    a = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    jpvt = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    tau = (lapack_complex_float *)
        LAPACKE_malloc( MIN(m,n) * sizeof(lapack_complex_float) );
    work = (lapack_complex_float *)
        LAPACKE_malloc( n * sizeof(lapack_complex_float) );
    rwork = (float *)LAPACKE_malloc( 2*n * sizeof(float) );

    /* Allocate memory for the C interface function arrays */
    a_i = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    jpvt_i = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    tau_i = (lapack_complex_float *)
        LAPACKE_malloc( MIN(m,n) * sizeof(lapack_complex_float) );
    work_i = (lapack_complex_float *)
        LAPACKE_malloc( n * sizeof(lapack_complex_float) );
    rwork_i = (float *)LAPACKE_malloc( 2*n * sizeof(float) );

    /* Allocate memory for the backup arrays */
    a_save = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    jpvt_save = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    tau_save = (lapack_complex_float *)
        LAPACKE_malloc( MIN(m,n) * sizeof(lapack_complex_float) );

    /* Allocate memory for the row-major arrays */
    a_r = (lapack_complex_float *)
        LAPACKE_malloc( m*(n+2) * sizeof(lapack_complex_float) );

    /* Initialize input arrays */
    init_a( lda*n, a );
    init_jpvt( n, jpvt );
    init_tau( (MIN(m,n)), tau );
    init_work( n, work );
    init_rwork( 2*n, rwork );

    /* Backup the ouptut arrays */
    for( i = 0; i < lda*n; i++ ) {
        a_save[i] = a[i];
    }
    for( i = 0; i < n; i++ ) {
        jpvt_save[i] = jpvt[i];
    }
    for( i = 0; i < (MIN(m,n)); i++ ) {
        tau_save[i] = tau[i];
    }

    /* Call the LAPACK routine */
    cgeqpf_( &m, &n, a, &lda, jpvt, tau, work, rwork, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        jpvt_i[i] = jpvt_save[i];
    }
    for( i = 0; i < (MIN(m,n)); i++ ) {
        tau_i[i] = tau_save[i];
    }
    for( i = 0; i < n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < 2*n; i++ ) {
        rwork_i[i] = rwork[i];
    }
    info_i = LAPACKE_cgeqpf_work( LAPACK_COL_MAJOR, m_i, n_i, a_i, lda_i,
                                  jpvt_i, tau_i, work_i, rwork_i );

    failed = compare_cgeqpf( a, a_i, jpvt, jpvt_i, tau, tau_i, info, info_i,
                             lda, m, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to cgeqpf\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to cgeqpf\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        jpvt_i[i] = jpvt_save[i];
    }
    for( i = 0; i < (MIN(m,n)); i++ ) {
        tau_i[i] = tau_save[i];
    }
    for( i = 0; i < n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < 2*n; i++ ) {
        rwork_i[i] = rwork[i];
    }
    info_i = LAPACKE_cgeqpf( LAPACK_COL_MAJOR, m_i, n_i, a_i, lda_i, jpvt_i,
                             tau_i );

    failed = compare_cgeqpf( a, a_i, jpvt, jpvt_i, tau, tau_i, info, info_i,
                             lda, m, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to cgeqpf\n" );
    } else {
        printf( "FAILED: column-major high-level interface to cgeqpf\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        jpvt_i[i] = jpvt_save[i];
    }
    for( i = 0; i < (MIN(m,n)); i++ ) {
        tau_i[i] = tau_save[i];
    }
    for( i = 0; i < n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < 2*n; i++ ) {
        rwork_i[i] = rwork[i];
    }

    LAPACKE_cge_trans( LAPACK_COL_MAJOR, m, n, a_i, lda, a_r, n+2 );
    info_i = LAPACKE_cgeqpf_work( LAPACK_ROW_MAJOR, m_i, n_i, a_r, lda_r,
                                  jpvt_i, tau_i, work_i, rwork_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, m, n, a_r, n+2, a_i, lda );

    failed = compare_cgeqpf( a, a_i, jpvt, jpvt_i, tau, tau_i, info, info_i,
                             lda, m, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to cgeqpf\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to cgeqpf\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        jpvt_i[i] = jpvt_save[i];
    }
    for( i = 0; i < (MIN(m,n)); i++ ) {
        tau_i[i] = tau_save[i];
    }
    for( i = 0; i < n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < 2*n; i++ ) {
        rwork_i[i] = rwork[i];
    }

    /* Init row_major arrays */
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, m, n, a_i, lda, a_r, n+2 );
    info_i = LAPACKE_cgeqpf( LAPACK_ROW_MAJOR, m_i, n_i, a_r, lda_r, jpvt_i,
                             tau_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, m, n, a_r, n+2, a_i, lda );

    failed = compare_cgeqpf( a, a_i, jpvt, jpvt_i, tau, tau_i, info, info_i,
                             lda, m, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to cgeqpf\n" );
    } else {
        printf( "FAILED: row-major high-level interface to cgeqpf\n" );
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
    if( jpvt != NULL ) {
        LAPACKE_free( jpvt );
    }
    if( jpvt_i != NULL ) {
        LAPACKE_free( jpvt_i );
    }
    if( jpvt_save != NULL ) {
        LAPACKE_free( jpvt_save );
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
    if( rwork != NULL ) {
        LAPACKE_free( rwork );
    }
    if( rwork_i != NULL ) {
        LAPACKE_free( rwork_i );
    }

    return 0;
}

/* Auxiliary function: cgeqpf scalar parameters initialization */
static void init_scalars_cgeqpf( lapack_int *m, lapack_int *n, lapack_int *lda )
{
    *m = 5;
    *n = 4;
    *lda = 8;

    return;
}

/* Auxiliary functions: cgeqpf array parameters initialization */
static void init_a( lapack_int size, lapack_complex_float *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    a[0] = lapack_make_complex_float( 4.699999988e-001, -3.400000036e-001 );
    a[8] = lapack_make_complex_float( -4.000000060e-001, 5.400000215e-001 );
    a[16] = lapack_make_complex_float( 6.000000238e-001, 9.999999776e-003 );
    a[24] = lapack_make_complex_float( 8.000000119e-001, -1.019999981e+000 );
    a[1] = lapack_make_complex_float( -3.199999928e-001, -2.300000042e-001 );
    a[9] = lapack_make_complex_float( -5.000000075e-002, 2.000000030e-001 );
    a[17] = lapack_make_complex_float( -2.599999905e-001, -4.399999976e-001 );
    a[25] = lapack_make_complex_float( -4.300000072e-001, 1.700000018e-001 );
    a[2] = lapack_make_complex_float( 3.499999940e-001, -6.000000238e-001 );
    a[10] = lapack_make_complex_float( -5.199999809e-001, -3.400000036e-001 );
    a[18] = lapack_make_complex_float( 8.700000048e-001, -1.099999994e-001 );
    a[26] = lapack_make_complex_float( -3.400000036e-001, -9.000000358e-002 );
    a[3] = lapack_make_complex_float( 8.899999857e-001, 7.099999785e-001 );
    a[11] = lapack_make_complex_float( -4.499999881e-001, -4.499999881e-001 );
    a[19] = lapack_make_complex_float( -1.999999955e-002, -5.699999928e-001 );
    a[27] = lapack_make_complex_float( 1.139999986e+000, -7.799999714e-001 );
    a[4] = lapack_make_complex_float( -1.899999976e-001, 5.999999866e-002 );
    a[12] = lapack_make_complex_float( 1.099999994e-001, -8.500000238e-001 );
    a[20] = lapack_make_complex_float( 1.440000057e+000, 8.000000119e-001 );
    a[28] = lapack_make_complex_float( 7.000000030e-002, 1.139999986e+000 );
}
static void init_jpvt( lapack_int size, lapack_int *jpvt ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        jpvt[i] = 0;
    }
    jpvt[0] = 0;
    jpvt[1] = 0;
    jpvt[2] = 0;
    jpvt[3] = 0;
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
static void init_rwork( lapack_int size, float *rwork ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        rwork[i] = 0;
    }
}

/* Auxiliary function: C interface to cgeqpf results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_cgeqpf( lapack_complex_float *a, lapack_complex_float *a_i,
                           lapack_int *jpvt, lapack_int *jpvt_i,
                           lapack_complex_float *tau,
                           lapack_complex_float *tau_i, lapack_int info,
                           lapack_int info_i, lapack_int lda, lapack_int m,
                           lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < lda*n; i++ ) {
        failed += compare_complex_floats(a[i],a_i[i]);
    }
    for( i = 0; i < n; i++ ) {
        failed += (jpvt[i] == jpvt_i[i]) ? 0 : 1;
    }
    for( i = 0; i < (MIN(m,n)); i++ ) {
        failed += compare_complex_floats(tau[i],tau_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
