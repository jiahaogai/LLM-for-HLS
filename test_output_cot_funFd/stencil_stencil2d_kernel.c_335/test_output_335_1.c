Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      tmp_orig = 0, tmp_sol = 0;
      
#pragma ACCEL PARALLEL reduction=tmp_orig FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        filter_elem = filter[k];
        tmp_orig += orig[i * 256 + j] * filter_elem;
      }
      
#pragma ACCEL PARALLEL reduction=tmp_sol FACTOR=auto{16}
      inner_sol:
      for (k = 0; k < 9; k++) {
        filter_elem = filter[k];
        tmp_sol += sol[i * 256 + j] * filter_elem;
      }
      tmp = tmp_sol + tmp_orig;
      if (tmp < 0) {
        tmp = 0;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      if (tmp > 255) {
        tmp = 255;
      }
      sol[i * 256 + j] = tmp;
    }
  }
}