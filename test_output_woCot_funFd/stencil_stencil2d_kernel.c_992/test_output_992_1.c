#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int r;
  int r_col;
  int c;
  int buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 2; r < 128 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 2; c < 64 - 1; c++) {
      buf = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k_col = 0; k_col < 3; k_col++) {
          i_col = r - 1 + k;
          j_col = c - 1 + k_col;
          buf += filter[k * 3 + k_col] * orig[i_col * 64 + j_col];
        }
      }
      sol[r * 64 + c] = buf;
    }
  }
}