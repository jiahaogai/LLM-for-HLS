#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        t += filter[k + 4] * orig[i * 64 + (j * 8 + k) * 16];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      sol[i * 64 + j * 8] = t;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        t += filter[k + 4] * sol[(i * 64 + (j + k) * 8) * 16];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      sol[i * 64 + j * 8] = t;
    }
  }
}