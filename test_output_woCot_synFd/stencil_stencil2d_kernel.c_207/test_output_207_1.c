#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{126}
#pragma ACCEL PARALLEL FACTOR=auto{1}

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + 1 + (-1 + k)) * 256 + 1 + (-1 + j);
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
    }
  }
}