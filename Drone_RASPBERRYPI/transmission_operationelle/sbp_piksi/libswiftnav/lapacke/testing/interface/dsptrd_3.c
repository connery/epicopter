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
* dsptrd_3 is the test program for the C interface to LAPACK
* routine dsptrd
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

static void init_scalars_dsptrd( char *uplo, lapack_int *n );
static void init_ap( lapack_int size, double *ap );
static void init_d( lapack_int size, double *d );
static void init_e( lapack_int size, double *e );
static void init_tau( lapack_int size, double *tau );
static int compare_dsptrd( double *ap, double *ap_i, double *d, double *d_i,
                           double *e, double *e_i, double *tau, double *tau_i,
                           lapack_int info, lapack_int info_i, lapack_int n );

int main(void)
{
    /* Local scalars */
    char uplo, uplo_i;
    lapack_int n, n_i;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    double *ap = NULL, *ap_i = NULL;
    double *d = NULL, *d_i = NULL;
    double *e = NULL, *e_i = NULL;
    double *tau = NULL, *tau_i = NULL;
    double *ap_save = NULL;
    double *d_save = NULL;
    double *e_save = NULL;
    double *tau_save = NULL;
    double *ap_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_dsptrd( &uplo, &n );
    uplo_i = uplo;
    n_i = n;

    /* Allocate memory for the LAPACK routine arrays */
    ap = (double *)LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(double) );
    d = (double *)LAPACKE_malloc( n * sizeof(double) );
    e = (double *)LAPACKE_malloc( (n-1) * sizeof(double) );
    tau = (double *)LAPACKE_malloc( (n-1) * sizeof(double) );

    /* Allocate memory for the C interface function arrays */
    ap_i = (double *)LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(double) );
    d_i = (double *)LAPACKE_malloc( n * sizeof(double) );
    e_i = (double *)LAPACKE_malloc( (n-1) * sizeof(double) );
    tau_i = (double *)LAPACKE_malloc( (n-1) * sizeof(double) );

    /* Allocate memory for the backup arrays */
    ap_save = (double *)LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(double) );
    d_save = (double *)LAPACKE_malloc( n * sizeof(double) );
    e_save = (double *)LAPACKE_malloc( (n-1) * sizeof(double) );
    tau_save = (double *)LAPACKE_malloc( (n-1) * sizeof(double) );

    /* Allocate memory for the row-major arrays */
    ap_r = (double *)LAPACKE_malloc( n*(n+1)/2 * sizeof(double) );

    /* Initialize input arrays */
    init_ap( (n*(n+1)/2), ap );
    init_d( n, d );
    init_e( (n-1), e );
    init_tau( (n-1), tau );

    /* Backup the ouptut arrays */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_save[i] = ap[i];
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
    dsptrd_( &uplo, &n, ap, d, e, tau, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap_save[i];
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
    info_i = LAPACKE_dsptrd_work( LAPACK_COL_MAJOR, uplo_i, n_i, ap_i, d_i, e_i,
                                  tau_i );

    failed = compare_dsptrd( ap, ap_i, d, d_i, e, e_i, tau, tau_i, info, info_i,
                             n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to dsptrd\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to dsptrd\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap_save[i];
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
    info_i = LAPACKE_dsptrd( LAPACK_COL_MAJOR, uplo_i, n_i, ap_i, d_i, e_i,
                             tau_i );

    failed = compare_dsptrd( ap, ap_i, d, d_i, e, e_i, tau, tau_i, info, info_i,
                             n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to dsptrd\n" );
    } else {
        printf( "FAILED: column-major high-level interface to dsptrd\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap_save[i];
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

    LAPACKE_dpp_trans( LAPACK_COL_MAJOR, uplo, n, ap_i, ap_r );
    info_i = LAPACKE_dsptrd_work( LAPACK_ROW_MAJOR, uplo_i, n_i, ap_r, d_i, e_i,
                                  tau_i );

    LAPACKE_dpp_trans( LAPACK_ROW_MAJOR, uplo, n, ap_r, ap_i );

    failed = compare_dsptrd( ap, ap_i, d, d_i, e, e_i, tau, tau_i, info, info_i,
                             n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to dsptrd\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to dsptrd\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap_save[i];
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

    /* Init row_major arrays */
    LAPACKE_dpp_trans( LAPACK_COL_MAJOR, uplo, n, ap_i, ap_r );
    info_i = LAPACKE_dsptrd( LAPACK_ROW_MAJOR, uplo_i, n_i, ap_r, d_i, e_i,
                             tau_i );

    LAPACKE_dpp_trans( LAPACK_ROW_MAJOR, uplo, n, ap_r, ap_i );

    failed = compare_dsptrd( ap, ap_i, d, d_i, e, e_i, tau, tau_i, info, info_i,
                             n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to dsptrd\n" );
    } else {
        printf( "FAILED: row-major high-level interface to dsptrd\n" );
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
    if( ap_save != NULL ) {
        LAPACKE_free( ap_save );
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

    return 0;
}

/* Auxiliary function: dsptrd scalar parameters initialization */
static void init_scalars_dsptrd( char *uplo, lapack_int *n )
{
    *uplo = 'L';
    *n = 4;

    return;
}

/* Auxiliary functions: dsptrd array parameters initialization */
static void init_ap( lapack_int size, double *ap ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        ap[i] = 0;
    }
    ap[0] = 5.76923076923076890e-002;
    ap[1] = 1.70393118107254630e-001;
    ap[2] = 2.94994937709884000e-001;
    ap[3] = -6.02408803967131700e-001;
    ap[4] = 2.26765799256505530e-001;
    ap[5] = 8.66732278893501460e-001;
    ap[6] = -6.15902621315513990e-001;
    ap[7] = -5.00011600337520040e-002;
    ap[8] = 3.97218700415568730e-001;
    ap[9] = -1.68754520903792620e+000;
}
static void init_d( lapack_int size, double *d ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        d[i] = 0;
    }
}
static void init_e( lapack_int size, double *e ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        e[i] = 0;
    }
}
static void init_tau( lapack_int size, double *tau ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        tau[i] = 0;
    }
}

/* Auxiliary function: C interface to dsptrd results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_dsptrd( double *ap, double *ap_i, double *d, double *d_i,
                           double *e, double *e_i, double *tau, double *tau_i,
                           lapack_int info, lapack_int info_i, lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        failed += compare_doubles(ap[i],ap_i[i]);
    }
    for( i = 0; i < n; i++ ) {
        failed += compare_doubles(d[i],d_i[i]);
    }
    for( i = 0; i < (n-1); i++ ) {
        failed += compare_doubles(e[i],e_i[i]);
    }
    for( i = 0; i < (n-1); i++ ) {
        failed += compare_doubles(tau[i],tau_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
