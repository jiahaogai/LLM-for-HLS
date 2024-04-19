#pragma ACCEL PIPELINE auto{off}
 
#pragma ACCEL TILE FACTOR=auto{25}
  
#pragma ACCEL PIPELINE auto{off}
 
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{25}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      sum[q] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      for (p = 0; p < 30; p++) {
        sum[q] += A[r][q][p] * C4[p][q];
      }
    }
    for (s = 0; s < 30; s++) {
      A[r][s][30] = sum[s];
    }
  }
//#pragma endscop
}