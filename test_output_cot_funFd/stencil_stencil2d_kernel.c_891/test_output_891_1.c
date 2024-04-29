#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_i:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 400 - 1; j++) {
      sum = 0;
      loop_k:
      for (k = 0; k < 9; k++) {
        idx = i + ((k / 3) - 1);
        idy = j + ((k % 3) - 1);
        sum += orig[idx][idy] * filter[k];
      }
      sol[i][j] = sum;
    }
  }
}