#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loop_row:
  for (row = 1; row < 33 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (col = 1; col < 33 - 1; col++) {
      flatten_row = row * 32 + col;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        flatten_col = k * 32 + col;
        idx = flatten_row * 9 + flatten_col;
        val = filter[k] * orig[idx];
        sol[idx] = val;
      }
    }
  }
}