#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 33; j++) {
      temp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        temp += orig[i + (-1 + k)/2 * 32 + (-1 + j)*32] * filter[k];
      }
      sol[i * 32 + j] = temp;
    }
  }
}