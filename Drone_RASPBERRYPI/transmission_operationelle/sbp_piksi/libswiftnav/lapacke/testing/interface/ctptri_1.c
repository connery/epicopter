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
* ctptri_1 is the test program for the C interface to LAPACK
* routine ctptri
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

static void init_scalars_ctptri( char *uplo, char *diag, lapack_int *n );
static void init_ap( lapack_int size, lapack_complex_float *ap );
static int compare_ctptri( lapack_complex_float *ap, lapack_complex_float *ap_i,
                           lapack_int info, lapack_int info_i, lapack_int n );

int main(void)
{
    /* Local scalars */
    char uplo, uplo_i;
    char diag, diag_i;
    lapack_int n, n_i;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_complex_float *ap = NULL, *ap_i = NULL;
    lapack_complex_float *ap_save = NULL;
    lapack_complex_float *ap_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_ctptri( &uplo, &diag, &n );
    uplo_i = uplo;
    diag_i = diag;
    n_i = n;

    /* Allocate memory for the LAPACK routine arrays */
    ap = (lapack_complex_float *)
        LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(lapack_complex_float) );

    /* Allocate memory for the C interface function arrays */
    ap_i = (lapack_complex_float *)
        LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(lapack_complex_float) );

    /* Allocate memory for the backup arrays */
    ap_save = (lapack_complex_float *)
        LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(lapack_complex_float) );

    /* Allocate memory for the row-major arrays */
    ap_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+1)/2 * sizeof(lapack_complex_float) );

    /* Initialize input arrays */
    init_ap( (n*(n+1)/2), ap );

    /* Backup the ouptut arrays */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_save[i] = ap[i];
    }

    /* Call the LAPACK routine */
    ctptri_( &uplo, &diag, &n, ap, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap_save[i];
    }
    info_i = LAPACKE_ctptri_work( LAPACK_COL_MAJOR, uplo_i, diag_i, n_i, ap_i );

    failed = compare_ctptri( ap, ap_i, info, info_i, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to ctptri\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to ctptri\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap_save[i];
    }
    info_i = LAPACKE_ctptri( LAPACK_COL_MAJOR, uplo_i, diag_i, n_i, ap_i );

    failed = compare_ctptri( ap, ap_i, info, info_i, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to ctptri\n" );
    } else {
        printf( "FAILED: column-major high-level interface to ctptri\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap_save[i];
    }

    LAPACKE_cpp_trans( LAPACK_COL_MAJOR, uplo, n, ap_i, ap_r );
    info_i = LAPACKE_ctptri_work( LAPACK_ROW_MAJOR, uplo_i, diag_i, n_i, ap_r );

    LAPACKE_cpp_trans( LAPACK_ROW_MAJOR, uplo, n, ap_r, ap_i );

    failed = compare_ctptri( ap, ap_i, info, info_i, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to ctptri\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to ctptri\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap_save[i];
    }

    /* Init row_major arrays */
    LAPACKE_cpp_trans( LAPACK_COL_MAJOR, uplo, n, ap_i, ap_r );
    info_i = LAPACKE_ctptri( LAPACK_ROW_MAJOR, uplo_i, diag_i, n_i, ap_r );

    LAPACKE_cpp_trans( LAPACK_ROW_MAJOR, uplo, n, ap_r, ap_i );

    failed = compare_ctptri( ap, ap_i, info, info_i, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to ctptri\n" );
    } else {
        printf( "FAILED: row-major high-level interface to ctptri\n" );
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

    return 0;
}

/* Auxiliary function: ctptri scalar parameters initialization */
static void init_scalars_ctptri( char *uplo, char *diag, lapack_int *n )
{
    *uplo = 'L';
    *diag = 'N';
    *n = 4;

    return;
}

/* Auxiliary functions: ctptri array parameters initialization */
static void init_ap( lapack_int size, lapack_complex_float *ap ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        ap[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    ap[0] = lapack_make_complex_float( 4.780000210e+000, 4.559999943e+000 );
    ap[1] = lapack_make_complex_float( 2.000000000e+000, -3.000000119e-001 );
    ap[2] = lapack_make_complex_float( 2.890000105e+000, -1.340000033e+000 );
    ap[3] = lapack_make_complex_float( -1.889999986e+000, 1.149999976e+000 );
    ap[4] = lapack_make_complex_float( -4.110000134e+000, 1.250000000e+000 );
    ap[5] = lapack_make_complex_float( 2.359999895e+000, -4.250000000e+000 );
    ap[6] = lapack_make_complex_float( 3.999999911e-002, -3.690000057e+000 );
    ap[7] = lapack_make_complex_float( 4.150000095e+000, 8.000000119e-001 );
    ap[8] = lapack_make_complex_float( -1.999999955e-002, 4.600000083e-001 );
    ap[9] = lapack_make_complex_float( 3.300000131e-001, -2.599999905e-001 );
}

/* Auxiliary function: C interface to ctptri results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_ctptri( lapack_complex_float *ap, lapack_complex_float *ap_i,
                           lapack_int info, lapack_int info_i, lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        failed += compare_complex_floats(ap[i],ap_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
