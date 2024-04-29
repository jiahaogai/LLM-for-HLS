#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 256; i < 128 + 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    for (j = 256; j < 64 + 256; j++) {
      result = ((0 * orig[i - 2 + (j - 2) * 128]) + (1 * orig[i - 1 + (j - 2) * 128]) + (2 * orig[i + (j - 2) * 128]) + (3 * orig[i + 1 + (j - 2) * 128]) + (4 * orig[i + 2 + (j - 2) * 128])) + ((1 * orig[i - 2 + (j - 1) * 128]) + (2 * orig[i - 1 + (j - 1) * 128]) + (3 * orig[i + (j - 1) * 128]) + (4 * orig[i + 1 + (j - 1) * 128]) + (5 * orig[i + 2 + (j - 1) * 128])) + ((2 * orig[i - 2 + (j) * 128]) + (3 * orig[i - 1 + (j) * 128]) + (4 * orig[i + (j) * 128]) + (5 * orig[i + 1 + (j) * 128]) + (6 * orig[i + 2 + (j) * 128])) + ((3 * orig[i - 2 + (j + 1) * 128]) + (4 * orig[i - 1 + (j + 1) * 128]) + (5 * orig[i + (j + 1) * 128]) + (6 * orig[i + 1 + (j + 1) * 128]) + (7 * orig[i + 2 + (j + 1) * 128])) + ((4 * orig[i - 2 + (j + 2) * 128]) + (5 * orig[i - 1 + (j + 2) * 128]) + (6 * orig[i + (j + 2) * 128]) + (7 * orig[i + 1 + (j + 2) * 128]) + (8 * orig[i + 2 + (j + 2) * 128]));
      sol[i + j * 128] = result;
    }
  }
}