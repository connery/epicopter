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
* cgerfs_1 is the test program for the C interface to LAPACK
* routine cgerfs
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

static void init_scalars_cgerfs( char *trans, lapack_int *n, lapack_int *nrhs,
                                 lapack_int *lda, lapack_int *ldaf,
                                 lapack_int *ldb, lapack_int *ldx );
static void init_a( lapack_int size, lapack_complex_float *a );
static void init_af( lapack_int size, lapack_complex_float *af );
static void init_ipiv( lapack_int size, lapack_int *ipiv );
static void init_b( lapack_int size, lapack_complex_float *b );
static void init_x( lapack_int size, lapack_complex_float *x );
static void init_ferr( lapack_int size, float *ferr );
static void init_berr( lapack_int size, float *berr );
static void init_work( lapack_int size, lapack_complex_float *work );
static void init_rwork( lapack_int size, float *rwork );
static int compare_cgerfs( lapack_complex_float *x, lapack_complex_float *x_i,
                           float *ferr, float *ferr_i, float *berr,
                           float *berr_i, lapack_int info, lapack_int info_i,
                           lapack_int ldx, lapack_int nrhs );

int main(void)
{
    /* Local scalars */
    char trans, trans_i;
    lapack_int n, n_i;
    lapack_int nrhs, nrhs_i;
    lapack_int lda, lda_i;
    lapack_int lda_r;
    lapack_int ldaf, ldaf_i;
    lapack_int ldaf_r;
    lapack_int ldb, ldb_i;
    lapack_int ldb_r;
    lapack_int ldx, ldx_i;
    lapack_int ldx_r;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_complex_float *a = NULL, *a_i = NULL;
    lapack_complex_float *af = NULL, *af_i = NULL;
    lapack_int *ipiv = NULL, *ipiv_i = NULL;
    lapack_complex_float *b = NULL, *b_i = NULL;
    lapack_complex_float *x = NULL, *x_i = NULL;
    float *ferr = NULL, *ferr_i = NULL;
    float *berr = NULL, *berr_i = NULL;
    lapack_complex_float *work = NULL, *work_i = NULL;
    float *rwork = NULL, *rwork_i = NULL;
    lapack_complex_float *x_save = NULL;
    float *ferr_save = NULL;
    float *berr_save = NULL;
    lapack_complex_float *a_r = NULL;
    lapack_complex_float *af_r = NULL;
    lapack_complex_float *b_r = NULL;
    lapack_complex_float *x_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_cgerfs( &trans, &n, &nrhs, &lda, &ldaf, &ldb, &ldx );
    lda_r = n+2;
    ldaf_r = n+2;
    ldb_r = nrhs+2;
    ldx_r = nrhs+2;
    trans_i = trans;
    n_i = n;
    nrhs_i = nrhs;
    lda_i = lda;
    ldaf_i = ldaf;
    ldb_i = ldb;
    ldx_i = ldx;

    /* Allocate memory for the LAPACK routine arrays */
    a = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    af = (lapack_complex_float *)
        LAPACKE_malloc( ldaf*n * sizeof(lapack_complex_float) );
    ipiv = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    b = (lapack_complex_float *)
        LAPACKE_malloc( ldb*nrhs * sizeof(lapack_complex_float) );
    x = (lapack_complex_float *)
        LAPACKE_malloc( ldx*nrhs * sizeof(lapack_complex_float) );
    ferr = (float *)LAPACKE_malloc( nrhs * sizeof(float) );
    berr = (float *)LAPACKE_malloc( nrhs * sizeof(float) );
    work = (lapack_complex_float *)
        LAPACKE_malloc( 2*n * sizeof(lapack_complex_float) );
    rwork = (float *)LAPACKE_malloc( n * sizeof(float) );

    /* Allocate memory for the C interface function arrays */
    a_i = (lapack_complex_float *)
        LAPACKE_malloc( lda*n * sizeof(lapack_complex_float) );
    af_i = (lapack_complex_float *)
        LAPACKE_malloc( ldaf*n * sizeof(lapack_complex_float) );
    ipiv_i = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    b_i = (lapack_complex_float *)
        LAPACKE_malloc( ldb*nrhs * sizeof(lapack_complex_float) );
    x_i = (lapack_complex_float *)
        LAPACKE_malloc( ldx*nrhs * sizeof(lapack_complex_float) );
    ferr_i = (float *)LAPACKE_malloc( nrhs * sizeof(float) );
    berr_i = (float *)LAPACKE_malloc( nrhs * sizeof(float) );
    work_i = (lapack_complex_float *)
        LAPACKE_malloc( 2*n * sizeof(lapack_complex_float) );
    rwork_i = (float *)LAPACKE_malloc( n * sizeof(float) );

    /* Allocate memory for the backup arrays */
    x_save = (lapack_complex_float *)
        LAPACKE_malloc( ldx*nrhs * sizeof(lapack_complex_float) );
    ferr_save = (float *)LAPACKE_malloc( nrhs * sizeof(float) );
    berr_save = (float *)LAPACKE_malloc( nrhs * sizeof(float) );

    /* Allocate memory for the row-major arrays */
    a_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+2) * sizeof(lapack_complex_float) );
    af_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(n+2) * sizeof(lapack_complex_float) );
    b_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(nrhs+2) * sizeof(lapack_complex_float) );
    x_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(nrhs+2) * sizeof(lapack_complex_float) );

    /* Initialize input arrays */
    init_a( lda*n, a );
    init_af( ldaf*n, af );
    init_ipiv( n, ipiv );
    init_b( ldb*nrhs, b );
    init_x( ldx*nrhs, x );
    init_ferr( nrhs, ferr );
    init_berr( nrhs, berr );
    init_work( 2*n, work );
    init_rwork( n, rwork );

    /* Backup the ouptut arrays */
    for( i = 0; i < ldx*nrhs; i++ ) {
        x_save[i] = x[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        ferr_save[i] = ferr[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        berr_save[i] = berr[i];
    }

    /* Call the LAPACK routine */
    cgerfs_( &trans, &n, &nrhs, a, &lda, af, &ldaf, ipiv, b, &ldb, x, &ldx,
             ferr, berr, work, rwork, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a[i];
    }
    for( i = 0; i < ldaf*n; i++ ) {
        af_i[i] = af[i];
    }
    for( i = 0; i < n; i++ ) {
        ipiv_i[i] = ipiv[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b[i];
    }
    for( i = 0; i < ldx*nrhs; i++ ) {
        x_i[i] = x_save[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        ferr_i[i] = ferr_save[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        berr_i[i] = berr_save[i];
    }
    for( i = 0; i < 2*n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < n; i++ ) {
        rwork_i[i] = rwork[i];
    }
    info_i = LAPACKE_cgerfs_work( LAPACK_COL_MAJOR, trans_i, n_i, nrhs_i, a_i,
                                  lda_i, af_i, ldaf_i, ipiv_i, b_i, ldb_i, x_i,
                                  ldx_i, ferr_i, berr_i, work_i, rwork_i );

    failed = compare_cgerfs( x, x_i, ferr, ferr_i, berr, berr_i, info, info_i,
                             ldx, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to cgerfs\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to cgerfs\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a[i];
    }
    for( i = 0; i < ldaf*n; i++ ) {
        af_i[i] = af[i];
    }
    for( i = 0; i < n; i++ ) {
        ipiv_i[i] = ipiv[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b[i];
    }
    for( i = 0; i < ldx*nrhs; i++ ) {
        x_i[i] = x_save[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        ferr_i[i] = ferr_save[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        berr_i[i] = berr_save[i];
    }
    for( i = 0; i < 2*n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < n; i++ ) {
        rwork_i[i] = rwork[i];
    }
    info_i = LAPACKE_cgerfs( LAPACK_COL_MAJOR, trans_i, n_i, nrhs_i, a_i, lda_i,
                             af_i, ldaf_i, ipiv_i, b_i, ldb_i, x_i, ldx_i,
                             ferr_i, berr_i );

    failed = compare_cgerfs( x, x_i, ferr, ferr_i, berr, berr_i, info, info_i,
                             ldx, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to cgerfs\n" );
    } else {
        printf( "FAILED: column-major high-level interface to cgerfs\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a[i];
    }
    for( i = 0; i < ldaf*n; i++ ) {
        af_i[i] = af[i];
    }
    for( i = 0; i < n; i++ ) {
        ipiv_i[i] = ipiv[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b[i];
    }
    for( i = 0; i < ldx*nrhs; i++ ) {
        x_i[i] = x_save[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        ferr_i[i] = ferr_save[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        berr_i[i] = berr_save[i];
    }
    for( i = 0; i < 2*n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < n; i++ ) {
        rwork_i[i] = rwork[i];
    }

    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, af_i, ldaf, af_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, nrhs, b_i, ldb, b_r, nrhs+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, nrhs, x_i, ldx, x_r, nrhs+2 );
    info_i = LAPACKE_cgerfs_work( LAPACK_ROW_MAJOR, trans_i, n_i, nrhs_i, a_r,
                                  lda_r, af_r, ldaf_r, ipiv_i, b_r, ldb_r, x_r,
                                  ldx_r, ferr_i, berr_i, work_i, rwork_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, nrhs, x_r, nrhs+2, x_i, ldx );

    failed = compare_cgerfs( x, x_i, ferr, ferr_i, berr, berr_i, info, info_i,
                             ldx, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to cgerfs\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to cgerfs\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < lda*n; i++ ) {
        a_i[i] = a[i];
    }
    for( i = 0; i < ldaf*n; i++ ) {
        af_i[i] = af[i];
    }
    for( i = 0; i < n; i++ ) {
        ipiv_i[i] = ipiv[i];
    }
    for( i = 0; i < ldb*nrhs; i++ ) {
        b_i[i] = b[i];
    }
    for( i = 0; i < ldx*nrhs; i++ ) {
        x_i[i] = x_save[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        ferr_i[i] = ferr_save[i];
    }
    for( i = 0; i < nrhs; i++ ) {
        berr_i[i] = berr_save[i];
    }
    for( i = 0; i < 2*n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < n; i++ ) {
        rwork_i[i] = rwork[i];
    }

    /* Init row_major arrays */
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, a_i, lda, a_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, n, af_i, ldaf, af_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, nrhs, b_i, ldb, b_r, nrhs+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, nrhs, x_i, ldx, x_r, nrhs+2 );
    info_i = LAPACKE_cgerfs( LAPACK_ROW_MAJOR, trans_i, n_i, nrhs_i, a_r, lda_r,
                             af_r, ldaf_r, ipiv_i, b_r, ldb_r, x_r, ldx_r,
                             ferr_i, berr_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, nrhs, x_r, nrhs+2, x_i, ldx );

    failed = compare_cgerfs( x, x_i, ferr, ferr_i, berr, berr_i, info, info_i,
                             ldx, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to cgerfs\n" );
    } else {
        printf( "FAILED: row-major high-level interface to cgerfs\n" );
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
    if( af != NULL ) {
        LAPACKE_free( af );
    }
    if( af_i != NULL ) {
        LAPACKE_free( af_i );
    }
    if( af_r != NULL ) {
        LAPACKE_free( af_r );
    }
    if( ipiv != NULL ) {
        LAPACKE_free( ipiv );
    }
    if( ipiv_i != NULL ) {
        LAPACKE_free( ipiv_i );
    }
    if( b != NULL ) {
        LAPACKE_free( b );
    }
    if( b_i != NULL ) {
        LAPACKE_free( b_i );
    }
    if( b_r != NULL ) {
        LAPACKE_free( b_r );
    }
    if( x != NULL ) {
        LAPACKE_free( x );
    }
    if( x_i != NULL ) {
        LAPACKE_free( x_i );
    }
    if( x_r != NULL ) {
        LAPACKE_free( x_r );
    }
    if( x_save != NULL ) {
        LAPACKE_free( x_save );
    }
    if( ferr != NULL ) {
        LAPACKE_free( ferr );
    }
    if( ferr_i != NULL ) {
        LAPACKE_free( ferr_i );
    }
    if( ferr_save != NULL ) {
        LAPACKE_free( ferr_save );
    }
    if( berr != NULL ) {
        LAPACKE_free( berr );
    }
    if( berr_i != NULL ) {
        LAPACKE_free( berr_i );
    }
    if( berr_save != NULL ) {
        LAPACKE_free( berr_save );
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

/* Auxiliary function: cgerfs scalar parameters initialization */
static void init_scalars_cgerfs( char *trans, lapack_int *n, lapack_int *nrhs,
                                 lapack_int *lda, lapack_int *ldaf,
                                 lapack_int *ldb, lapack_int *ldx )
{
    *trans = 'N';
    *n = 4;
    *nrhs = 2;
    *lda = 8;
    *ldaf = 8;
    *ldb = 8;
    *ldx = 8;

    return;
}

/* Auxiliary functions: cgerfs array parameters initialization */
static void init_a( lapack_int size, lapack_complex_float *a ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        a[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    a[0] = lapack_make_complex_float( -1.340000033e+000, 2.549999952e+000 );
    a[8] = lapack_make_complex_float( 2.800000012e-001, 3.170000076e+000 );
    a[16] = lapack_make_complex_float( -6.389999866e+000, -2.200000048e+000 );
    a[24] = lapack_make_complex_float( 7.200000286e-001, -9.200000167e-001 );
    a[1] = lapack_make_complex_float( -1.700000018e-001, -1.409999967e+000 );
    a[9] = lapack_make_complex_float( 3.309999943e+000, -1.500000060e-001 );
    a[17] = lapack_make_complex_float( -1.500000060e-001, 1.340000033e+000 );
    a[25] = lapack_make_complex_float( 1.289999962e+000, 1.379999995e+000 );
    a[2] = lapack_make_complex_float( -3.289999962e+000, -2.390000105e+000 );
    a[10] = lapack_make_complex_float( -1.909999967e+000, 4.420000076e+000 );
    a[18] = lapack_make_complex_float( -1.400000006e-001, -1.350000024e+000 );
    a[26] = lapack_make_complex_float( 1.720000029e+000, 1.350000024e+000 );
    a[3] = lapack_make_complex_float( 2.410000086e+000, 3.899999857e-001 );
    a[11] = lapack_make_complex_float( -5.600000024e-001, 1.470000029e+000 );
    a[19] = lapack_make_complex_float( -8.299999833e-001, -6.899999976e-001 );
    a[27] = lapack_make_complex_float( -1.960000038e+000, 6.700000167e-001 );
}
static void init_af( lapack_int size, lapack_complex_float *af ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        af[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    af[0] = lapack_make_complex_float( -3.289999962e+000, -2.390000105e+000 );
    af[8] = lapack_make_complex_float( -1.909999967e+000, 4.420000076e+000 );
    af[16] = lapack_make_complex_float( -1.400000006e-001, -1.350000024e+000 );
    af[24] = lapack_make_complex_float( 1.720000029e+000, 1.350000024e+000 );
    af[1] = lapack_make_complex_float( 2.376120239e-001, 2.559596300e-001 );
    af[9] = lapack_make_complex_float( 4.895180702e+000, -7.113622427e-001 );
    af[17] = lapack_make_complex_float( -4.622798264e-001, 1.696610570e+000 );
    af[25] = lapack_make_complex_float( 1.226852775e+000, 6.189731956e-001 );
    af[2] = lapack_make_complex_float( -1.019521058e-001, -7.010135055e-001 );
    af[10] = lapack_make_complex_float( -6.691496968e-001, 3.688699007e-001 );
    af[18] = lapack_make_complex_float( -5.141410828e+000, -1.129969597e+000 );
    af[26] = lapack_make_complex_float( 9.982581139e-001, 3.850151896e-001 );
    af[3] = lapack_make_complex_float( -5.358546376e-001, 2.707273066e-001 );
    af[11] = lapack_make_complex_float( -2.040217221e-001, 8.601181507e-001 );
    af[19] = lapack_make_complex_float( 8.233040571e-003, 1.210636795e-001 );
    af[27] = lapack_make_complex_float( 1.482392550e-001, -1.252242178e-001 );
}
static void init_ipiv( lapack_int size, lapack_int *ipiv ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        ipiv[i] = 0;
    }
    ipiv[0] = 3;
    ipiv[1] = 2;
    ipiv[2] = 3;
    ipiv[3] = 4;
}
static void init_b( lapack_int size, lapack_complex_float *b ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        b[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    b[0] = lapack_make_complex_float( 2.626000023e+001, 5.177999878e+001 );
    b[8] = lapack_make_complex_float( 3.131999969e+001, -6.699999809e+000 );
    b[1] = lapack_make_complex_float( 6.429999828e+000, -8.680000305e+000 );
    b[9] = lapack_make_complex_float( 1.585999966e+001, -1.419999957e+000 );
    b[2] = lapack_make_complex_float( -5.750000000e+000, 2.530999947e+001 );
    b[10] = lapack_make_complex_float( -2.150000095e+000, 3.019000053e+001 );
    b[3] = lapack_make_complex_float( 1.159999967e+000, 2.569999933e+000 );
    b[11] = lapack_make_complex_float( -2.559999943e+000, 7.550000191e+000 );
}
static void init_x( lapack_int size, lapack_complex_float *x ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        x[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    x[0] = lapack_make_complex_float( 9.999898672e-001, 9.999940395e-001 );
    x[8] = lapack_make_complex_float( -1.000002265e+000, -1.999994636e+000 );
    x[1] = lapack_make_complex_float( 1.999998808e+000, -2.999995947e+000 );
    x[9] = lapack_make_complex_float( 5.000001907e+000, 1.000000238e+000 );
    x[2] = lapack_make_complex_float( -4.000001431e+000, -5.000002861e+000 );
    x[10] = lapack_make_complex_float( -3.000001431e+000, 4.000000954e+000 );
    x[3] = lapack_make_complex_float( -9.536743164e-006, 5.999988079e+000 );
    x[11] = lapack_make_complex_float( 1.999994278e+000, -2.999994516e+000 );
}
static void init_ferr( lapack_int size, float *ferr ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        ferr[i] = 0;
    }
}
static void init_berr( lapack_int size, float *berr ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        berr[i] = 0;
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

/* Auxiliary function: C interface to cgerfs results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_cgerfs( lapack_complex_float *x, lapack_complex_float *x_i,
                           float *ferr, float *ferr_i, float *berr,
                           float *berr_i, lapack_int info, lapack_int info_i,
                           lapack_int ldx, lapack_int nrhs )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < ldx*nrhs; i++ ) {
        failed += compare_complex_floats(x[i],x_i[i]);
    }
    for( i = 0; i < nrhs; i++ ) {
        failed += compare_floats(ferr[i],ferr_i[i]);
    }
    for( i = 0; i < nrhs; i++ ) {
        failed += compare_floats(berr[i],berr_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
