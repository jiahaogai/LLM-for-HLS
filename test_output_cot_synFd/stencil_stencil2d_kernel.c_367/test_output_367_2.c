#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8; j++) {
      t = 0;
      int idx = pad + i - 1 + ((pad + j - 1) * 8);
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (int k = 0; k < 9; ++k) {
        int idx_filter = k + ((pad + i - 1) * 9);
        int idx_input = pad + j - 1 + (idx_filter * 8);
        t += filter[k] * orig[idx_input];
      }
      sol[idx] = t;
    }
  }
}