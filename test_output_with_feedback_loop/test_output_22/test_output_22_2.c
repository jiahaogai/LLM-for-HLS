#pragma ACCEL kernel

void kernel_seidel_2d(int orig_A[4096],int sol[4096],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int temp;
  int mul;
  int u;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 32; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    for (c = 0; c < 32; c++) {
      temp = ((int )0);
      mul = 0;
      k1 = 0;
      int _in_loop_k1 = 0;
      for (k2 = 0; k2 < 32; k2++) {
        for (k1 = 0; k1 < 3; k1++) {
          mul = k1 * 32;
          temp += filter[k1] * orig_A[(mul + r) * 32 + c];
        }
      }
      u = sol[mul + r * 32 + c];
      sol[mul + r * 32 + c] = u + temp;
    }
  }
}