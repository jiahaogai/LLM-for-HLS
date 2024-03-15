

/* DGEMM  Performs one of the matrix-matrix operations
  C := alpha*A*B + beta*C,
  where alpha and beta are scalars, A is a general rectangular matrix
  and B and C are general rectangular matrices.
  
  Arguments
  =========
  
  TRANSA - CHARACTER*1.
           On entry, TRANSA specifies the form of op( A ) to be used in
           the matrix multiplication as follows:
               
   TRANSA = 'N' or 'N'   A is transposed, but not conjugated.
  
   TRANSA = 'C' or 'C'   A is conjugated and transposed.
   
   TRANSA is a  blas character variable
   
   TRANSB - CHARACTER*1.
           On entry, TRANSB specifies the form of op( B ) to be used in
           the matrix multiplication as follows:
               
   TRANSB = 'N' or 'N'   B is transposed, but not conjugated.
  
   TRANSB = 'C' or 'C'   B is conjugated and transposed.
   
   TRANSB is a  blas character variable
   
   M      - INTEGER.
           On entry,  M  specifies  the number  of rows  of  the  matrix
           op( A )  and of the  matrix  C.  M  must  be at least  zero.
           Unchanged on exit.
   
   N      - INTEGER.
           On entry,  N  specifies the number  of columns of the matrix
           op( A ) and the number of columns of the matrix  C. N must be
           at least zero.
           Unchanged on exit.
   
   K      - INTEGER.
           On entry,  K  specifies  the number of columns of the matrix
           op( B ) and the number of rows of the matrix op( A ). K must
           be at least  zero.
           Unchanged on exit.
   
   ALPHA  - DOUBLE PRECISION.
           On entry, ALPHA specifies the scalar alpha.
           Unchanged on exit.
   
   A      - DOUBLE PRECISION array of DIMENSION ( LDA, ka ), where ka is
           k  when  TRANSA = 'N' or 'n',  and is  m  otherwise.
           Before entry with  TRANSA = 'N' or 'n',  the leading  m by k
           part of the array  A  must contain the matrix  A,  otherwise
           the leading  k by m  part of the array  A  must contain  the
           matrix A.
           Unchanged on exit.
   
   LDA    - INTEGER.
           On entry, LDA specifies the first dimension of A as declared
           in the calling (sub) program. When  TRANSA = 'N' or 'n' then
           LDA must be at least  max( 1, m ), otherwise  LDA must be at
           least  max( 1, k ).
           Unchanged on exit.
   
   B      - DOUBLE PRECISION array of DIMENSION ( LDB, kb ), where kb is
           n  when  TRANSB = 'N' or 'n',  and is  k  otherwise.
           Before entry with  TRANSB = 'N' or 'n',  the leading  k by n
           part of the array  B  must contain the matrix  B,  otherwise
           the leading  n by k  part of the array  B  must contain  the
           matrix B.
           Unchanged on exit.
   
   LDB    - INTEGER.
           On entry, LDB specifies the first dimension of B as declared
           in the calling (sub) program. When  TRANSB = 'N' or 'n' then
           LDB must be at least  max( 1, k ), otherwise  LDB must be at
           least  max( 1, n ).
           Unchanged on exit.
   
   BETA   - DOUBLE PRECISION.
           On entry,  BETA  specifies the scalar  beta.  When  BETA  is
           supplied as zero then C need not be set on input.
           Unchanged on exit.
   
   C      - DOUBLE PRECISION array of DIMENSION ( LDC, n ).
           Before entry, the leading  m by n  part of the array  C must
           contain the matrix  C,  except when  beta  is zero, in which
           case C need not be set on entry.
           On exit, the array  C  is overwritten by the  m by n  matrix
           ( alpha*op( A )*op( B ) + beta*C ).
   
   LDC    - INTEGER.
           On entry, LDC specifies the first dimension of C as declared
           in the calling (sub) program. LDC must be at least
           max( 1, m ).
           Unchanged on exit.
   
   Further Details
   ===============
   
   Level 3 Blas routine.   
   
   -- Written on 8-February-1989.   
   Jack Dongarra, Argonne National Laboratory.   
   Iain Duff, AERE Harwell.   
   Jeremy Du Croz, Numerical Algorithms Group Ltd.   
   Sven Hammarling, Numerical Algorithms Group Ltd.   
   
   -- Modified 8-Nov-93 to set CL3JUMP = .TRUE. if SCALEA = SCALEB = 1.   
   --   SJH, 1993-10.   
   ----------------------------------------------------------------------- */
   /* Table of constant values */
   
   static doublecomplex c_b1 = {0.0,0.0} ;
   static doublecomplex c_b2 = {1.0,0.0} ;
   static double alpha = 1.0;
   static double beta = 1.0;
   
#include "dgemm.h"
   /* System generated locals */
   int a_dim1, a_offset, b_dim1, b_offset, c_dim1, c_offset, i__1, i__2;
   double d__1;
   
   /* Local variables */
   static int k, m1, n1, n2, n1b, n2b;
   static double beta1;
   static double s1, s2, t1, t2;
   static double a11, a12, a21, a22, b11, b12, b21, b22;
   static double tmp;
   static doublecomplex z__1;
   static double r1, d12;
   static double d22;
   static double r2, d21;
   static double t128;
   static double s228;
   static double t228;
   static double s216;
   static double d11;
   static double s116;
   static double s128;
   static double s12;
   static double s22;
   static double s16;
   static double s26;
   static double s18;
   static double s28;
   static double s61;
   static double s62;
   static double s64;
   static double s68;
   static double s82;
   static double s86;
   static double s88;
   static double s112;
   static double s1168;
   static double s1282;
   static double s1286;
   static double s144;
   static double s1472;
   static double s1632;
   static double s168;
   static double s1824;
   static double s1872;
   static double s192;
   static double s1984;
   static double s2048;
   static double s2112;
   static double s2144;
   static double s2176;
   static double s2224;
   static double s2256;
   static double s2288;
   static double s2352;
   static double s2400;
   static double s2464;
   static double s2528;
   static double s254