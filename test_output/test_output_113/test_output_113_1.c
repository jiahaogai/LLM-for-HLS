
7. Turn off automatic loop blocking for the following loop.
8. Use the original, full form of the loop without breaking it into smaller chunks.
9. Run the iterations of the loop with a parallel factor of 2.
10. Run the iterations of the first inner loop with a parallel factor of 3.
11. Run the iterations of the second inner loop with a parallel factor of 1.
12. Turn off automatic loop unrolling for the following loop.
13. Use the original, full form of the loop without breaking it into smaller chunks.
14. Run the iterations of the loop with a parallel factor of 2.
15. Run the iterations of the first inner loop with a parallel factor of 3.
16. Run the iterations of the second inner loop with a parallel factor of 1.
 #pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double tmp[40][50],double A[40][70],double B[70][50],double C[50][80],double D[40][80])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 50; j++) {
      tmp[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 70; ++k) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      D[i][j] *= beta;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 50; ++k) {
        D[i][j] += tmp[i][k] * C[k][j];
      }
    }
  }
//#pragma endscop
}
