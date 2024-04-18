### PIPELINE auto{off}
 

### TILE FACTOR=auto{1}
 

### PIPELINE auto{flatten}
 

### PARALLEL reduction=sum_tmp FACTOR=auto{1}
 
#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      double tmp = A[r][q][0];
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (p = 1; p < 30; p++) {
        A[r][q][p] = tmp * C4[p][q];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (s = 0; s < 30; s++) {
      sum[s] = A[r][0][s] + A[r][1][s];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (s = 0; s < 30; s++) {
    double sum_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
    for (r = 0; r < 25; r++) {
      sum_tmp += sum[r] * A[r][20][s];
    }
    sum[s] = sum_tmp;
  }
//#pragma endscop
}