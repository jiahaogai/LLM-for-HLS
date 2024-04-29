#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8176; j++) {
      result = ((0 * orig[i * 8192 + j]) + (1 * orig[i * 8192 + j + 1]) + (2 * orig[i * 8192 + j + 2]) + (3 * orig[i * 8192 + j + 8176]) + (4 * orig[i * 8192 + j + 8177]) + (5 * orig[i * 8192 + j + 8178]) + (6 * orig[i * 8192 + j + 8179]) + (7 * orig[i * 8192 + j + 8180]) + (8 * orig[i * 8192 + j + 8181])) / 40;
      sol[i * 8192 + j] = result;
    }
  }
}