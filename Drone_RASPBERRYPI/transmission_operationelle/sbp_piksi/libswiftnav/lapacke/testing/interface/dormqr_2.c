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
* dormqr_2 is the test program for the C interface to LAPACK
* routine dormqr
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

static void init_scalars_dormqr( char *side, char *trans, lapack_int *m,
                                 lapack_int *n, lapack_int *k, lapack_int *lda,
                                 lapack_int *ldc, lapack_int *lwork );
static void init_a( lapack_int size, double *a );
static void init_tau( lapack_int size, double *tau );
static void init_c( lapack_int size, double *c );
static void init_work( lapack_int size, double *work );
static int compare_dormqr( double *c, double *c_i, lapack_int info,
                           lapack_int info_i, lapack_int ldc, lapack_int n );

int main(void)
{
    /* Local scalars */
    char side, side_i;
    char trans, trans_i;
    lapack_int m, m_i;
    lapack_int n, n_i;
    lapack_int k, k_i;
    lapack_int lda, lda_i;
    lapack_int lda_r;
    lapack_int ldc, ldc_i;
    lapack_int ldc_r;
    lapack_int lwork, lwork_i;
    lapack_int info, info_i;
    /* Declare scalars */
    lapack_int r;
    lapack_int i;
    int failed;

    /* Local arrays */
    double *a = NULL, *a_i = NULL;
    double *tau = NULL, *tau_i = NULL;
    double *c = NULL, *c_i = NULL;
    double *work = NULL, *work_i = NULL;
    double *c_save = NULL;
    double *a_r = NULL;
    double *c_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_dormqr( &side, &trans, &m, &n, &k, &lda, &ldc, &lwork );
    r = LAPACKE_lsame( side, 'l' ) ? m : n;
    lda_r = k+2;
    ldc_r = n+2;
    side_i = side;
    trans_i = trans;
    m_i = m;
    n_i = n;
    k_i = k;
    lda_i = lda;
    ldc_i = ldc;
    lwork_i = lwork;

    /* Allocate memory for the LAPACK routine arrays */
    a = (double *)LAPACKE_malloc( lda*k * sizeof(double) );
    tau = (double *)LAPACKE_malloc( k * sizeof(double) );
    c = (double *)LAPACKE_malloc( ldc*n * sizeof(double) );
    work = (double *)LAPACKE_malloc( lwork * sizeof(double) );

    /* Allocate memory for the C interface function arrays */
    a_i = (double *)LAPACKE_malloc( lda*k * sizeof(double) );
    tau_i = (double *)LAPACKE_malloc( k * sizeof(double) );
    c_i = (double *)LAPACKE_malloc( ldc*n * sizeof(double) );
    work_i = (double *)LAPACKE_malloc( lwork * sizeof(double) );

    /* Allocate memory for the backup arrays */
    c_save = (double *)LAPACKE_malloc( ldc*n * sizeof(double) );

    /* Allocate memory for the row-major arrays */
    a_r = (double *)LAPACKE_malloc( r*(k+2) * sizeof(double) );
    c_r = (double *)LAPACKE_malloc( m*(n+2) * sizeof(double) );

    /* Initialize input arrays */
    init_a( lda*k, a );
    init_tau( k, tau );
    init_c( ldc*n, c );
    init_work( lwork, work );

    /* Backup the ouptut arrays */
    for( i = 0; i < ldc*n; i++ ) {
        c_save[i] = c[i];
    }

    /* Call the LAPACK routine */
    dormqr_( &side, &trans, &m, &n, &k, a, &lda, tau, c, &ldc, work, &lwork,
             &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*k; i++ ) {
        a_i[i] = a[i];
    }
    for( i = 0; i < k; i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < ldc*n; i++ ) {
        c_i[i] = c_save[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_dormqr_work( LAPACK_COL_MAJOR, side_i, trans_i, m_i, n_i,
                                  k_i, a_i, lda_i, tau_i, c_i, ldc_i, work_i,
                                  lwork_i );

    failed = compare_dormqr( c, c_i, info, info_i, ldc, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to dormqr\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to dormqr\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*k; i++ ) {
        a_i[i] = a[i];
    }
    for( i = 0; i < k; i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < ldc*n; i++ ) {
        c_i[i] = c_save[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_dormqr( LAPACK_COL_MAJOR, side_i, trans_i, m_i, n_i, k_i,
                             a_i, lda_i, tau_i, c_i, ldc_i );

    failed = compare_dormqr( c, c_i, info, info_i, ldc, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to dormqr\n" );
    } else {
        printf( "FAILED: column-major high-level interface to dormqr\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*k; i++ ) {
        a_i[i] = a[i];
    }
    for( i = 0; i < k; i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < ldc*n; i++ ) {
        c_i[i] = c_save[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }

    LAPACKE_dge_trans( LAPACK_COL_MAJOR, r, k, a_i, lda, a_r, k+2 );
    LAPACKE_dge_trans( LAPACK_COL_MAJOR, m, n, c_i, ldc, c_r, n+2 );
    info_i = LAPACKE_dormqr_work( LAPACK_ROW_MAJOR, side_i, trans_i, m_i, n_i,
                                  k_i, a_r, lda_r, tau_i, c_r, ldc_r, work_i,
                                  lwork_i );

    LAPACKE_dge_trans( LAPACK_ROW_MAJOR, m, n, c_r, n+2, c_i, ldc );

    failed = compare_dormqr( c, c_i, info, info_i, ldc, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to dormqr\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to dormqr\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*k; i++ ) {
        a_i[i] = a[i];
    }
    for( i = 0; i < k; i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < ldc*n; i++ ) {
        c_i[i] = c_save[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }

    /* Init row_major arrays */
    LAPACKE_dge_trans( LAPACK_COL_MAJOR, r, k, a_i, lda, a_r, k+2 );
    LAPACKE_dge_trans( LAPACK_COL_MAJOR, m, n, c_i, ldc, c_r, n+2 );
    info_i = LAPACKE_dormqr( LAPACK_ROW_MAJOR, side_i, trans_i, m_i, n_i, k_i,
                             a_r, lda_r, tau_i, c_r, ldc_r );

    LAPACKE_dge_trans( LAPACK_ROW_MAJOR, m, n, c_r, n+2, c_i, ldc );

    failed = compare_dormqr( c, c_i, info, info_i, ldc, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to dormqr\n" );
    } else {
        printf( "FAILED: row-major high-level interface to dormqr\n" );
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
    if( tau != NULL ) {
        LAPACKE_free( tau );
    }
    if( tau_i != NULL ) {
        LAPACKE_free( tau_i );
    }
    if( c != NULL ) {
        LAPACKE_free( c );
    }
    if( c_i != NULL ) {
        LAPACKE_free( c_i );
    }
    if( c_r != NULL ) {
        LAPACKE_free( c_r );
    }
    if( c_save != NULL ) {
        LAPACKE_free( c_save );
    }
    if( work != NULL ) {
        LAPACKE_free( work );
    }
    if( work_i != NULL ) {
        LAPACKE_free( work_i );
    }

    return 0;
}

/* Auxiliary function: dormqr scalar parameters initialization */
static void init_scalars_dormqr( char *side, char *trans, lapack_int *m,
                                 lapack_int *n, lapack_int *k, lapack_int *lda,
                                 lapack_int *ldc, lapack_int *lwork )
{
    *side = 'L';
    *trans = 'T';
    *m = 6;
    *n = 2;
    *k = 4;
    *lda = 8;
    *ldc = 8;
    *lwork = 512;

    return;
}

/* Auxiliary functions: dormqr array parameters initialization */
static void init_a( lapack_int size, double *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = 0;
    }
    a[0] = 3.61767881382524030e+000;  /* a[0,0] */
    a[8] = -5.56599992322389660e-001;  /* a[0,1] */
    a[16] = 8.47366545721238150e-001;  /* a[0,2] */
    a[24] = 7.46003207826611560e-001;  /* a[0,3] */
    a[1] = 4.60875842155869410e-001;  /* a[1,0] */
    a[9] = -2.02807703220235600e+000;  /* a[1,1] */
    a[17] = 5.51387235002093750e-001;  /* a[1,2] */
    a[25] = 1.16996276895584920e+000;  /* a[1,3] */
    a[2] = -5.49230278216839230e-001;  /* a[2,0] */
    a[10] = -4.57109828928023500e-002;  /* a[2,1] */
    a[18] = 1.37446064122229530e+000;  /* a[2,2] */
    a[26] = -1.41047378105999590e+000;  /* a[2,3] */
    a[3] = 4.60875842155869410e-001;  /* a[3,0] */
    a[11] = 2.82843169061735180e-001;  /* a[3,1] */
    a[19] = 4.43081480436171260e-003;  /* a[3,2] */
    a[27] = -2.37552731958861860e+000;  /* a[3,3] */
    a[4] = -3.58193659706634230e-002;  /* a[4,0] */
    a[12] = 7.96426824688575980e-002;  /* a[4,1] */
    a[20] = -7.72856175744114360e-002;  /* a[4,2] */
    a[28] = -5.21374484743236330e-001;  /* a[4,3] */
    a[5] = 4.77591546275512370e-003;  /* a[5,0] */
    a[13] = 3.00294208560961730e-001;  /* a[5,1] */
    a[21] = 8.01665355572227840e-001;  /* a[5,2] */
    a[29] = 2.55811387218232210e-001;  /* a[5,3] */
}
static void init_tau( lapack_int size, double *tau ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        tau[i] = 0;
    }
    tau[0] = 1.15755959258232120e+000;
    tau[1] = 1.69691513947038100e+000;
    tau[2] = 1.21310637129962080e+000;
    tau[3] = 1.49558337124162670e+000;
}
static void init_c( lapack_int size, double *c ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        c[i] = 0;
    }
    c[0] = -3.14999999999999990e+000;  /* c[0,0] */
    c[8] = 2.18999999999999990e+000;  /* c[0,1] */
    c[1] = -1.10000000000000000e-001;  /* c[1,0] */
    c[9] = -3.64000000000000010e+000;  /* c[1,1] */
    c[2] = 1.99000000000000000e+000;  /* c[2,0] */
    c[10] = 5.69999999999999950e-001;  /* c[2,1] */
    c[3] = -2.70000000000000020e+000;  /* c[3,0] */
    c[11] = 8.23000000000000040e+000;  /* c[3,1] */
    c[4] = 2.60000000000000010e-001;  /* c[4,0] */
    c[12] = -6.34999999999999960e+000;  /* c[4,1] */
    c[5] = 4.50000000000000000e+000;  /* c[5,0] */
    c[13] = -1.48000000000000000e+000;  /* c[5,1] */
}
static void init_work( lapack_int size, double *work ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        work[i] = 0;
    }
}

/* Auxiliary function: C interface to dormqr results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_dormqr( double *c, double *c_i, lapack_int info,
                           lapack_int info_i, lapack_int ldc, lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < ldc*n; i++ ) {
        failed += compare_doubles(c[i],c_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
