#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      center = orig[idx];
      flatten_idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        if ((idx + k - 4) >= 0 && (idx + k - 4) < 8192) {
          flatten_idx += filter[k] * orig[idx + k - 4];
        }
      }
      sol[idx] = flatten_idx;
    }
  }
}