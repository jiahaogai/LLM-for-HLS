#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k1;
  int k2;
  int r;
  int c;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 8191; c++) {
      sol[r * 8192 + c] = 0;
      k1 = r - 4;
      k2 = c - 4;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        int tmp_1;
        tmp_1 = filter[k] * orig[k1 + 4][k2 + 4];
        sol[r * 8192 + c] += tmp_1;
        k1++;
      }
    }
  }
}