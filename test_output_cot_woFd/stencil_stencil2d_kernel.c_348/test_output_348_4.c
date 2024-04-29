#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        if ((i + k) < 0 || (i + k) > 255) {
          filter_elem = 0;
        }
         else {
          filter_elem = filter[4 + k];
        }
        tmp_orig = orig[i + k] * filter_elem;
        tmp_sol += tmp_orig;
      }
      tmp = sol[i * 256 + j];
      tmp_sol += tmp;
      tmp_orig = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_1:
      for (k = -4; k < 5; k++) {
        if ((j + k) < 0 || (j + k) > 255) {
          filter_elem = 0;
        }
         else {
          filter_elem = filter[4 + k];
        }
        tmp_orig = orig[((i + 4) + ((256 - 1) - (j + 4)) - 1) * 256 + ((j + k) + 4)] * filter_elem;
        tmp_sol += tmp_orig;
      }
      sol[i * 256 + j] = tmp_sol;
    }
  }
}