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
          double tmp = 0.0;
          if (i >= 0 && i < 3 && j >= 0 && j < 3 && k >= 0 && k < 3) {
            tmp = orig[i * 3 * 3 + j * 3 + k];
          }
          sum += tmp;
        }
	sol[r * 3 * 3 + q * 3 + p] = sum;
      }
    }
  }
//#pragma endscop
}