

5. Don't automatically distribute this loop: `#pragma ACCEL DISTRIBUTE FACTOR=1`

6. Don't automatically parallelize this loop: `#pragma ACCEL PARALLEL FACTOR=auto{1}`

7. Don't automatically parallelize this loop: `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}`
//#pragma ACCEL PIPELINE auto{flatten}

//#pragma ACCEL TILE FACTOR=auto{4}

//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
/* Configurations */
#define TILE_FACTOR 4
#define PARA_L2 1
#define PARA_L1 16
#define PARA_L0 1
#define PARA_INPUT_L 1
#define PARA_OUTPUT_L 1

#include <math.h>
#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif

struct lp_struct_t {
  double A[120][120];
  double x[120];
  double b[120];
  double b_orig[120];
  double b_error[120];
};

void kernel_gemm(double m1[120][120],double m2[120][120],double prod[120][120])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 120; j++) {
      lp_1:
      double sum = (double )0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L2}
      for (k = 0; k < 120; k++) {
        lp_2:
        sum += m1[i][k] * m2[k][j];
      }
      prod[i][j] = sum;
    }
  }
//#pragma endscop
}

void kernel_gemm_orig(double m1[120][120],double m2[120][120],double prod[120][120])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 120; j++) {
      lp_3:
      double sum = (double )0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L0}
      for (k = 0; k < 120; k++) {
        lp_4:
        sum += m1[i][k] * m2[k][j];
      }
      prod[i][j] = sum;
    }
  }
//#pragma endscop
}

int main(int argc,char **argv)
{
  double (*A)[120][120]) = ((double (*)[120][120])((double *)malloc(480000 * sizeof(double ))));
  double (*x)[120][120]) = ((double (*)[120][120])((double *)malloc(480000 * sizeof(double ))));
  double (*b)[120]) = ((double (*)[120])((double *)malloc(120 * sizeof(double ))));
  double (*b_orig)[120]) = ((double (*)[120])((double *)malloc(120 * sizeof(double ))));
  double (*b_error)[120]) = ((double (*)[120])((double *)malloc(120 * sizeof(double ))));
  double _in_A[120][120];
  double _in_x[120][120];
  double _in_b[120];
  double _out_b[120];
  double _out_b_orig[120];
  double _out_b_error[120];
  double _result;
  struct lp_struct_t _lp;
  int i;
  int j;
  int k;
//#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  kernel_gemm(_in_A,_in_x,_out_b);
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  kernel_gemm_orig(_in_A,_in_x,_out_b_orig);
//Section0:
//  Original from: gemm.c:30
//  A[i][k] * x[k][j] => sum[i][j]
  
#pragma ACCEL PIPELINE auto{off}
  for (i = 0; i < 120; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (j = 0; j < 120; j++) {
      sum:
      _lp.b[i] = 0.0;
      for (k = 0; k < 120; k++) {
        _lp.b[i] += _lp.A[i][k] * _lp.x[k][j];
      }
      _lp.b_error[i] = _lp.b[i] - _lp.b_orig[i];
    }
  }
//Section1:
//  Original from: gemm.c:44
//  A[i][k] * x[k][j] => sum[i][j]
//  Function: gemm
//  Args:
//  Return: double
//  Requirements:
//    All data must be aligned.
//    A and x must be private.
//    sum must be local.
//    b must be local.
//    b_error must be reduction.
//    depend(2) sum -> b
//    depend(2) b -> b_error
//    depend(1) A => sum
//    depend(1) x => sum
//    gemm_orig
//    
//#pragma ACCEL PIPELINE auto{flatten}
//#pragma ACCEL TILE FACTOR=auto{4}
//#pragma ACCEL PARALLEL FACTOR=auto{1}
//  for (i = 0; i < 120; i++) {
//    
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
//    for (j = 0; j < 120; j++) {
//      sum:
//      double sum = (double )0;
//      
//#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L3}
//      for (k = 0; k < 120; k++) {
//        double _in_val = _in_A[i][k];
//        double _in_ptr = _in_x[k][j];
//        sum += _in_val * _in_ptr;
//      }
//      _out_b[i] = sum;