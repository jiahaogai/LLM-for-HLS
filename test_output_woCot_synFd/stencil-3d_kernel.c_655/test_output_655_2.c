#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double CENTER;
  double EDGE;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  int r;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  int q;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  int p;
  EDGE = 1.0 / 8.0;
  CENTER = 2.0 / 8.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 0; r < 3; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{27}
    for (q = 0; q < 3; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      for (p = 0; p < 3; p++) {
        double sum = 0.0;
        int i;
        int j;
        int k;
        for (i = 0; i < 3; i++) {
          for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
              double val = orig[i * 3 * 3 + j * 3 + k];
              if ((((i + r) < 3) && (((j + q) < 3) && ((k + p) < 3)))) {
                sum += val;
              }
              else {
                sum += C0 * val;
              }
            }
          }
        }
        sol[r * 3 * 3 + q * 3 + p] = sum;
      }
    }
  }
}