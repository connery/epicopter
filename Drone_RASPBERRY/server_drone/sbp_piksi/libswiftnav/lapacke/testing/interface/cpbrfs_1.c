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
* cpbrfs_1 is the test program for the C interface to LAPACK
* routine cpbrfs
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

static void init_scalars_cpbrfs( char *uplo, lapack_int *n, lapack_int *kd,
                                 lapack_int *nrhs, lapack_int *ldab,
                                 lapack_int *ldafb, lapack_int *ldb,
                                 lapack_int *ldx );
static void init_ab( lapack_int size, lapack_complex_float *ab );
static void init_afb( lapack_int size, lapack_complex_float *afb );
static void init_b( lapack_int size, lapack_complex_float *b );
static void init_x( lapack_int size, lapack_complex_float *x );
static void init_ferr( lapack_int size, float *ferr );
static void init_berr( lapack_int size, float *berr );
static void init_work( lapack_int size, lapack_complex_float *work );
static void init_rwork( lapack_int size, float *rwork );
static int compare_cpbrfs( lapack_complex_float *x, lapack_complex_float *x_i,
                           float *ferr, float *ferr_i, float *berr,
                           float *berr_i, lapack_int info, lapack_int info_i,
                           lapack_int ldx, lapack_int nrhs );

int main(void)
{
    /* Local scalars */
    char uplo, uplo_i;
    lapack_int n, n_i;
    lapack_int kd, kd_i;
    lapack_int nrhs, nrhs_i;
    lapack_int ldab, ldab_i;
    lapack_int ldab_r;
    lapack_int ldafb, ldafb_i;
    lapack_int ldafb_r;
    lapack_int ldb, ldb_i;
    lapack_int ldb_r;
    lapack_int ldx, ldx_i;
    lapack_int ldx_r;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_complex_float *ab = NULL, *ab_i = NULL;
    lapack_complex_float *afb = NULL, *afb_i = NULL;
    lapack_complex_float *b = NULL, *b_i = NULL;
    lapack_complex_float *x = NULL, *x_i = NULL;
    float *ferr = NULL, *ferr_i = NULL;
    float *berr = NULL, *berr_i = NULL;
    lapack_complex_float *work = NULL, *work_i = NULL;
    float *rwork = NULL, *rwork_i = NULL;
    lapack_complex_float *x_save = NULL;
    float *ferr_save = NULL;
    float *berr_save = NULL;
    lapack_complex_float *ab_r = NULL;
    lapack_complex_float *afb_r = NULL;
    lapack_complex_float *b_r = NULL;
    lapack_complex_float *x_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_cpbrfs( &uplo, &n, &kd, &nrhs, &ldab, &ldafb, &ldb, &ldx );
    ldab_r = n+2;
    ldafb_r = n+2;
    ldb_r = nrhs+2;
    ldx_r = nrhs+2;
    uplo_i = uplo;
    n_i = n;
    kd_i = kd;
    nrhs_i = nrhs;
    ldab_i = ldab;
    ldafb_i = ldafb;
    ldb_i = ldb;
    ldx_i = ldx;

    /* Allocate memory for the LAPACK routine arrays */
    ab = (lapack_complex_float *)
        LAPACKE_malloc( ldab*n * sizeof(lapack_complex_float) );
    afb = (lapack_complex_float *)
        LAPACKE_malloc( ldafb*n * sizeof(lapack_complex_float) );
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
    ab_i = (lapack_complex_float *)
        LAPACKE_malloc( ldab*n * sizeof(lapack_complex_float) );
    afb_i = (lapack_complex_float *)
        LAPACKE_malloc( ldafb*n * sizeof(lapack_complex_float) );
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
    ab_r = (lapack_complex_float *)
        LAPACKE_malloc( (kd+1)*(n+2) * sizeof(lapack_complex_float) );
    afb_r = (lapack_complex_float *)
        LAPACKE_malloc( (kd+1)*(n+2) * sizeof(lapack_complex_float) );
    b_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(nrhs+2) * sizeof(lapack_complex_float) );
    x_r = (lapack_complex_float *)
        LAPACKE_malloc( n*(nrhs+2) * sizeof(lapack_complex_float) );

    /* Initialize input arrays */
    init_ab( ldab*n, ab );
    init_afb( ldafb*n, afb );
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
    cpbrfs_( &uplo, &n, &kd, &nrhs, ab, &ldab, afb, &ldafb, b, &ldb, x, &ldx,
             ferr, berr, work, rwork, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < ldab*n; i++ ) {
        ab_i[i] = ab[i];
    }
    for( i = 0; i < ldafb*n; i++ ) {
        afb_i[i] = afb[i];
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
    info_i = LAPACKE_cpbrfs_work( LAPACK_COL_MAJOR, uplo_i, n_i, kd_i, nrhs_i,
                                  ab_i, ldab_i, afb_i, ldafb_i, b_i, ldb_i, x_i,
                                  ldx_i, ferr_i, berr_i, work_i, rwork_i );

    failed = compare_cpbrfs( x, x_i, ferr, ferr_i, berr, berr_i, info, info_i,
                             ldx, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to cpbrfs\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to cpbrfs\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < ldab*n; i++ ) {
        ab_i[i] = ab[i];
    }
    for( i = 0; i < ldafb*n; i++ ) {
        afb_i[i] = afb[i];
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
    info_i = LAPACKE_cpbrfs( LAPACK_COL_MAJOR, uplo_i, n_i, kd_i, nrhs_i, ab_i,
                             ldab_i, afb_i, ldafb_i, b_i, ldb_i, x_i, ldx_i,
                             ferr_i, berr_i );

    failed = compare_cpbrfs( x, x_i, ferr, ferr_i, berr, berr_i, info, info_i,
                             ldx, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to cpbrfs\n" );
    } else {
        printf( "FAILED: column-major high-level interface to cpbrfs\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < ldab*n; i++ ) {
        ab_i[i] = ab[i];
    }
    for( i = 0; i < ldafb*n; i++ ) {
        afb_i[i] = afb[i];
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

    LAPACKE_cge_trans( LAPACK_COL_MAJOR, kd+1, n, ab_i, ldab, ab_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, kd+1, n, afb_i, ldafb, afb_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, nrhs, b_i, ldb, b_r, nrhs+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, nrhs, x_i, ldx, x_r, nrhs+2 );
    info_i = LAPACKE_cpbrfs_work( LAPACK_ROW_MAJOR, uplo_i, n_i, kd_i, nrhs_i,
                                  ab_r, ldab_r, afb_r, ldafb_r, b_r, ldb_r, x_r,
                                  ldx_r, ferr_i, berr_i, work_i, rwork_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, nrhs, x_r, nrhs+2, x_i, ldx );

    failed = compare_cpbrfs( x, x_i, ferr, ferr_i, berr, berr_i, info, info_i,
                             ldx, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to cpbrfs\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to cpbrfs\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < ldab*n; i++ ) {
        ab_i[i] = ab[i];
    }
    for( i = 0; i < ldafb*n; i++ ) {
        afb_i[i] = afb[i];
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
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, kd+1, n, ab_i, ldab, ab_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, kd+1, n, afb_i, ldafb, afb_r, n+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, nrhs, b_i, ldb, b_r, nrhs+2 );
    LAPACKE_cge_trans( LAPACK_COL_MAJOR, n, nrhs, x_i, ldx, x_r, nrhs+2 );
    info_i = LAPACKE_cpbrfs( LAPACK_ROW_MAJOR, uplo_i, n_i, kd_i, nrhs_i, ab_r,
                             ldab_r, afb_r, ldafb_r, b_r, ldb_r, x_r, ldx_r,
                             ferr_i, berr_i );

    LAPACKE_cge_trans( LAPACK_ROW_MAJOR, n, nrhs, x_r, nrhs+2, x_i, ldx );

    failed = compare_cpbrfs( x, x_i, ferr, ferr_i, berr, berr_i, info, info_i,
                             ldx, nrhs );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to cpbrfs\n" );
    } else {
        printf( "FAILED: row-major high-level interface to cpbrfs\n" );
    }

    /* Release memory */
    if( ab != NULL ) {
        LAPACKE_free( ab );
    }
    if( ab_i != NULL ) {
        LAPACKE_free( ab_i );
    }
    if( ab_r != NULL ) {
        LAPACKE_free( ab_r );
    }
    if( afb != NULL ) {
        LAPACKE_free( afb );
    }
    if( afb_i != NULL ) {
        LAPACKE_free( afb_i );
    }
    if( afb_r != NULL ) {
        LAPACKE_free( afb_r );
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

/* Auxiliary function: cpbrfs scalar parameters initialization */
static void init_scalars_cpbrfs( char *uplo, lapack_int *n, lapack_int *kd,
                                 lapack_int *nrhs, lapack_int *ldab,
                                 lapack_int *ldafb, lapack_int *ldb,
                                 lapack_int *ldx )
{
    *uplo = 'L';
    *n = 4;
    *kd = 1;
    *nrhs = 2;
    *ldab = 9;
    *ldafb = 9;
    *ldb = 8;
    *ldx = 8;

    return;
}

/* Auxiliary functions: cpbrfs array parameters initialization */
static void init_ab( lapack_int size, lapack_complex_float *ab ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        ab[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    ab[0] = lapack_make_complex_float( 9.390000343e+000, 0.000000000e+000 );
    ab[9] = lapack_make_complex_float( 1.690000057e+000, 0.000000000e+000 );
    ab[18] = lapack_make_complex_float( 2.650000095e+000, 0.000000000e+000 );
    ab[27] = lapack_make_complex_float( 2.170000076e+000, 0.000000000e+000 );
    ab[1] = lapack_make_complex_float( 1.080000043e+000, 1.730000019e+000 );
    ab[10] = lapack_make_complex_float( -3.999999911e-002, -2.899999917e-001 );
    ab[19] = lapack_make_complex_float( -3.300000131e-001, -2.240000010e+000 );
    ab[28] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
}
static void init_afb( lapack_int size, lapack_complex_float *afb ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        afb[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    afb[0] = lapack_make_complex_float( 3.064310789e+000, 0.000000000e+000 );
    afb[9] = lapack_make_complex_float( 1.116714001e+000, 0.000000000e+000 );
    afb[18] = lapack_make_complex_float( 1.606635571e+000, 0.000000000e+000 );
    afb[27] = lapack_make_complex_float( 4.289152622e-001, 0.000000000e+000 );
    afb[1] = lapack_make_complex_float( 3.524446785e-001, 5.645641685e-001 );
    afb[10] = lapack_make_complex_float( -3.581937775e-002, -2.596904933e-001 );
    afb[19] = lapack_make_complex_float( -2.053981870e-001, -1.394217849e+000 );
    afb[28] = lapack_make_complex_float( 0.000000000e+000, 0.000000000e+000 );
}
static void init_b( lapack_int size, lapack_complex_float *b ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        b[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    b[0] = lapack_make_complex_float( -1.242000008e+001, 6.841999817e+001 );
    b[8] = lapack_make_complex_float( 5.429999924e+001, -5.656000137e+001 );
    b[1] = lapack_make_complex_float( -9.930000305e+000, 8.799999952e-001 );
    b[9] = lapack_make_complex_float( 1.831999969e+001, 4.760000229e+000 );
    b[2] = lapack_make_complex_float( -2.729999924e+001, -9.999999776e-003 );
    b[10] = lapack_make_complex_float( -4.400000095e+000, 9.970000267e+000 );
    b[3] = lapack_make_complex_float( 5.309999943e+000, 2.362999916e+001 );
    b[11] = lapack_make_complex_float( 9.430000305e+000, 1.409999967e+000 );
}
static void init_x( lapack_int size, lapack_complex_float *x ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        x[i] = lapack_make_complex_float( 0.0f, 0.0f );
    }
    x[0] = lapack_make_complex_float( -1.000000834e+000, 7.999998569e+000 );
    x[8] = lapack_make_complex_float( 5.000000000e+000, -6.000000000e+000 );
    x[1] = lapack_make_complex_float( 2.000000477e+000, -2.999995708e+000 );
    x[9] = lapack_make_complex_float( 1.999998093e+000, 2.999998331e+000 );
    x[2] = lapack_make_complex_float( -4.000012875e+000, -4.999993324e+000 );
    x[10] = lapack_make_complex_float( -7.999992847e+000, 3.999997377e+000 );
    x[3] = lapack_make_complex_float( 6.999990940e+000, 5.999987125e+000 );
    x[11] = lapack_make_complex_float( -9.999961257e-001, -6.999992847e+000 );
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

/* Auxiliary function: C interface to cpbrfs results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_cpbrfs( lapack_complex_float *x, lapack_complex_float *x_i,
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
