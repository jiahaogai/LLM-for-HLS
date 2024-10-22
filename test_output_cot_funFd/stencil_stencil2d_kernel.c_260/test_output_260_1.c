#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{16}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (256 * (i + 4)) + (j + k);
        if (idx < 0 || idx >= 8192) {
          continue;
        }
        s += ((double )filter[k + 4]) * orig[idx];
      }
      sol[i * 256 + j] = s;
    }
  }
}