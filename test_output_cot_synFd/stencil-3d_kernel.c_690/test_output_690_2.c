#pragma ACCEL kernel

void stencil3d(double C0,double C1,double orig[27],double sol[27])
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
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (p = 0; p < 3; p++) {
        double sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
	for (s = 0; s < 3; s++) {
          sum += orig[r + s * 3] * C1;
        }
	sum += C0;
	sol[r + q * 3 + p * 9] = sum;
      }
    }
  }
//#pragma endscop
}