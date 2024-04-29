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
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        t += filter[k + 4] * orig[((i * 64) + (j * 8)) + pad + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      sol[((i * 64) + (j * 8)) + pad] = t;
    }
  }
}