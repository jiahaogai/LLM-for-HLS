#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 337; j++) {
      result = ((orig[i * 337 + j] * filter[0]) + (orig[i * 337 + j + 1] * filter[1]) + (orig[i * 337 + j + 2] * filter[2]) + (orig[(i + 1) * 337 + j] * filter[3]) + (orig[(i + 1) * 337 + j + 1] * filter[4]) + (orig[(i + 1) * 337 + j + 2] * filter[5]) + (orig[(i + 2) * 337 + j] * filter[6]) + (orig[(i + 2) * 337 + j + 1] * filter[7]) + (orig[(i + 2) * 337 + j + 2] * filter[8])) / 256;
      sol[i * 337 + j] = result;
    }
  }
}