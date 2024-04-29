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
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      for (k = -4; k < 5; k++) {
        int idx = pad + i * 64 + k;
        t += filter[k + 4] * orig[idx * 8 + j];
      }
      sol[i * 64 + j] = t;
    }
  }
}