#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf[9];
  int index;
  int upper_bound;
  int lower_bound;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        buf[k] = orig[((i + (-4 + k))) * 256 + j];
      }
      index = i * 256 + j;
      lower_bound = lower_bound_fast(buf, 0);
      upper_bound = upper_bound_fast(buf, 8);
      sol[index] = filter[upper_bound] - filter[lower_bound];
    }
  }
}