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
* zgebak_1 is the test program for the C interface to LAPACK
* routine zgebak
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

static void init_scalars_zgebak( char *job, char *side, lapack_int *n,
                                 lapack_int *ilo, lapack_int *ihi,
                                 lapack_int *m, lapack_int *ldv );
static void init_scale( lapack_int size, double *scale );
static void init_v( lapack_int size, lapack_complex_double *v );
static int compare_zgebak( lapack_complex_double *v, lapack_complex_double *v_i,
                           lapack_int info, lapack_int info_i, lapack_int ldv,
                           lapack_int m );

int main(void)
{
    /* Local scalars */
    char job, job_i;
    char side, side_i;
    lapack_int n, n_i;
    lapack_int ilo, ilo_i;
    lapack_int ihi, ihi_i;
    lapack_int m, m_i;
    lapack_int ldv, ldv_i;
    lapack_int ldv_r;
    lapack_int info, info_i;
    lapack_int i;
    int failed;

    /* Local arrays */
    double *scale = NULL, *scale_i = NULL;
    lapack_complex_double *v = NULL, *v_i = NULL;
    lapack_complex_double *v_save = NULL;
    lapack_complex_double *v_r = NULL;

    /* Iniitialize the scalar parameters */
    init_scalars_zgebak( &job, &side, &n, &ilo, &ihi, &m, &ldv );
    ldv_r = m+2;
    job_i = job;
    side_i = side;
    n_i = n;
    ilo_i = ilo;
    ihi_i = ihi;
    m_i = m;
    ldv_i = ldv;

    /* Allocate memory for the LAPACK routine arrays */
    scale = (double *)LAPACKE_malloc( n * sizeof(double) );
    v = (lapack_complex_double *)
        LAPACKE_malloc( ldv*m * sizeof(lapack_complex_double) );

    /* Allocate memory for the C interface function arrays */
    scale_i = (double *)LAPACKE_malloc( n * sizeof(double) );
    v_i = (lapack_complex_double *)
        LAPACKE_malloc( ldv*m * sizeof(lapack_complex_double) );

    /* Allocate memory for the backup arrays */
    v_save = (lapack_complex_double *)
        LAPACKE_malloc( ldv*m * sizeof(lapack_complex_double) );

    /* Allocate memory for the row-major arrays */
    v_r = (lapack_complex_double *)
        LAPACKE_malloc( n*(m+2) * sizeof(lapack_complex_double) );

    /* Initialize input arrays */
    init_scale( n, scale );
    init_v( ldv*m, v );

    /* Backup the ouptut arrays */
    for( i = 0; i < ldv*m; i++ ) {
        v_save[i] = v[i];
    }

    /* Call the LAPACK routine */
    zgebak_( &job, &side, &n, &ilo, &ihi, scale, &m, v, &ldv, &info );

    /* Initialize input data, call the column-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale[i];
    }
    for( i = 0; i < ldv*m; i++ ) {
        v_i[i] = v_save[i];
    }
    info_i = LAPACKE_zgebak_work( LAPACK_COL_MAJOR, job_i, side_i, n_i, ilo_i,
                                  ihi_i, scale_i, m_i, v_i, ldv_i );

    failed = compare_zgebak( v, v_i, info, info_i, ldv, m );
    if( failed == 0 ) {
        printf( "PASSED: column-major middle-level interface to zgebak\n" );
    } else {
        printf( "FAILED: column-major middle-level interface to zgebak\n" );
    }

    /* Initialize input data, call the column-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale[i];
    }
    for( i = 0; i < ldv*m; i++ ) {
        v_i[i] = v_save[i];
    }
    info_i = LAPACKE_zgebak( LAPACK_COL_MAJOR, job_i, side_i, n_i, ilo_i, ihi_i,
                             scale_i, m_i, v_i, ldv_i );

    failed = compare_zgebak( v, v_i, info, info_i, ldv, m );
    if( failed == 0 ) {
        printf( "PASSED: column-major high-level interface to zgebak\n" );
    } else {
        printf( "FAILED: column-major high-level interface to zgebak\n" );
    }

    /* Initialize input data, call the row-major middle-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale[i];
    }
    for( i = 0; i < ldv*m; i++ ) {
        v_i[i] = v_save[i];
    }

    LAPACKE_zge_trans( LAPACK_COL_MAJOR, n, m, v_i, ldv, v_r, m+2 );
    info_i = LAPACKE_zgebak_work( LAPACK_ROW_MAJOR, job_i, side_i, n_i, ilo_i,
                                  ihi_i, scale_i, m_i, v_r, ldv_r );

    LAPACKE_zge_trans( LAPACK_ROW_MAJOR, n, m, v_r, m+2, v_i, ldv );

    failed = compare_zgebak( v, v_i, info, info_i, ldv, m );
    if( failed == 0 ) {
        printf( "PASSED: row-major middle-level interface to zgebak\n" );
    } else {
        printf( "FAILED: row-major middle-level interface to zgebak\n" );
    }

    /* Initialize input data, call the row-major high-level
     * interface to LAPACK routine and check the results */
    for( i = 0; i < n; i++ ) {
        scale_i[i] = scale[i];
    }
    for( i = 0; i < ldv*m; i++ ) {
        v_i[i] = v_save[i];
    }

    /* Init row_major arrays */
    LAPACKE_zge_trans( LAPACK_COL_MAJOR, n, m, v_i, ldv, v_r, m+2 );
    info_i = LAPACKE_zgebak( LAPACK_ROW_MAJOR, job_i, side_i, n_i, ilo_i, ihi_i,
                             scale_i, m_i, v_r, ldv_r );

    LAPACKE_zge_trans( LAPACK_ROW_MAJOR, n, m, v_r, m+2, v_i, ldv );

    failed = compare_zgebak( v, v_i, info, info_i, ldv, m );
    if( failed == 0 ) {
        printf( "PASSED: row-major high-level interface to zgebak\n" );
    } else {
        printf( "FAILED: row-major high-level interface to zgebak\n" );
    }

    /* Release memory */
    if( scale != NULL ) {
        LAPACKE_free( scale );
    }
    if( scale_i != NULL ) {
        LAPACKE_free( scale_i );
    }
    if( v != NULL ) {
        LAPACKE_free( v );
    }
    if( v_i != NULL ) {
        LAPACKE_free( v_i );
    }
    if( v_r != NULL ) {
        LAPACKE_free( v_r );
    }
    if( v_save != NULL ) {
        LAPACKE_free( v_save );
    }

    return 0;
}

/* Auxiliary function: zgebak scalar parameters initialization */
static void init_scalars_zgebak( char *job, char *side, lapack_int *n,
                                 lapack_int *ilo, lapack_int *ihi,
                                 lapack_int *m, lapack_int *ldv )
{
    *job = 'B';
    *side = 'R';
    *n = 4;
    *ilo = 2;
    *ihi = 3;
    *m = 4;
    *ldv = 8;

    return;
}

/* Auxiliary functions: zgebak array parameters initialization */
static void init_scale( lapack_int size, double *scale ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        scale[i] = 0;
    }
    scale[0] = 3.00000000000000000e+000;
    scale[1] = 1.00000000000000000e+000;
    scale[2] = 1.00000000000000000e+000;
    scale[3] = 1.00000000000000000e+000;
}
static void init_v( lapack_int size, lapack_complex_double *v ) {
    lapack_int i;
    for( i = 0; i < size; i++ ) {
        v[i] = lapack_make_complex_double( 0.0, 0.0 );
    }
    v[0] = lapack_make_complex_double( 1.00000000000000000e+000,
                                       0.00000000000000000e+000 );
    v[8] = lapack_make_complex_double( 9.88933982312813820e-001,
                                       1.10660176871861960e-002 );
    v[16] = lapack_make_complex_double( 3.66377687451538150e-001,
                                        6.33622312548461910e-001 );
    v[24] = lapack_make_complex_double( 7.76825586133595420e-001,
                                        2.23174413866404380e-001 );
    v[1] = lapack_make_complex_double( 0.00000000000000000e+000,
                                       0.00000000000000000e+000 );
    v[9] = lapack_make_complex_double( -1.01530325593412730e-001,
                                       -2.53824227592024860e-004 );
    v[17] = lapack_make_complex_double( 4.39510052937173770e-001,
                                        -5.40439343831681730e-002 );
    v[25] = lapack_make_complex_double( -2.07193786235892630e-001,
                                        -2.45019888672620730e-001 );
    v[2] = lapack_make_complex_double( 0.00000000000000000e+000,
                                       0.00000000000000000e+000 );
    v[10] = lapack_make_complex_double( 9.34076076494462640e-002,
                                        6.29486051550616070e-002 );
    v[18] = lapack_make_complex_double( 4.38409314020978880e-001,
                                        2.21679100586738650e-001 );
    v[26] = lapack_make_complex_double( -1.18895637414734840e-002,
                                        4.37183961683508200e-001 );
    v[3] = lapack_make_complex_double( 0.00000000000000000e+000,
                                       0.00000000000000000e+000 );
    v[11] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    v[19] = lapack_make_complex_double( 0.00000000000000000e+000,
                                        0.00000000000000000e+000 );
    v[27] = lapack_make_complex_double( 1.45210308488997350e-001,
                                        0.00000000000000000e+000 );
}

/* Auxiliary function: C interface to zgebak results check */
/* Return value: 0 - test is passed, non-zero - test is failed */
static int compare_zgebak( lapack_complex_double *v, lapack_complex_double *v_i,
                           lapack_int info, lapack_int info_i, lapack_int ldv,
                           lapack_int m )
{
    lapack_int i;
    int failed = 0;
    for( i = 0; i < ldv*m; i++ ) {
        failed += compare_complex_doubles(v[i],v_i[i]);
    }
    failed += (info == info_i) ? 0 : 1;
    if( info != 0 || info_i != 0 ) {
        printf( "info=%d, info_i=%d\n",(int)info,(int)info_i );
    }

    return failed;
}
