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
          int j = q + s - 1;
          int k = p + s - 1;
          if (i < 0) {
            i = 0;
          }
          if (j < 0) {
            j = 0;
          }
          if (k < 0) {
            k = 0;
          }
          if (i > 2) {
            i = 2;
          }
          if (j > 2) {
            j = 2;
          }
          if (k > 2) {
            k = 2;
          }
          sum += orig[i * 9 + j * 3 + k] * 4.0;
        }
        sol[r * 9 + q * 3 + p] = sum;
      }
    }
  }
//#pragma endscop
}