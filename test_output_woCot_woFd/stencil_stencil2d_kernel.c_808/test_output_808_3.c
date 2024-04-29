5. #pragma ACCEL PIPELINE auto{off}: Do not pipeline the outer loop.
6. #pragma ACCEL TILE FACTOR=auto{8}: Divide the loop into 8 smaller parts.
7. #pragma ACCEL PARALLEL FACTOR=auto{4}: Process 4 smaller parts at a time.
8. #pragma ACCEL PIPELINE auto{off}: Do not pipeline the inner loop.
9. #pragma ACCEL TILE FACTOR=auto{1}: Keep the loop structure intact.
10. #pragma ACCEL PARALLEL FACTOR=auto{1}: Process 1 iteration at a time.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  outer:
  for (i = 0; i < 128 + 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 64 + 8; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i * 64 + j - 4 + k];
      }
      sol[i * 64 + j] = result;
      result = 0;
    }
  }
}