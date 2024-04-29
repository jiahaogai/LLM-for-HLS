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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      filter_elem:
      for (k = 0; k < 9; k++) {
        idx = i + (-1 + k);
        idy = j + (-1 + k);
        if (idx < 0 || idx > 255 || idy < 0 || idy > 255) {
          t += 0;
        }
         else {
          t += orig[idx * 256 + idy] * filter[k];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}