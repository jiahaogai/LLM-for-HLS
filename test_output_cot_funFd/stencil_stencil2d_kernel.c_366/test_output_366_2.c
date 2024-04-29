#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8186; j++) {
      result = ((0 * orig[i - 1 + (j - 1) * 8192]) + (1 * orig[i + (j - 1) * 8192]) + (0 * orig[i + 1 + (j - 1) * 8192]) + (2 * orig[i - 1 + j * 8192]) + (3 * orig[i + j * 8192]) + (2 * orig[i + 1 + j * 8192]) + (0 * orig[i - 1 + (j + 1) * 8192]) + (1 * orig[i + (j + 1) * 8192]) + (0 * orig[i + 1 + (j + 1) * 8192]));
      sol[i + j * 8192] = result;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      sol[i + j * 8192] = filter[4] * sol[i + j * 8192] + filter[0] * (sol[i - 1 + j * 8192] + sol[i + 1 + j * 8192]) + filter[1] * (sol[i + (j - 1) * 8192] + sol[i + (j + 1) * 8192]) + filter[2] * sol[i - 1 + (j - 1) * 8192] + filter[3] * (sol[i - 1 + (j + 1) * 8192] + sol[i + 1 + (j + 1) * 8192]) + filter[5] * sol[i - 1 + (j + 1) * 8192] + filter[6] * sol[i + 1 + (j - 1) * 8192];
    }
  }
}