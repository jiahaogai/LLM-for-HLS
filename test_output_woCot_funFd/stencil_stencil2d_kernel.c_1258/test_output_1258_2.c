#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = -1; k <= 1; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        for (int jj = -1; jj <= 1; jj++) {
          t += filter[((k + 1) * 3) + (jj + 1)] * orig[pad + ((i * 8) + k) * 64 + ((j * 8) + jj)];
        }
      }
      sol[pad + (i * 64) + (j * 8)] = t;
    }
  }
}