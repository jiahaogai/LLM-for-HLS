
 #pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[200][240][30],double C4[30][30],double B[200][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 200; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    for (q = 0; q < 240; q++) {
      A[r][q][0] = 1.0;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 200; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (p = 0; p < 30; p++) {
      B[r][p] = 0.0;
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{1}
      for (s = 0; s < 30; s++) {
        B[r][p] += C4[p][s] * A[r][s][0];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (p = 0; p < 30; p++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (r = 0; r < 200; r++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (q = 0; q < 240; q++) {
        sum += A[r][q][0] * B[q][p];
      }
      A[r][0][p] = sum;
    }
  }
//#pragma endscop
}
