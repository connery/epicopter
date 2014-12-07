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
* sgebal_1 is the test program for the C interface to LAPACK
* routine sgebal
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

static void init_scalars_sgebal( char *job, lapack_int *n, lapack_int *lda );
static void init_a( lapack_int size, float *a );
static void init_scale( lapack_int size, float *scale );
static int compare_sgebal( float *a, float *a_i, lapack_int ilo,
                           lapack_int ilo_i, lapack_int ihi, lapack_int ihi_i,
                           float *scale, float *scale_i, lapack_int info,
                           lapack_int info_i, char job, lapack_int lda,
                           lapack_int n );

int main(void)
{
    /* Local scalars */
    char job, job_i;
    lapack_int n, n_i;
    lapack_int lda, lda_i;
    lapack_int lda_r;
    lapack_int ilo, ilo_i;
    lapack_int ihi, ihi_i;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    float *a = NULL, *a_i = NULL;
    float *scale = NULL, *scale_i = NULL;
    float *a_save = NULL;
    float *scale_save = NULL;
    float *a_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_sgebal( &job, &n, &lda );
    lda_r = n+2;
    job_i = job;
    n_i = n;
    lda_i = lda;

    /* Allocate memory for the LAPACK routine arrays */
    a = (float *)LAPACKE_malloc( lda*n * sizeof(float) );
    scale = (float *)LAPACKE_malloc( n * sizeof(float) );

    /* Allocate memory for the C interface function arrays */
    a_i = (float *)LAPACKE_malloc( lda*n * sizeof(float) );
    scale_i = (float *)LAPACKE_malloc( n * sizeof(float) );

    /* Allocate memory for the backup arrays */
    a_save = (float *)LAPACKE_malloc( lda*n * sizeof(float) );
    scale_save = (float *)LAPACKE_malloc( n * sizeof(float) );

    /* Allocate memory for the row-major arrays */
    a_r = (float *)LAPACKE_malloc( n*(n+2) * sizeof(float) );

    /* Initialize input arrays */
    init_a( lda*n, a );
    init_scale( n, scale );

    /* Backup the ouptut arrays */
    for( i = 0; i < lda*n; i++ ) {
        a_save[i] = a[i];
    }
    for( i = 0; i < n; i++ ) {
        scale_save[i] = scale[i];
    }

    /* Call the LAPACK routine */
    sgebal_( &job, &n, a, &lda, &ilo, &ihi, scale, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale_save[i];
    }
    info_i = LAPACKE_sgebal_work( LAPACK_COL_MAJOR, job_i, n_i, a_i, lda_i,
                                  &ilo_i, &ihi_i, scale_i );

    failed = compare_sgebal( a, a_i, ilo, ilo_i, ihi, ihi_i, scale, scale_i,
                             info, info_i, job, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to sgebal\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to sgebal\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale_save[i];
    }
    info_i = LAPACKE_sgebal( LAPACK_COL_MAJOR, job_i, n_i, a_i, lda_i, &ilo_i,
                             &ihi_i, scale_i );

    failed = compare_sgebal( a, a_i, ilo, ilo_i, ihi, ihi_i, scale, scale_i,
                             info, info_i, job, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to sgebal\n" );
    } else {
        printf( "FAILED: column-major high-level interface to sgebal\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale_save[i];
    }

    if( LAPACKE_lsame( job, 'b' ) || LAPACKE_lsame( job, 'p' ) ||
        LAPACKE_lsame( job, 's' ) ) {
        LAPACKE_sge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    }
    info_i = LAPACKE_sgebal_work( LAPACK_ROW_MAJOR, job_i, n_i, a_r, lda_r,
                                  &ilo_i, &ihi_i, scale_i );

    if( LAPACKE_lsame( job, 'b' ) || LAPACKE_lsame( job, 'p' ) ||
        LAPACKE_lsame( job, 's' ) ) {
        LAPACKE_sge_trans( LAPACK_ROW_MAJOR, n, n, a_r, n+2, a_i, lda );
    }

    failed = compare_sgebal( a, a_i, ilo, ilo_i, ihi, ihi_i, scale, scale_i,
                             info, info_i, job, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to sgebal\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to sgebal\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale_save[i];
    }

    /* Init row_major arrays */
    if( LAPACKE_lsame( job, 'b' ) || LAPACKE_lsame( job, 'p' ) ||
        LAPACKE_lsame( job, 's' ) ) {
        LAPACKE_sge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    }
    info_i = LAPACKE_sgebal( LAPACK_ROW_MAJOR, job_i, n_i, a_r, lda_r, &ilo_i,
                             &ihi_i, scale_i );

    if( LAPACKE_lsame( job, 'b' ) || LAPACKE_lsame( job, 'p' ) ||
        LAPACKE_lsame( job, 's' ) ) {
        LAPACKE_sge_trans( LAPACK_ROW_MAJOR, n, n, a_r, n+2, a_i, lda );
    }

    failed = compare_sgebal( a, a_i, ilo, ilo_i, ihi, ihi_i, scale, scale_i,
                             info, info_i, job, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to sgebal\n" );
    } else {
        printf( "FAILED: row-major high-level interface to sgebal\n" );
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
    if( scale != NULL ) {
        LAPACKE_free( scale );
    }
    if( scale_i != NULL ) {
        LAPACKE_free( scale_i );
    }
    if( scale_save != NULL ) {
        LAPACKE_free( scale_save );
    }

    return 0;
}

/* Auxiliary function: sgebal scalar parameters initialization */
static void init_scalars_sgebal( char *job, lapack_int *n, lapack_int *lda )
{
    *job = 'B';
    *n = 4;
    *lda = 8;

    return;
}

/* Auxiliary functions: sgebal array parameters initialization */
static void init_a( lapack_int size, float *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = 0;
    }
    a[0] = 5.139999866e+000;  /* a[0,0] */
    a[8] = 9.100000262e-001;  /* a[0,1] */
    a[16] = 0.000000000e+000;  /* a[0,2] */
    a[24] = -3.279999924e+001;  /* a[0,3] */
    a[1] = 9.100000262e-001;  /* a[1,0] */
    a[9] = 2.000000030e-001;  /* a[1,1] */
    a[17] = 0.000000000e+000;  /* a[1,2] */
    a[25] = 3.450000000e+001;  /* a[1,3] */
    a[2] = 1.899999976e+000;  /* a[2,0] */
    a[10] = 8.000000119e-001;  /* a[2,1] */
    a[18] = -4.000000060e-001;  /* a[2,2] */
    a[26] = -3.000000000e+000;  /* a[2,3] */
    a[3] = -3.300000131e-001;  /* a[3,0] */
    a[11] = 3.499999940e-001;  /* a[3,1] */
    a[19] = 0.000000000e+000;  /* a[3,2] */
    a[27] = 6.600000262e-001;  /* a[3,3] */
}
static void init_scale( lapack_int size, float *scale ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        scale[i] = 0;
    }
}

/* Auxiliary function: C interface to sgebal results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_sgebal( float *a, float *a_i, lapack_int ilo,
                           lapack_int ilo_i, lapack_int ihi, lapack_int ihi_i,
                           float *scale, float *scale_i, lapack_int info,
                           lapack_int info_i, char job, lapack_int lda,
                           lapack_int n )
{
    lapack_int i;
    int failed = 0;
    if( LAPACKE_lsame( job, 'b' ) || LAPACKE_lsame( job, 'p' ) ||
        LAPACKE_lsame( job, 's' ) ) {
        for( i = 0; i < lda*n; i++ ) {
            failed += compare_floats(a[i],a_i[i]);
        }
    }
    failed += (ilo == ilo_i) ? 0 : 1;
    failed += (ihi == ihi_i) ? 0 : 1;
    for( i = 0; i < n; i++ ) {
        failed += compare_floats(scale[i],scale_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
