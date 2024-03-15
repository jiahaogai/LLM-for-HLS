
8. Don't automatically distribute the middle loop.
9. Automatically distribute the outermost loop across 1500 cores.
10. Automatically parallelize the middle loop across 128 cores.
11. Automatically parallelize the outermost loop across 1500 cores.


 #pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,int nalphas,double eps,double sigma,double alpha[4],double A[40][50],double B[50][80],double C[40][80])
{
  int i;
  int j;
  int k;
  int n;
  int q;
  double val;
  double sum;
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    loopk:
    for (k = 0; k < 40; k++) {
      sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L4}
      loopn:
      for (n = 0; n < 50; n++) {
        sum += A[k][n] * B[n][j];
      }
      C[k][j] = sum;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  loopi:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    loopq:
    for (q = 0; q < 50; q++) {
      val = 0.0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{__PARA__L3}
      loopn:
      for (n = 0; n < 50; n++) {
        tmp = A[i][n] * B[n][q];
        val += tmp * C[n][q];
      }
      A[i][q] = val;
    }
  }
}
