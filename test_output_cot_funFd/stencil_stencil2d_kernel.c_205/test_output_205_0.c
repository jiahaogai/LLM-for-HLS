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
    for (j = 1; j < 8176; j++) {
      result = ((orig[i * 8192 + j] + orig[i * 8192 + j + 1] + orig[i * 8192 + j + 8176] + orig[i * 8192 + j + 8177] + orig[
                 (i + 1) * 8192 + j] + orig[((i + 1) * 8192) + j + 1] + orig[((i + 1) * 8192) + j + 8176] + orig[((i + 1)
                  * 8192) + j + 8177] + orig[((i - 1) * 8192) + j] + orig[((i - 1) * 8192) + j + 1] + orig[((i - 1) *
                   8192) + j + 8176] + orig[((i - 1) * 8192) + j + 8177]) / 11);
      sol[i * 8192 + j] = result;
    }
  }
}