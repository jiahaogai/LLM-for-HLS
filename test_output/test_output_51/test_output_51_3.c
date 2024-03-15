
 #pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,int nn,double A[200][240],double B[240][280],double C[200][280])
{
  int r;
  int q;
  int p;
  int n;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 0; r < 200; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 240; q++) {
      A[r][q] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 200; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (q = 0; q < 280; q++) {
      C[r][q] = ((double )0);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (p = 0; p < 240; p++) {
      
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L4}
      for (n = 0; n < 200; n++) {
        A[r][p] += B[n][q] * C[n][q];
      }
    }
  }
//#pragma endscop
}
