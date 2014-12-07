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
* dtrevc_1 is the test program for the C interface to LAPACK
* routine dtrevc
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

static void init_scalars_dtrevc( char *side, char *howmny, lapack_int *n,
                                 lapack_int *ldt, lapack_int *ldvl,
                                 lapack_int *ldvr, lapack_int *mm );
static void init_select( lapack_int size, lapack_int *select );
static void init_t( lapack_int size, double *t );
static void init_vl( lapack_int size, double *vl );
static void init_vr( lapack_int size, double *vr );
static void init_work( lapack_int size, double *work );
static int compare_dtrevc( lapack_int *select, lapack_int *select_i, double *vl,
                           double *vl_i, double *vr, double *vr_i, lapack_int m,
                           lapack_int m_i, lapack_int info, lapack_int info_i,
                           char howmny, lapack_int ldvl, lapack_int ldvr,
                           lapack_int mm, lapack_int n, char side );

int main(void)
{
    /* Local scalars */
    char side, side_i;
    char howmny, howmny_i;
    lapack_int n, n_i;
    lapack_int ldt, ldt_i;
    lapack_int ldt_r;
    lapack_int ldvl, ldvl_i;
    lapack_int ldvl_r;
    lapack_int ldvr, ldvr_i;
    lapack_int ldvr_r;
    lapack_int mm, mm_i;
    lapack_int m, m_i;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    lapack_int *select = NULL, *select_i = NULL;
    double *t = NULL, *t_i = NULL;
    double *vl = NULL, *vl_i = NULL;
    double *vr = NULL, *vr_i = NULL;
    double *work = NULL, *work_i = NULL;
    lapack_int *select_save = NULL;
    double *vl_save = NULL;
    double *vr_save = NULL;
    double *t_r = NULL;
    double *vl_r = NULL;
    double *vr_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_dtrevc( &side, &howmny, &n, &ldt, &ldvl, &ldvr, &mm );
    ldt_r = n+2;
    ldvl_r = mm+2;
    ldvr_r = mm+2;
    side_i = side;
    howmny_i = howmny;
    n_i = n;
    ldt_i = ldt;
    ldvl_i = ldvl;
    ldvr_i = ldvr;
    mm_i = mm;

    /* Allocate memory for the LAPACK routine arrays */
    select = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    t = (double *)LAPACKE_malloc( ldt*n * sizeof(double) );
    vl = (double *)LAPACKE_malloc( ldvl*mm * sizeof(double) );
    vr = (double *)LAPACKE_malloc( ldvr*mm * sizeof(double) );
    work = (double *)LAPACKE_malloc( 3*n * sizeof(double) );

    /* Allocate memory for the C interface function arrays */
    select_i = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    t_i = (double *)LAPACKE_malloc( ldt*n * sizeof(double) );
    vl_i = (double *)LAPACKE_malloc( ldvl*mm * sizeof(double) );
    vr_i = (double *)LAPACKE_malloc( ldvr*mm * sizeof(double) );
    work_i = (double *)LAPACKE_malloc( 3*n * sizeof(double) );

    /* Allocate memory for the backup arrays */
    select_save = (lapack_int *)LAPACKE_malloc( n * sizeof(lapack_int) );
    vl_save = (double *)LAPACKE_malloc( ldvl*mm * sizeof(double) );
    vr_save = (double *)LAPACKE_malloc( ldvr*mm * sizeof(double) );

    /* Allocate memory for the row-major arrays */
    t_r = (double *)LAPACKE_malloc( n*(n+2) * sizeof(double) );
    vl_r = (double *)LAPACKE_malloc( n*(mm+2) * sizeof(double) );
    vr_r = (double *)LAPACKE_malloc( n*(mm+2) * sizeof(double) );

    /* Initialize input arrays */
    init_select( n, select );
    init_t( ldt*n, t );
    init_vl( ldvl*mm, vl );
    init_vr( ldvr*mm, vr );
    init_work( 3*n, work );

    /* Backup the ouptut arrays */
    for( i = 0; i < n; i++ ) {
        select_save[i] = select[i];
    }
    for( i = 0; i < ldvl*mm; i++ ) {
        vl_save[i] = vl[i];
    }
    for( i = 0; i < ldvr*mm; i++ ) {
        vr_save[i] = vr[i];
    }

    /* Call the LAPACK routine */
    dtrevc_( &side, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr, &mm, &m,
             work, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        select_i[i] = select_save[i];
    }
    for( i = 0; i < ldt*n; i++ ) {
        t_i[i] = t[i];
    }
    for( i = 0; i < ldvl*mm; i++ ) {
        vl_i[i] = vl_save[i];
    }
    for( i = 0; i < ldvr*mm; i++ ) {
        vr_i[i] = vr_save[i];
    }
    for( i = 0; i < 3*n; i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_dtrevc_work( LAPACK_COL_MAJOR, side_i, howmny_i, select_i,
                                  n_i, t_i, ldt_i, vl_i, ldvl_i, vr_i, ldvr_i,
                                  mm_i, &m_i, work_i );

    failed = compare_dtrevc( select, select_i, vl, vl_i, vr, vr_i, m, m_i, info,
                             info_i, howmny, ldvl, ldvr, mm, n, side );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to dtrevc\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to dtrevc\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        select_i[i] = select_save[i];
    }
    for( i = 0; i < ldt*n; i++ ) {
        t_i[i] = t[i];
    }
    for( i = 0; i < ldvl*mm; i++ ) {
        vl_i[i] = vl_save[i];
    }
    for( i = 0; i < ldvr*mm; i++ ) {
        vr_i[i] = vr_save[i];
    }
    for( i = 0; i < 3*n; i++ ) {
        work_i[i] = work[i];
    }
    info_i = LAPACKE_dtrevc( LAPACK_COL_MAJOR, side_i, howmny_i, select_i, n_i,
                             t_i, ldt_i, vl_i, ldvl_i, vr_i, ldvr_i, mm_i,
                             &m_i );

    failed = compare_dtrevc( select, select_i, vl, vl_i, vr, vr_i, m, m_i, info,
                             info_i, howmny, ldvl, ldvr, mm, n, side );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to dtrevc\n" );
    } else {
        printf( "FAILED: column-major high-level interface to dtrevc\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        select_i[i] = select_save[i];
    }
    for( i = 0; i < ldt*n; i++ ) {
        t_i[i] = t[i];
    }
    for( i = 0; i < ldvl*mm; i++ ) {
        vl_i[i] = vl_save[i];
    }
    for( i = 0; i < ldvr*mm; i++ ) {
        vr_i[i] = vr_save[i];
    }
    for( i = 0; i < 3*n; i++ ) {
        work_i[i] = work[i];
    }

    LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, n, t_i, ldt, t_r, n+2 );
    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'l' ) ) {
        LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, mm, vl_i, ldvl, vl_r, mm+2 );
    }
    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'r' ) ) {
        LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, mm, vr_i, ldvr, vr_r, mm+2 );
    }
    info_i = LAPACKE_dtrevc_work( LAPACK_ROW_MAJOR, side_i, howmny_i, select_i,
                                  n_i, t_r, ldt_r, vl_r, ldvl_r, vr_r, ldvr_r,
                                  mm_i, &m_i, work_i );

    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'l' ) ) {
        LAPACKE_dge_trans( LAPACK_ROW_MAJOR, n, mm, vl_r, mm+2, vl_i, ldvl );
    }
    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'r' ) ) {
        LAPACKE_dge_trans( LAPACK_ROW_MAJOR, n, mm, vr_r, mm+2, vr_i, ldvr );
    }

    failed = compare_dtrevc( select, select_i, vl, vl_i, vr, vr_i, m, m_i, info,
                             info_i, howmny, ldvl, ldvr, mm, n, side );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to dtrevc\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to dtrevc\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        select_i[i] = select_save[i];
    }
    for( i = 0; i < ldt*n; i++ ) {
        t_i[i] = t[i];
    }
    for( i = 0; i < ldvl*mm; i++ ) {
        vl_i[i] = vl_save[i];
    }
    for( i = 0; i < ldvr*mm; i++ ) {
        vr_i[i] = vr_save[i];
    }
    for( i = 0; i < 3*n; i++ ) {
        work_i[i] = work[i];
    }

    /* Init row_major arrays */
    LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, n, t_i, ldt, t_r, n+2 );
    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'l' ) ) {
        LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, mm, vl_i, ldvl, vl_r, mm+2 );
    }
    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'r' ) ) {
        LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, mm, vr_i, ldvr, vr_r, mm+2 );
    }
    info_i = LAPACKE_dtrevc( LAPACK_ROW_MAJOR, side_i, howmny_i, select_i, n_i,
                             t_r, ldt_r, vl_r, ldvl_r, vr_r, ldvr_r, mm_i,
                             &m_i );

    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'l' ) ) {
        LAPACKE_dge_trans( LAPACK_ROW_MAJOR, n, mm, vl_r, mm+2, vl_i, ldvl );
    }
    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'r' ) ) {
        LAPACKE_dge_trans( LAPACK_ROW_MAJOR, n, mm, vr_r, mm+2, vr_i, ldvr );
    }

    failed = compare_dtrevc( select, select_i, vl, vl_i, vr, vr_i, m, m_i, info,
                             info_i, howmny, ldvl, ldvr, mm, n, side );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to dtrevc\n" );
    } else {
        printf( "FAILED: row-major high-level interface to dtrevc\n" );
    }

    /* Release memory */
    if( select != NULL ) {
        LAPACKE_free( select );
    }
    if( select_i != NULL ) {
        LAPACKE_free( select_i );
    }
    if( select_save != NULL ) {
        LAPACKE_free( select_save );
    }
    if( t != NULL ) {
        LAPACKE_free( t );
    }
    if( t_i != NULL ) {
        LAPACKE_free( t_i );
    }
    if( t_r != NULL ) {
        LAPACKE_free( t_r );
    }
    if( vl != NULL ) {
        LAPACKE_free( vl );
    }
    if( vl_i != NULL ) {
        LAPACKE_free( vl_i );
    }
    if( vl_r != NULL ) {
        LAPACKE_free( vl_r );
    }
    if( vl_save != NULL ) {
        LAPACKE_free( vl_save );
    }
    if( vr != NULL ) {
        LAPACKE_free( vr );
    }
    if( vr_i != NULL ) {
        LAPACKE_free( vr_i );
    }
    if( vr_r != NULL ) {
        LAPACKE_free( vr_r );
    }
    if( vr_save != NULL ) {
        LAPACKE_free( vr_save );
    }
    if( work != NULL ) {
        LAPACKE_free( work );
    }
    if( work_i != NULL ) {
        LAPACKE_free( work_i );
    }

    return 0;
}

/* Auxiliary function: dtrevc scalar parameters initialization */
static void init_scalars_dtrevc( char *side, char *howmny, lapack_int *n,
                                 lapack_int *ldt, lapack_int *ldvl,
                                 lapack_int *ldvr, lapack_int *mm )
{
    *side = 'R';
    *howmny = 'B';
    *n = 4;
    *ldt = 8;
    *ldvl = 1;
    *ldvr = 8;
    *mm = 4;

    return;
}

/* Auxiliary functions: dtrevc array parameters initialization */
static void init_select( lapack_int size, lapack_int *select ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        select[i] = 0;
    }
    select[0] = 0;
    select[1] = 0;
    select[2] = 0;
    select[3] = 0;
}
static void init_t( lapack_int size, double *t ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        t[i] = 0;
    }
    t[0] = -4.00000000000000020e-001;  /* t[0,0] */
    t[8] = 5.51321443098590100e-001;  /* t[0,1] */
    t[16] = -5.37870326205712330e+000;  /* t[0,2] */
    t[24] = -6.40434195566693100e+000;  /* t[0,3] */
    t[1] = 0.00000000000000000e+000;  /* t[1,0] */
    t[9] = -4.02078135020595080e+000;  /* t[1,1] */
    t[17] = -9.76012875813315190e-001;  /* t[1,2] */
    t[25] = 1.79171581755631100e+000;  /* t[1,3] */
    t[2] = 0.00000000000000000e+000;  /* t[2,0] */
    t[10] = 0.00000000000000000e+000;  /* t[2,1] */
    t[18] = 3.01355719437426560e+000;  /* t[2,2] */
    t[26] = 5.06368981440549760e-001;  /* t[2,3] */
    t[3] = 0.00000000000000000e+000;  /* t[3,0] */
    t[11] = 0.00000000000000000e+000;  /* t[3,1] */
    t[19] = 0.00000000000000000e+000;  /* t[3,2] */
    t[27] = 7.00722415583168790e+000;  /* t[3,3] */
}
static void init_vl( lapack_int size, double *vl ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        vl[i] = 0;
    }
    vl[0] = 0.00000000000000000e+000;  /* vl[0,0] */
    vl[1] = 0.00000000000000000e+000;  /* vl[0,1] */
    vl[2] = 0.00000000000000000e+000;  /* vl[0,2] */
    vl[3] = 0.00000000000000000e+000;  /* vl[0,3] */
    vl[1] = 0.00000000000000000e+000;  /* vl[1,0] */
    vl[2] = 0.00000000000000000e+000;  /* vl[1,1] */
    vl[3] = 0.00000000000000000e+000;  /* vl[1,2] */
    vl[2] = 0.00000000000000000e+000;  /* vl[2,0] */
    vl[3] = 0.00000000000000000e+000;  /* vl[2,1] */
    vl[3] = 0.00000000000000000e+000;  /* vl[3,0] */
}
static void init_vr( lapack_int size, double *vr ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        vr[i] = 0;
    }
    vr[0] = 1.00000000000000000e+000;  /* vr[0,0] */
    vr[8] = 0.00000000000000000e+000;  /* vr[0,1] */
    vr[16] = 0.00000000000000000e+000;  /* vr[0,2] */
    vr[24] = 0.00000000000000000e+000;  /* vr[0,3] */
    vr[1] = 0.00000000000000000e+000;  /* vr[1,0] */
    vr[9] = 7.05885498968063300e-001;  /* vr[1,1] */
    vr[17] = -6.93609763007558720e-001;  /* vr[1,2] */
    vr[25] = 1.43635507473627600e-001;  /* vr[1,3] */
    vr[2] = 0.00000000000000000e+000;  /* vr[2,0] */
    vr[10] = -3.46594279043188120e-001;  /* vr[2,1] */
    vr[18] = -5.15071446985306380e-001;  /* vr[2,2] */
    vr[26] = -7.83947581305660220e-001;  /* vr[2,3] */
    vr[3] = 0.00000000000000000e+000;  /* vr[3,0] */
    vr[11] = -6.17736244752677520e-001;  /* vr[3,1] */
    vr[19] = -5.03593984436928150e-001;  /* vr[3,2] */
    vr[27] = 6.03982641106347030e-001;  /* vr[3,3] */
}
static void init_work( lapack_int size, double *work ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        work[i] = 0;
    }
}

/* Auxiliary function: C interface to dtrevc results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_dtrevc( lapack_int *select, lapack_int *select_i, double *vl,
                           double *vl_i, double *vr, double *vr_i, lapack_int m,
                           lapack_int m_i, lapack_int info, lapack_int info_i,
                           char howmny, lapack_int ldvl, lapack_int ldvr,
                           lapack_int mm, lapack_int n, char side )
{
    lapack_int i;
    int failed = 0;
    if( LAPACKE_lsame( howmny, 's' ) ) {
        for( i = 0; i < n; i++ ) {
            failed += (select[i] == select_i[i]) ? 0 : 1;
        }
    }
    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'l' ) ) {
        for( i = 0; i < ldvl*mm; i++ ) {
            failed += compare_doubles(vl[i],vl_i[i]);
        }
    }
    if( LAPACKE_lsame( side, 'b' ) || LAPACKE_lsame( side, 'r' ) ) {
        for( i = 0; i < ldvr*mm; i++ ) {
            failed += compare_doubles(vr[i],vr_i[i]);
        }
    }
    failed += (m == m_i) ? 0 : 1;
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
