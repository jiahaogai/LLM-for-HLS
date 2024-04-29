#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_j:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_i:
    for (i = 1; i < 32; i++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loop_k:
      for (k = 0; k < 9; k++) {
        row = j + (-1 + k);
        col = i + (-1 + k);
        sum += filter[k] * orig[row * 32 + col];
      }
      sol[j * 32 + i] = sum;
    }
  }
}