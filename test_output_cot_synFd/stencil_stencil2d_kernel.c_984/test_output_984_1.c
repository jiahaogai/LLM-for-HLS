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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 0; j < 256; j++) {
      val = 0;
      filter:
      for (k = 0; k < 9; k++) {
        idx = i + (-4 + k);
        idy = j + (-4 + k);
        if (idx < 0 || idx > 255 || idy < 0 || idy > 255) {
          val = 0;
        }
         else {
          val += orig[idx * 256 + idy] * filter[k];
        }
      }
      sol[i * 256 + j] = val;
    }
  }
}