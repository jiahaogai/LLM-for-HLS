Code: 
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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        if (((i + k) >= 0) && ((i + k) < 256)) {
          filter_elem = filter[4 + k];
          tmp_orig += filter_elem * orig[i + k];
          tmp_sol += filter_elem * sol[i + k];
        }
      }
      tmp = tmp_sol + tmp_orig;
      sol[i * 256 + j] = tmp;
    }
  }
}