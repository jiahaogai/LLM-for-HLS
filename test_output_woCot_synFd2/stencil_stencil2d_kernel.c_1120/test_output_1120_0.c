#pragma ACCEL kernel

void kernel(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k / 3) - 1);
        int bound_check = (k_col >= 0 && k_col < 64);
        int src_index = bound_check ? (k_col * 64) + (k % 3 - 1) : 0;
        sum += filter[k] * orig[src_index];
      }
      sol[i * 64 + j] = sum;
    }
  }
}