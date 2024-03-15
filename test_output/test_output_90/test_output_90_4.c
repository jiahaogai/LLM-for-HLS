
- For the loop over `q`, unroll it by a factor of 2 (`#pragma ACCEL PIPELINE auto{flatten} UNROLL=2`)).
- For the loop over `p`, unroll it by a factor of 2 (`#pragma ACCEL PIPELINE auto{off} UNROLL=2`)).
After the above optimizations, the generated kernel should be similar to the following with no pipeline pragmas:
 #pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{2}
      for (p = 0; p < 30; p++) {
        double sum_tmp = 0.0;
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
	for (s = 0; s < 30; s++) {
          sum_tmp += A[r][q][s] * C4[s][p];
        }
	sum[p] = sum_tmp;
      }
      for (p = 0; p < 30; p++) {
        A[r][q][p] = sum[p];
      }
    }
  }
//#pragma endscop
}
