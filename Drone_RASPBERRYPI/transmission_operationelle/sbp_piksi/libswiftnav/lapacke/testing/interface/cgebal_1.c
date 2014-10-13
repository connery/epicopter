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
* cgebal_1 is the test program for the C interface to LAPACK
* routine cgebal
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

static void init_scalars_cgebal( char *job, lapack_int *n, lapack_int *lda );
static void init_a( lapack_int size, lapack_complex_float *a );
static void init_scale( lapack_int size, float *scale );
static int compare_cgebal( lapack_complex_float *a, lapack_complex_float *a_i,
                           lapack_int ilo, lapack_int ilo_i, lapack_int ihi,
                           lapack_int ihi_i, float *scale, float *scale_i,
                           lapack_int info, lapack_int info_i, char job,
                           lapack_int lda, lapack_int n );

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
    lapack_complex_float *a = NULL, *a_i = NULL;
    float *scale = NULL, *scale_i = NULL;
    lapack_complex_float *a_save = NULL;
    float *scale_save = NULL;
    lapack_complex_float *a_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_cgebal( &job, &n, &lda );
    lda_r = n+2;
    job_i = job;
    n_i = n;
    lda_i = lda;

    /* Allocate memory for the LAPACK routine arrays */
    a = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    scale = (float *)LAPACKE_malloc( n * sizeof(float) );

    /* Allocate memory for the C interface function arrays */
    a_i = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    scale_i = (float *)LAPACKE_malloc( n * sizeof(float) );

    /* Allocate memory for the backup arrays */
    a_save = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    scale_save = (float *)LAPACKE_malloc( n * sizeof(float) );

    /* Allocate memory for the row-major arrays */
    a_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+2) * sizeof(lapack_complex_float) );

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
    cgebal_( &job, &n, a, &lda, &ilo, &ihi, scale, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale_save[i];
    }
    info_i = LAPACKE_cgebal_work( LAPACK_COL_MAJOR, job_i, n_i, a_i, lda_i,
                                  &ilo_i, &ihi_i, scale_i );

    failed = compare_cgebal( a, a_i, ilo, ilo_i, ihi, ihi_i, scale, scale_i,
                             info, info_i, job, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to cgebal\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to cgebal\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a_save[i];
    }
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale_save[i];
    }
    info_i = LAPACKE_cgebal( LAPACK_COL_MAJOR, job_i, n_i, a_i, lda_i, &ilo_i,
                             &ihi_i, scale_i );

    failed = compare_cgebal( a, a_i, ilo, ilo_i, ihi, ihi_i, scale, scale_i,
                             info, info_i, job, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to cgebal\n" );
    } else {
        printf( "FAILED: column-major high-level interface to cgebal\n" );
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
        LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    }
    info_i = LAPACKE_cgebal_work( LAPACK_ROW_MAJOR, job_i, n_i, a_r, lda_r,
                                  &ilo_i, &ihi_i, scale_i );

    if( LAPACKE_lsame( job, 'b' ) || LAPACKE_lsame( job, 'p' ) ||
        LAPACKE_lsame( job, 's' ) ) {
        LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, n, a_r, n+2, a_i, lda );
    }

    failed = compare_cgebal( a, a_i, ilo, ilo_i, ihi, ihi_i, scale, scale_i,
                             info, info_i, job, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to cgebal\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to cgebal\n" );
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
        LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    }
    info_i = LAPACKE_cgebal( LAPACK_ROW_MAJOR, job_i, n_i, a_r, lda_r, &ilo_i,
                             &ihi_i, scale_i );

    if( LAPACKE_lsame( job, 'b' ) || LAPACKE_lsame( job, 'p' ) ||
        LAPACKE_lsame( job, 's' ) ) {
        LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, n, a_r, n+2, a_i, lda );
    }

    failed = compare_cgebal( a, a_i, ilo, ilo_i, ihi, ihi_i, scale, scale_i,
                             info, info_i, job, lda, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to cgebal\n" );
    } else {
        printf( "FAILED: row-major high-level interface to cgebal\n" );
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

/* Auxiliary function: cgebal scalar parameters initialization */
static void init_scalars_cgebal( char *job, lapack_int *n, lapack_int *lda )
{
    *job = 'B';
    *n = 4;
    *lda = 8;

    return;
}

/* Auxiliary functions: cgebal array parameters initialization */
static void init_a( lapack_int size, lapack_complex_float *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    a[0] = lapack_make_complex_float( 1.500000000e+000, -2.750000000e+000 );
    a[8] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[16] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[24] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[1] = lapack_make_complex_float( -8.060000420e+000, -1.240000010e+000 );
    a[9] = lapack_make_complex_float( -2.500000000e+000, -5.000000000e-001 );
    a[17] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[25] = lapack_make_complex_float( -7.500000000e-001, 5.000000000e-001 );
    a[2] = lapack_make_complex_float( -2.089999914e+000, 7.559999943e+000 );
    a[10] = lapack_make_complex_float( 1.389999986e+000, 3.970000029e+000 );
    a[18] = lapack_make_complex_float( -1.250000000e+000, 7.500000000e-001 );
    a[26] = lapack_make_complex_float( -4.820000172e+000, -5.670000076e+000 );
    a[3] = lapack_make_complex_float( 6.179999828e+000, 9.789999962e+000 );
    a[11] = lapack_make_complex_float( -9.200000167e-001, -6.200000048e-001 );
    a[19] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
    a[27] = lapack_make_complex_float( -2.500000000e+000, -5.000000000e-001 );
}
static void init_scale( lapack_int size, float *scale ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        scale[i] = 0;
    }
}

/* Auxiliary function: C interface to cgebal results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_cgebal( lapack_complex_float *a, lapack_complex_float *a_i,
                           lapack_int ilo, lapack_int ilo_i, lapack_int ihi,
                           lapack_int ihi_i, float *scale, float *scale_i,
                           lapack_int info, lapack_int info_i, char job,
                           lapack_int lda, lapack_int n )
{
    lapack_int i;
    int failed = 0;
    if( LAPACKE_lsame( job, 'b' ) || LAPACKE_lsame( job, 'p' ) ||
        LAPACKE_lsame( job, 's' ) ) {
        for( i = 0; i < lda*n; i++ ) {
            failed += compare_complex_floats(a[i],a_i[i]);
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
