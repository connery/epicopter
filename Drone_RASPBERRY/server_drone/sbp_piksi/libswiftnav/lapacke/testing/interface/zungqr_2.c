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
* zungqr_2 is the test program for the C interface to LAPACK
* routine zungqr
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

static void init_scalars_zungqr( lapack_int *m, lapack_int *n, lapack_int *k,
                                 lapack_int *lda, lapack_int *lwork );
static void init_a( lapack_int size, lapack_complex_double *a );
static void init_tau( lapack_int size, lapack_complex_double *tau );
static void init_work( lapack_int size, lapack_complex_double *work );
static int compare_zungqr( lapack_complex_double *a, lapack_complex_double *a_i,
                           lapack_int info, lapack_int info_i, lapack_int lda,
                           lapack_int n );

int main(void)
{
    /* Local scalars */
    lapack_int m, m_i;
    lapack_int n, n_i;
    lapack_int k, k_i;
    lapack_int lda, lda_i;
    lapack_int lda_r;
    lapack_int lwork, lwork_i;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_complex_double *a = NULL, *a_i = NULL;
    lapack_complex_double *tau = NULL, *tau_i = NULL;
    lapack_complex_double *work = NULL, *work_i = NULL;
    lapack_complex_double *a_save = NULL;
    lapack_complex_double *a_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_zungqr( &m, &n, &k, &lda, &lwork );
    lda_r = n+2;
    m_i = m;
    n_i = n;
    k_i = k;
    lda_i = lda;
    lwork_i = lwork;

    /* Allocate memory for the LAPACK routine arrays */
    a = (lapack_complex_double *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_double) );
    tau = (lapack_complex_double *)
        LAPACKE_malloc( k * sizeof(lapack_complex_double) );
    work = (lapack_complex_double *)
        LAPACKE_malloc( lwork * sizeof(lapack_complex_double) );

    /* Allocate memory for the C interface function arrays */
    a_i = (lapack_complex_double *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_double) );
    tau_i = (lapack_complex_double *)
        LAPACKE_malloc( k * sizeof(lapack_complex_double) );
    work_i = (lapack_complex_double *)
        LAPACKE_malloc( lwork * sizeof(lapack_complex_double) );

    /* Allocate memory for the backup arrays */
    a_save = (lapack_complex_double *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_double) );

    /* Allocate memory for the row-major arrays */
    a_r = (lapack_complex_double *)
        LAPACKE_malloc( m*(n+2) * sizeof(lapack_complex_double) );

    /* Initialize input arrays */
    init_a( lda*n, a );
    init_tau( k, tau );
    init_work( lwork, work );

    /* Backup the ouptut arrays */
    for( i = 0; i < lda*n; i++ ) {
        a_save[i] = a[i];
    }

    /* Call the LAPACK routine */
    zungqr_( &m, &n, &k, a, &lda, tau, work, &lwork, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < k; i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_zungqr_work( LAPACK_COL_MAJOR, m_i, n_i, k_i, a_i, lda_i,
                                  tau_i, work_i, lwork_i );

    failed = compare_zungqr( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to zungqr\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to zungqr\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < k; i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_zungqr( LAPACK_COL_MAJOR, m_i, n_i, k_i, a_i, lda_i,
                             tau_i );

    failed = compare_zungqr( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to zungqr\n" );
    } else {
        printf( "FAILED: column-major high-level interface to zungqr\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < k; i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }

    LAPACKE_zge_trans( LAPACK_COL_MAJOR, m, n, a_i, lda, a_r, n+2 );
    info_i = LAPACKE_zungqr_work( LAPACK_ROW_MAJOR, m_i, n_i, k_i, a_r, lda_r,
                                  tau_i, work_i, lwork_i );

    LAPACKE_zge_trans( LAPACK_ROW_MAJOR, m, n, a_r, n+2, a_i, lda );

    failed = compare_zungqr( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to zungqr\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to zungqr\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < k; i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < lwork; i++ ) {
        work_i[i] = work[i];
    }

    /* Init row_major arrays */
    LAPACKE_zge_trans( LAPACK_COL_MAJOR, m, n, a_i, lda, a_r, n+2 );
    info_i = LAPACKE_zungqr( LAPACK_ROW_MAJOR, m_i, n_i, k_i, a_r, lda_r,
                             tau_i );

    LAPACKE_zge_trans( LAPACK_ROW_MAJOR, m, n, a_r, n+2, a_i, lda );

    failed = compare_zungqr( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to zungqr\n" );
    } else {
        printf( "FAILED: row-major high-level interface to zungqr\n" );
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
    if( tau != NULL ) {
        LAPACKE_free( tau );
    }
    if( tau_i != NULL ) {
        LAPACKE_free( tau_i );
    }
    if( work != NULL ) {
        LAPACKE_free( work );
    }
    if( work_i != NULL ) {
        LAPACKE_free( work_i );
    }

    return 0;
}

/* Auxiliary function: zungqr scalar parameters initialization */
static void init_scalars_zungqr( lapack_int *m, lapack_int *n, lapack_int *k,
                                 lapack_int *lda, lapack_int *lwork )
{
    *m = 6;
    *n = 6;
    *k = 4;
    *lda = 8;
    *lwork = 1024;

    return;
}

/* Auxiliary functions: zungqr array parameters initialization */
static void init_a( lapack_int size, lapack_complex_double *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = lapack_make_complex_double( 0.0, 0.0 );
    }
    a[0] = lapack_make_complex_double( -3.08700502105195800e+000,
                                       0.00000000000000000e+000 );
    a[8] = lapack_make_complex_double( 0.00000000000000000e+000,
                                       0.00000000000000000e+000 );
    a[16] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[24] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[32] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[40] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[1] = lapack_make_complex_double( -3.26978431123342020e-001,
                                       4.23806608064021150e-001 );
    a[9] = lapack_make_complex_double( 1.51631604729093160e+000,
                                       0.00000000000000000e+000 );
    a[17] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[25] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[33] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[41] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[2] = lapack_make_complex_double( 1.69172476430465120e-001,
                                       -7.98047673307239890e-002 );
    a[10] = lapack_make_complex_double( -4.53710486149829670e-001,
                                        -6.49149959135295050e-003 );
    a[18] = lapack_make_complex_double( -2.17134536255717010e+000,
                                        0.00000000000000000e+000 );
    a[26] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[34] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[42] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[3] = lapack_make_complex_double( -1.05973629513027950e-001,
                                       7.26861860966964010e-002 );
    a[11] = lapack_make_complex_double( -2.73407174139646880e-001,
                                        9.78078838704348470e-002 );
    a[19] = lapack_make_complex_double( -2.91822737804995960e-001,
                                        4.88808144155306160e-001 );
    a[27] = lapack_make_complex_double( -2.35337610655542080e+000,
                                        0.00000000000000000e+000 );
    a[35] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[43] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[4] = lapack_make_complex_double( 1.72939632545932170e-001,
                                       1.60632640429298590e-001 );
    a[12] = lapack_make_complex_double( -3.23630471463261900e-001,
                                        1.23000700219973860e-001 );
    a[20] = lapack_make_complex_double( 2.72768506164479230e-001,
                                        4.69769330690376700e-002 );
    a[28] = lapack_make_complex_double( 7.05422688603155710e-001,
                                        2.51508056610988850e-001 );
    a[36] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[44] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[5] = lapack_make_complex_double( 2.69899674468747240e-001,
                                       -1.51670836485297000e-002 );
    a[13] = lapack_make_complex_double( -1.64593543935458470e-001,
                                        3.38900720348261240e-001 );
    a[21] = lapack_make_complex_double( 5.34839525361778920e-001,
                                        3.98829067784022160e-001 );
    a[29] = lapack_make_complex_double( 2.70306990523076050e-001,
                                        -7.26878326406570770e-002 );
    a[37] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    a[45] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
}
static void init_tau( lapack_int size, lapack_complex_double *tau ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        tau[i] = lapack_make_complex_double( 0.0, 0.0 );
    }
    tau[0] = lapack_make_complex_double( 1.31098102965600650e+000,
                                         -2.62390243772255500e-001 );
    tau[1] = lapack_make_complex_double( 1.10510398911057410e+000,
                                         -4.50362538745018080e-001 );
    tau[2] = lapack_make_complex_double( 1.04025187161551910e+000,
                                         2.12175810726109660e-001 );
    tau[3] = lapack_make_complex_double( 1.18595901116610980e+000,
                                         2.01183600330743640e-001 );
}
static void init_work( lapack_int size, lapack_complex_double *work ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        work[i] = lapack_make_complex_double( 0.0, 0.0 );
    }
}

/* Auxiliary function: C interface to zungqr results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_zungqr( lapack_complex_double *a, lapack_complex_double *a_i,
                           lapack_int info, lapack_int info_i, lapack_int lda,
                           lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < lda*n; i++ ) {
        failed += compare_complex_doubles(a[i],a_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
