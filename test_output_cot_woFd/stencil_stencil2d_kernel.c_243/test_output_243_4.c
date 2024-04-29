#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = orig[idx] * filter[0];
      pos:
      for (k = 1; k < 9; k++) {
        idx = ((i + ((k >> 1) - 1)) % 256) * 256 + (j + ((k >> 1) - 1)) % 256;
        val += orig[idx] * filter[k];
      }
      sol[idx] = val;
    }
  }
}