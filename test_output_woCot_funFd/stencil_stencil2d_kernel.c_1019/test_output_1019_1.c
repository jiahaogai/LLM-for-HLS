#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_i;
  int flatten_j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 16;
      flatten_i = 0 + row;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (k = 0; k < 16; k++) {
        sol[flatten_i + col + k] = 0;
        
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
        for (k = 0; k < 9; k++) {
          sol[flatten_i + col + k] += filter[k] * orig[flatten_i + col + k];
        }
      }
    }
  }
}