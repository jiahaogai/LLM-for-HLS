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
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    inner:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter_idx:
      for (k = 0; k < 9; k++) {
        idx = (256 + 1 + 8 - 1) * (256 + 1 + 8 - 1) * k + (256 + 1 + 8 - 1) * j + i;
        s += orig[idx] * filter[k];
      }
      sol[idx] = s;
    }
  }
}