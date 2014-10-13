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
* sstebz_2 is the test program for the C interface to LAPACK
* routine sstebz
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

static void init_scalars_sstebz( char *range, char *order, lapack_int *n,
                                 float *vl, float *vu, lapack_int *il,
                                 lapack_int *iu, float *abstol );
static void init_d( lapack_int size, float *d );
static void init_e( lapack_int size, float *e );
static void init_w( lapack_int size, float *w );
static void init_iblock( lapack_int size, lapack_int *iblock );
static void init_isplit( lapack_int size, lapack_int *isplit );
static void init_work( lapack_int size, float *work );
static void init_iwork( lapack_int size, lapack_int *iwork );
static int compare_sstebz( lapack_int m, lapack_int m_i, lapack_int nsplit,
                           lapack_int nsplit_i, float *w, float *w_i,
                           lapack_int *iblock, lapack_int *iblock_i,
                           lapack_int *isplit, lapack_int *isplit_i,
                           lapack_int info, lapack_int info_i, lapack_int n );

int main(void)
{
    /* Local scalars */
    char range, range_i;
    char order, order_i;
    lapack_int n, n_i;
    float vl, vl_i;
    float vu, vu_i;
    lapack_int il, il_i;
    lapack_int iu, iu_i;
    float abstol, abstol_i;
    lapack_int m, m_i;
    lapack_int nsplit, nsplit_i;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    float *d = NULL, *d_i = NULL;
    float *e = NULL, *e_i = NULL;
    float *w = NULL, *w_i = NULL;
    lapack_int *iblock = NULL, *iblock_i = NULL;
    lapack_int *isplit = NULL, *isplit_i = NULL;
    float *work = NULL, *work_i = NULL;
    lapack_int *iwork = NULL, *iwork_i = NULL;
    float *w_save = NULL;
    lapack_int *iblock_save = NULL;
    lapack_int *isplit_save = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_sstebz( &range, &order, &n, &vl, &vu, &il, &iu, &abstol );
    range_i = range;
    order_i = order;
    n_i = n;
    vl_i = vl;
    vu_i = vu;
    il_i = il;
    iu_i = iu;
    abstol_i = abstol;

    /* Allocate memory for the LAPACK routine arrays */
    d = (float *)LAPACKE_malloc( n * sizeof(float) );
    e = (float *)LAPACKE_malloc( (n-1) * sizeof(float) );
    w = (float *)LAPACKE_malloc( n * sizeof(float) );
    iblock = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    isplit = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    work = (float *)LAPACKE_malloc( 4*n * sizeof(float) );
    iwork = (lapack_int *)LAPACKE_malloc( 3*n * sizeof(lapack_int) );

    /* Allocate memory for the C interface function arrays */
    d_i = (float *)LAPACKE_malloc( n * sizeof(float) );
    e_i = (float *)LAPACKE_malloc( (n-1) * sizeof(float) );
    w_i = (float *)LAPACKE_malloc( n * sizeof(float) );
    iblock_i = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    isplit_i = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    work_i = (float *)LAPACKE_malloc( 4*n * sizeof(float) );
    iwork_i = (lapack_int *)LAPACKE_malloc( 3*n * sizeof(lapack_int) );

    /* Allocate memory for the backup arrays */
    w_save = (float *)LAPACKE_malloc( n * sizeof(float) );
    iblock_save = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    isplit_save = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );

    /* Allocate memory for the row-major arrays */

    /* Initialize input arrays */
    init_d( n, d );
    init_e( (n-1), e );
    init_w( n, w );
    init_iblock( n, iblock );
    init_isplit( n, isplit );
    init_work( 4*n, work );
    init_iwork( 3*n, iwork );

    /* Backup the ouptut arrays */
    for( i = 0; i < n; i++ ) {
        w_save[i] = w[i];
    }
    for( i = 0; i < n; i++ ) {
        iblock_save[i] = iblock[i];
    }
    for( i = 0; i < n; i++ ) {
        isplit_save[i] = isplit[i];
    }

    /* Call the LAPACK routine */
    sstebz_( &range, &order, &n, &vl, &vu, &il, &iu, &abstol, d, e, &m, &nsplit,
             w, iblock, isplit, work, iwork, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        d_i[i] = d[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        e_i[i] = e[i];
    }
    for( i = 0; i < n; i++ ) {
        w_i[i] = w_save[i];
    }
    for( i = 0; i < n; i++ ) {
        iblock_i[i] = iblock_save[i];
    }
    for( i = 0; i < n; i++ ) {
        isplit_i[i] = isplit_save[i];
    }
    for( i = 0; i < 4*n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < 3*n; i++ ) {
        iwork_i[i] = iwork[i];
    }
    info_i = LAPACKE_sstebz_work( range_i, order_i, n_i, vl_i, vu_i, il_i, iu_i,
                                  abstol_i, d_i, e_i, &m_i, &nsplit_i, w_i,
                                  iblock_i, isplit_i, work_i, iwork_i );

    failed = compare_sstebz( m, m_i, nsplit, nsplit_i, w, w_i, iblock, iblock_i,
                             isplit, isplit_i, info, info_i, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to sstebz\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to sstebz\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        d_i[i] = d[i];
    }
    for( i = 0; i < (n-1); i++ ) {
        e_i[i] = e[i];
    }
    for( i = 0; i < n; i++ ) {
        w_i[i] = w_save[i];
    }
    for( i = 0; i < n; i++ ) {
        iblock_i[i] = iblock_save[i];
    }
    for( i = 0; i < n; i++ ) {
        isplit_i[i] = isplit_save[i];
    }
    for( i = 0; i < 4*n; i++ ) {
        work_i[i] = work[i];
    }
    for( i = 0; i < 3*n; i++ ) {
        iwork_i[i] = iwork[i];
    }
    info_i = LAPACKE_sstebz( range_i, order_i, n_i, vl_i, vu_i, il_i, iu_i,
                             abstol_i, d_i, e_i, &m_i, &nsplit_i, w_i, iblock_i,
                             isplit_i );

    failed = compare_sstebz( m, m_i, nsplit, nsplit_i, w, w_i, iblock, iblock_i,
                             isplit, isplit_i, info, info_i, n );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to sstebz\n" );
    } else {
        printf( "FAILED: column-major high-level interface to sstebz\n" );
    }

    failed = compare_sstebz( m, m_i, nsplit, nsplit_i, w, w_i, iblock, iblock_i,
                             isplit, isplit_i, info, info_i, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to sstebz\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to sstebz\n" );
    }

    failed = compare_sstebz( m, m_i, nsplit, nsplit_i, w, w_i, iblock, iblock_i,
                             isplit, isplit_i, info, info_i, n );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to sstebz\n" );
    } else {
        printf( "FAILED: row-major high-level interface to sstebz\n" );
    }

    /* Release memory */
    if( d != NULL ) {
        LAPACKE_free( d );
    }
    if( d_i != NULL ) {
        LAPACKE_free( d_i );
    }
    if( e != NULL ) {
        LAPACKE_free( e );
    }
    if( e_i != NULL ) {
        LAPACKE_free( e_i );
    }
    if( w != NULL ) {
        LAPACKE_free( w );
    }
    if( w_i != NULL ) {
        LAPACKE_free( w_i );
    }
    if( w_save != NULL ) {
        LAPACKE_free( w_save );
    }
    if( iblock != NULL ) {
        LAPACKE_free( iblock );
    }
    if( iblock_i != NULL ) {
        LAPACKE_free( iblock_i );
    }
    if( iblock_save != NULL ) {
        LAPACKE_free( iblock_save );
    }
    if( isplit != NULL ) {
        LAPACKE_free( isplit );
    }
    if( isplit_i != NULL ) {
        LAPACKE_free( isplit_i );
    }
    if( isplit_save != NULL ) {
        LAPACKE_free( isplit_save );
    }
    if( work != NULL ) {
        LAPACKE_free( work );
    }
    if( work_i != NULL ) {
        LAPACKE_free( work_i );
    }
    if( iwork != NULL ) {
        LAPACKE_free( iwork );
    }
    if( iwork_i != NULL ) {
        LAPACKE_free( iwork_i );
    }

    return 0;
}

/* Auxiliary function: sstebz scalar parameters initialization */
static void init_scalars_sstebz( char *range, char *order, lapack_int *n,
                                 float *vl, float *vu, lapack_int *il,
                                 lapack_int *iu, float *abstol )
{
    *range = 'I';
    *order = 'B';
    *n = 4;
    *vl = 0.000000000e+000;
    *vu = 0.000000000e+000;
    *il = 1;
    *iu = 2;
    *abstol = 0.000000000e+000;

    return;
}

/* Auxiliary functions: sstebz array parameters initialization */
static void init_d( lapack_int size, float *d ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        d[i] = 0;
    }
    d[0] = -2.279999971e+000;
    d[1] = -1.284568310e-001;
    d[2] = -1.665935516e-001;
    d[3] = -1.924949646e+000;
}
static void init_e( lapack_int size, float *e ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        e[i] = 0;
    }
    e[0] = -4.338455677e+000;
    e[1] = -2.022594690e+000;
    e[2] = -1.802322745e+000;
}
static void init_w( lapack_int size, float *w ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        w[i] = 0;
    }
}
static void init_iblock( lapack_int size, lapack_int *iblock ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        iblock[i] = 0;
    }
}
static void init_isplit( lapack_int size, lapack_int *isplit ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        isplit[i] = 0;
    }
}
static void init_work( lapack_int size, float *work ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        work[i] = 0;
    }
}
static void init_iwork( lapack_int size, lapack_int *iwork ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        iwork[i] = 0;
    }
}

/* Auxiliary function: C interface to sstebz results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_sstebz( lapack_int m, lapack_int m_i, lapack_int nsplit,
                           lapack_int nsplit_i, float *w, float *w_i,
                           lapack_int *iblock, lapack_int *iblock_i,
                           lapack_int *isplit, lapack_int *isplit_i,
                           lapack_int info, lapack_int info_i, lapack_int n )
{
    lapack_int i;
    int failed = 0;
    failed += (m == m_i) ? 0 : 1;
    failed += (nsplit == nsplit_i) ? 0 : 1;
    for( i = 0; i < n; i++ ) {
        failed += compare_floats(w[i],w_i[i]);
    }
    for( i = 0; i < n; i++ ) {
        failed += (iblock[i] == iblock_i[i]) ? 0 : 1;
    }
    for( i = 0; i < n; i++ ) {
        failed += (isplit[i] == isplit_i[i]) ? 0 : 1;
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
