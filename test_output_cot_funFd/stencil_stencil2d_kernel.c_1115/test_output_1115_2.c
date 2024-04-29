#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int temp_orig;
  int temp_sol;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8192; i++) {
    int _in_i = i;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      int _in_j = j;
      temp_orig = orig[_in_i] >> 16;
      temp_sol = 0;
      
#pragma ACCEL PARALLEL reduction=temp_sol FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        int _in_k = k;
        k_col = _in_i + k;
        filter_elem = filter[4 + _in_k];
        if (k_col < 0 || k_col > 8191) {
          filter_elem = 0;
        }
        temp_sol += filter_elem * ((int )((unsigned short )orig[k_col]) >> 16);
      }
      sol[_in_j] = temp_sol;
      orig[i] = ((temp_sol & 65535) << 16) | (temp_orig & 65535);
    }
  }
}