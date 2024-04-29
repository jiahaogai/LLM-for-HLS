#pragma ACCEL kernel

void stencil3d(int C0,int C1,double orig[27],double sol[27])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 3; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 3; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 3; p++) {
        double sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
	for (s = 0; s < 3; s++) {
          int i = r + s - 1;
          if (i < 0) {
            i = -i;
          }
          if (i > 2) {
            i = 6 - i;
          }
          int j = q + s - 1;
          if (j < 0) {
            j = -j;
          }
          if (j > 2) {
            j = 6 - j;
          }
          int k = p + s - 1;
          if (k < 0) {
            k = -k;
          }
          if (k > 2) {
            k = 6 - k;
          }
          int i_src = i * 3;
          int j_src = j * 3;
          int k_src = k * 3;
          sum += orig[i_src + j_src + k_src] * C0;
        }
        sol[r * 3 + q * 3 + p] = sum;
      }
    }
  }
//#pragma endscop
}