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
* cupgtr_1 is the test program for the C interface to LAPACK
* routine cupgtr
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

static void init_scalars_cupgtr( char *uplo, lapack_int *n, lapack_int *ldq );
static void init_ap( lapack_int size, lapack_complex_float *ap );
static void init_tau( lapack_int size, lapack_complex_float *tau );
static void init_q( lapack_int size, lapack_complex_float *q );
static void init_work( lapack_int size, lapack_complex_float *work );
static int compare_cupgtr( lapack_complex_float *q, lapack_complex_float *q_i,
                           lapack_int info, lapack_int info_i, lapack_int ldq,
                           lapack_int n );

int main(void)
{
    /* Local scalars */
    char uplo, uplo_i;
    lapack_int n, n_i;
    lapack_int ldq, ldq_i;
    lapack_int ldq_r;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_complex_float *ap = NULL, *ap_i = NULL;
    lapack_complex_float *tau = NULL, *tau_i = NULL;
    lapack_complex_float *q = NULL, *q_i = NULL;
    lapack_complex_float *work = NULL, *work_i = NULL;
    lapack_complex_float *q_save = NULL;
    lapack_complex_float *ap_r = NULL;
    lapack_complex_float *q_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_cupgtr( &uplo, &n, &ldq );
    ldq_r = n+2;
    uplo_i = uplo;
    n_i = n;
    ldq_i = ldq;

    /* Allocate memory for the LAPACK routine arrays */
    ap = (lapack_complex_float *)
        LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(lapack_complex_float) );
    tau = (lapack_complex_float *)
        LAPACKE_malloc( (n-1) * sizeof(lapack_complex_float) );
    q = (lapack_complex_float *)
        LAPACKE_malloc( ldq*n * sizeof(lapack_complex_float) );
    work = (lapack_complex_float *)
        LAPACKE_malloc( (n-1) * sizeof(lapack_complex_float) );

    /* Allocate memory for the C interface function arrays */
    ap_i = (lapack_complex_float *)
        LAPACKE_malloc( ((n*(n+1)/2)) * sizeof(lapack_complex_float) );
    tau_i = (lapack_complex_float *)
        LAPACKE_malloc( (n-1) * sizeof(lapack_complex_float) );
    q_i = (lapack_complex_float *)
        LAPACKE_malloc( ldq*n * sizeof(lapack_complex_float) );
    work_i = (lapack_complex_float *)
        LAPACKE_malloc( (n-1) * sizeof(lapack_complex_float) );

    /* Allocate memory for the backup arrays */
    q_save = (lapack_complex_float *)
        LAPACKE_malloc( ldq*n * sizeof(lapack_complex_float) );

    /* Allocate memory for the row-major arrays */
    ap_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+1)/2 * sizeof(lapack_complex_float) );
    q_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+2) * sizeof(lapack_complex_float) );

    /* Initialize input arrays */
    init_ap( (n*(n+1)/2), ap );
    init_tau( (n-1), tau );
    init_q( ldq*n, q );
    init_work( (n-1), work );

    /* Backup the ouptut arrays */
    for( i = 0; i < ldq*n; i++ ) {
        q_save[i] = q[i];
    }

    /* Call the LAPACK routine */
    cupgtr_( &uplo, &n, ap, tau, q, &ldq, work, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < ldq*n; i++ ) {
        q_i[i] = q_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_cupgtr_work( LAPACK_COL_MAJOR, uplo_i, n_i, ap_i, tau_i,
                                  q_i, ldq_i, work_i );

    failed = compare_cupgtr( q, q_i, info, info_i, ldq, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to cupgtr\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to cupgtr\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < ldq*n; i++ ) {
        q_i[i] = q_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_cupgtr( LAPACK_COL_MAJOR, uplo_i, n_i, ap_i, tau_i, q_i,
                             ldq_i );

    failed = compare_cupgtr( q, q_i, info, info_i, ldq, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to cupgtr\n" );
    } else {
        printf( "FAILED: column-major high-level interface to cupgtr\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < ldq*n; i++ ) {
        q_i[i] = q_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        work_i[i] = work[i];
    }

    LAPACKE_cpp_trans( LAPACK_COL_MAJOR, uplo, n, ap_i, ap_r );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, q_i, ldq, q_r, n+2 );
    info_i = LAPACKE_cupgtr_work( LAPACK_ROW_MAJOR, uplo_i, n_i, ap_r, tau_i,
                                  q_r, ldq_r, work_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, n, q_r, n+2, q_i, ldq );

    failed = compare_cupgtr( q, q_i, info, info_i, ldq, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to cupgtr\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to cupgtr\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < (n*(n+1)/2); i++ ) {
        ap_i[i] = ap[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        tau_i[i] = tau[i];
    }
    for( i = 0; i < ldq*n; i++ ) {
        q_i[i] = q_save[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        work_i[i] = work[i];
    }

    /* Init row_major arrays */
    LAPACKE_cpp_trans( LAPACK_COL_MAJOR, uplo, n, ap_i, ap_r );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, q_i, ldq, q_r, n+2 );
    info_i = LAPACKE_cupgtr( LAPACK_ROW_MAJOR, uplo_i, n_i, ap_r, tau_i, q_r,
                             ldq_r );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, n, q_r, n+2, q_i, ldq );

    failed = compare_cupgtr( q, q_i, info, info_i, ldq, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to cupgtr\n" );
    } else {
        printf( "FAILED: row-major high-level interface to cupgtr\n" );
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
    if( tau != NULL ) {
        LAPACKE_free( tau );
    }
    if( tau_i != NULL ) {
        LAPACKE_free( tau_i );
    }
    if( q != NULL ) {
        LAPACKE_free( q );
    }
    if( q_i != NULL ) {
        LAPACKE_free( q_i );
    }
    if( q_r != NULL ) {
        LAPACKE_free( q_r );
    }
    if( q_save != NULL ) {
        LAPACKE_free( q_save );
    }
    if( work != NULL ) {
        LAPACKE_free( work );
    }
    if( work_i != NULL ) {
        LAPACKE_free( work_i );
    }

    return 0;
}

/* Auxiliary function: cupgtr scalar parameters initialization */
static void init_scalars_cupgtr( char *uplo, lapack_int *n, lapack_int *ldq )
{
    *uplo = 'L';
    *n = 4;
    *ldq = 8;

    return;
}

/* Auxiliary functions: cupgtr array parameters initialization */
static void init_ap( lapack_int size, lapack_complex_float *ap ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        ap[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    ap[0] = lapack_make_complex_float( -2.279999971e+000, 0.000000000e+000 );
    ap[1] = lapack_make_complex_float( -4.338455677e+000, 0.000000000e+000 );
    ap[2] = lapack_make_complex_float( 3.278606534e-001, -1.251226068e-001 );
    ap[3] = lapack_make_complex_float( -1.412565559e-001, -3.666364849e-001 );
    ap[4] = lapack_make_complex_float( -1.284568310e-001, 0.000000000e+000 );
    ap[5] = lapack_make_complex_float( -2.022594690e+000, 0.000000000e+000 );
    ap[6] = lapack_make_complex_float( -3.083218634e-001, 1.763225943e-001 );
    ap[7] = lapack_make_complex_float( -1.665935516e-001, 0.000000000e+000 );
    ap[8] = lapack_make_complex_float( -1.802322745e+000, 0.000000000e+000 );
    ap[9] = lapack_make_complex_float( -1.924949646e+000, 0.000000000e+000 );
}
static void init_tau( lapack_int size, lapack_complex_float *tau ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        tau[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    tau[0] = lapack_make_complex_float( 1.410284281e+000, 4.679084122e-001 );
    tau[1] = lapack_make_complex_float( 1.302420378e+000, 7.853320837e-001 );
    tau[2] = lapack_make_complex_float( 1.093973756e+000, -9.955747128e-001 );
}
static void init_q( lapack_int size, lapack_complex_float *q ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        q[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
}
static void init_work( lapack_int size, lapack_complex_float *work ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        work[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
}

/* Auxiliary function: C interface to cupgtr results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_cupgtr( lapack_complex_float *q, lapack_complex_float *q_i,
                           lapack_int info, lapack_int info_i, lapack_int ldq,
                           lapack_int n )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < ldq*n; i++ ) {
        failed += compare_complex_floats(q[i],q_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
