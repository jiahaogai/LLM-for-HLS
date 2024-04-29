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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      for (k = -4; k < 5; k++) {
        int idx = (((4 * i) + k) * 8) + j;
        t += filter[((k + 4) * 2) + 1] * orig[pad + idx];
      }
      sol[((4 * i) * 8) + j] = t;
    }
  }
}