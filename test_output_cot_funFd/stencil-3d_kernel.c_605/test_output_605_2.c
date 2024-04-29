#pragma ACCEL kernel

void stencil3d(int C0,int C1,double orig[27],double sol[27])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 0; r < 3; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 3; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 3; p++) {
        double sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
	for (s = 0; s < 3; s++) {
          sum += orig[r * 3 + s] * 
            ((q * 3 + s) % 3 == 0 ? 
             1.0 : ((q * 3 + s) % 3 == 1 ? 
                    2.0 : 1.0));
        }
	sol[r * 3 + p] = sum;
      }
    }
  }
//#pragma endscop
}