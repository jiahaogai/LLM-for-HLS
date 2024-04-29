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
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    inner:
    for (j = 0; j < 8192; j++) {
      result = ((0 * orig[i * 8192 + j]) + (1 * orig[i * 8192 + ((j + 1) > 8191 ? 8191 : (j + 1))]) + (2 * orig[i * 8192 + ((j + 8192) > 8191 ? 8191 : (j + 8192))]) + (3 * orig[i * 8192 + ((j + 1) > 8191 ? 8191 : (j + 1)) + 8192]) + (4 * orig[i * 8192 + ((j + 8192) > 8191 ? 8191 : (j + 8192)) + 8192]) + (5 * orig[i * 8192 + ((j + 1) > 8191 ? 8191 : (j + 1)) - 8192]) + (6 * orig[i * 8192 + ((j + 8192) > 8191 ? 8191 : (j + 8192)) - 8192]) + (7 * orig[i * 8192 + ((j + 1) > 8191 ? 8191 : (j + 1)) + 1]) + (8 * orig[i * 8192 + ((j + 8192) > 8191 ? 8191 : (j + 8192)) + 1])) / 8192;
      sol[i * 8192 + j] = result;
    }
  }
}