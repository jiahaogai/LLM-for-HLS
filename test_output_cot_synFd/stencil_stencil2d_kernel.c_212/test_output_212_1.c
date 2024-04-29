#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      middle:
      for (k = -4; k < 5; k++) {
        idx = (256 + i + k) % 256;
        idy = (256 + j + filter[k + 4]) % 256;
        t += orig[idx * 256 + idy] * filter[k + 4];
      }
      sol[i * 256 + j] = t;
    }
  }
}