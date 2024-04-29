#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8192; j++) {
      val = 0;
      
#pragma ACCEL PIPELINE auto{off}
      inner:
      for (k = 0; k < 9; k++) {
        idx = i + ((k / 3) - 1);
        idy = j + ((k % 3) - 1);
        if (idx >= 0 && idx < 8192 && idy >= 0 && idy < 8192) {
          val += orig[idx * 8192 + idy] * filter[k];
        }
      }
      sol[i * 8192 + j] = val;
    }
  }
}