#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 32; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k / 3) - 1);
        if ((k_col >= 0)) {
           if ((k_col < 32)) {
            idx = k_col * 32 + j + ((k % 3) - 1);
            if ((idx >= 0)) {
               if ((idx < 8192)) {
                val += orig[idx] * filter[k];
              }
           }
          }
        }
      }
      sol[i * 32 + j] = val;
    }
  }
}