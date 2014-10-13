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
* sorglq_2 is the test program for the C interface to LAPACK
* routine sorglq
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

static void init_scalars_sorglq( lapack_int *m, lapack_int *n, lapack_int *k,
                                 lapack_int *lda, lapack_int *lwork );
static void init_a( lapack_int size, float *a );
static void init_tau( lapack_int size, float *tau );
static void init_work( lapack_int size, float *work );
static int compare_sorglq( float *a, float *a_i, lapack_int info,
                           lapack_int info_i, lapack_int lda, lapack_int n );

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
    float *a = NULL, *a_i = NULL;
    float *tau = NULL, *tau_i = NULL;
    float *work = NULL, *work_i = NULL;
    float *a_save = NULL;
    float *a_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_sorglq( &m, &n, &k, &lda, &lwork );
    lda_r = n+2;
    m_i = m;
    n_i = n;
    k_i = k;
    lda_i = lda;
    lwork_i = lwork;

    /* Allocate memory for the LAPACK routine arrays */
    a = (float *)LAPACKE_malloc( lda*n * sizeof(float) );
    tau = (float *)LAPACKE_malloc( k * sizeof(float) );
    work = (float *)LAPACKE_malloc( lwork * sizeof(float) );

    /* Allocate memory for the C interface function arrays */
    a_i = (float *)LAPACKE_malloc( lda*n * sizeof(float) );
    tau_i = (float *)LAPACKE_malloc( k * sizeof(float) );
    work_i = (float *)LAPACKE_malloc( lwork * sizeof(float) );

    /* Allocate memory for the backup arrays */
    a_save = (float *)LAPACKE_malloc( lda*n * sizeof(float) );

    /* Allocate memory for the row-major arrays */
    a_r = (float *)LAPACKE_malloc( m*(n+2) * sizeof(float) );

    /* Initialize input arrays */
    init_a( lda*n, a );
    init_tau( k, tau );
    init_work( lwork, work );

    /* Backup the ouptut arrays */
    for( i = 0; i < lda*n; i++ ) {
        a_save[i] = a[i];
    }

    /* Call the LAPACK routine */
    sorglq_( &m, &n, &k, a, &lda, tau, work, &lwork, &info );

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
    info_i = LAPACKE_sorglq_work( LAPACK_COL_MAJOR, m_i, n_i, k_i, a_i, lda_i,
                                  tau_i, work_i, lwork_i );

    failed = compare_sorglq( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to sorglq\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to sorglq\n" );
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
    info_i = LAPACKE_sorglq( LAPACK_COL_MAJOR, m_i, n_i, k_i, a_i, lda_i,
                             tau_i );

    failed = compare_sorglq( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to sorglq\n" );
    } else {
        printf( "FAILED: column-major high-level interface to sorglq\n" );
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

    LAPACKE_sge_trans( LAPACK_COL_MAJOR, m, n, a_i, lda, a_r, n+2 );
    info_i = LAPACKE_sorglq_work( LAPACK_ROW_MAJOR, m_i, n_i, k_i, a_r, lda_r,
                                  tau_i, work_i, lwork_i );

    LAPACKE_sge_trans( LAPACK_ROW_MAJOR, m, n, a_r, n+2, a_i, lda );

    failed = compare_sorglq( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to sorglq\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to sorglq\n" );
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
    LAPACKE_sge_trans( LAPACK_COL_MAJOR, m, n, a_i, lda, a_r, n+2 );
    info_i = LAPACKE_sorglq( LAPACK_ROW_MAJOR, m_i, n_i, k_i, a_r, lda_r,
                             tau_i );

    LAPACKE_sge_trans( LAPACK_ROW_MAJOR, m, n, a_r, n+2, a_i, lda );

    failed = compare_sorglq( a, a_i, info, info_i, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to sorglq\n" );
    } else {
        printf( "FAILED: row-major high-level interface to sorglq\n" );
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

/* Auxiliary function: sorglq scalar parameters initialization */
static void init_scalars_sorglq( lapack_int *m, lapack_int *n, lapack_int *k,
                                 lapack_int *lda, lapack_int *lwork )
{
    *m = 6;
    *n = 6;
    *k = 4;
    *lda = 8;
    *lwork = 1024;

    return;
}

/* Auxiliary functions: sorglq array parameters initialization */
static void init_a( lapack_int size, float *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = 0;
    }
    a[0] = 7.629240036e+000;  /* a[0,0] */
    a[8] = -2.513556182e-001;  /* a[0,1] */
    a[16] = 2.820087671e-001;  /* a[0,2] */
    a[24] = -2.069086023e-002;  /* a[0,3] */
    a[32] = -1.578635871e-001;  /* a[0,4] */
    a[40] = -3.525109589e-002;  /* a[0,5] */
    a[1] = 0.000000000e+000;  /* a[1,0] */
    a[9] = 6.484792709e+000;  /* a[1,1] */
    a[17] = 2.614412904e-001;  /* a[1,2] */
    a[25] = 1.032576039e-001;  /* a[1,3] */
    a[33] = 4.200951755e-001;  /* a[1,4] */
    a[41] = 7.010589354e-003;  /* a[1,5] */
    a[2] = 0.000000000e+000;  /* a[2,0] */
    a[10] = 2.040916309e-002;  /* a[2,1] */
    a[18] = -5.426580906e+000;  /* a[2,2] */
    a[26] = 6.051375270e-001;  /* a[2,3] */
    a[34] = -5.386683345e-001;  /* a[2,4] */
    a[42] = 1.685937792e-001;  /* a[2,5] */
    a[3] = 0.000000000e+000;  /* a[3,0] */
    a[11] = -3.216264248e-001;  /* a[3,1] */
    a[19] = 1.342281103e-001;  /* a[3,2] */
    a[27] = 6.255532265e+000;  /* a[3,3] */
    a[35] = -1.704478860e-001;  /* a[3,4] */
    a[43] = -3.498629630e-001;  /* a[3,5] */
    a[4] = 0.000000000e+000;  /* a[4,0] */
    a[12] = 0.000000000e+000;  /* a[4,1] */
    a[20] = 0.000000000e+000;  /* a[4,2] */
    a[28] = 0.000000000e+000;  /* a[4,3] */
    a[36] = 0.000000000e+000;  /* a[4,4] */
    a[44] = 0.000000000e+000;  /* a[4,5] */
    a[5] = 0.000000000e+000;  /* a[5,0] */
    a[13] = 0.000000000e+000;  /* a[5,1] */
    a[21] = 0.000000000e+000;  /* a[5,2] */
    a[29] = 0.000000000e+000;  /* a[5,3] */
    a[37] = 0.000000000e+000;  /* a[5,4] */
    a[45] = 0.000000000e+000;  /* a[5,5] */
}
static void init_tau( lapack_int size, float *tau ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        tau[i] = 0;
    }
    tau[0] = 1.710424662e+000;
    tau[1] = 1.592936516e+000;
    tau[2] = 1.187099457e+000;
    tau[3] = 1.736930490e+000;
}
static void init_work( lapack_int size, float *work ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        work[i] = 0;
    }
}

/* Auxiliary function: C interface to sorglq results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_sorglq( float *a, float *a_i, lapack_int info,
                           lapack_int info_i, lapack_int lda, lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < lda*n; i++ ) {
        failed += compare_floats(a[i],a_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
