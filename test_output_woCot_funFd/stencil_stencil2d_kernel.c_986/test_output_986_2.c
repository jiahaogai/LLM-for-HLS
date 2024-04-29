The `flatten` optimization factor, for example, will flatten the accessed rows and columns of the 2D arrays into 1D arrays, which in turn reduces the amount of memory accesses.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_orig[1024];
  int flatten_sol[1024];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      row = i * 32;
      col = j * 32;
      flatten_orig[row + col] = orig[i * 32 + j];
      flatten_sol[row + col] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        flatten_sol[row + col] += filter[k] * flatten_orig[row + ((col + k) % 32)];
      }
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      sol[i * 32 + j] = flatten_sol[i * 32 + j];
    }
  }
}