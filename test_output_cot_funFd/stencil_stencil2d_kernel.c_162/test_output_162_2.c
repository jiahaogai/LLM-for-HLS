#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[256])
{
  int i;
  int j;
  int k;
  int k_col;
  int buff_col[256];
  int buff[8192];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    buff[i] = orig[i];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    buff_col[i] = buff[i];
    
#pragma ACCEL PARALLEL reduction=buff_col FACTOR=auto{1}
    for (j = 1; j < 8; j++) {
      k_col = i - 1 + j;
      
#pragma ACCEL PARALLEL reduction=buff_col FACTOR=auto{1}
      for (k = 0; k < 8; k++) {
        int orig_value;
        int sol_value;
        int flt_value;
        int result;
        int place_in_orig;
        int place_in_sol;
        
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
        place_in_orig = i + ((-1 * j) + k) * 8;
        orig_value = buff[place_in_orig];
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
        place_in_sol = i + k * 8;
        sol_value = sol[place_in_sol];
        
#pragma ACCEL PARALLEL reduction=flt FACTOR=auto{8}
        flt_value = filter[k_col];
        
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{8}
        result = sol_value + flt_value * orig_value;
        buff[place_in_orig] = result;
      }
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = buff[i];
  }
}