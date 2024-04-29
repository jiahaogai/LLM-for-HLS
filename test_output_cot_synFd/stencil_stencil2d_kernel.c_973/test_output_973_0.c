#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  int k1;
  int k2;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 0; c < 64; c++) {
      sum = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k1 = 0; k1 < 3; k1++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k2 = 0; k2 < 3; k2++) {
          k = (k1 - 1) * 3 + (k2 - 1);
          sum += filter[k] * orig[(r + k1) * 64 + c + k2];
        }
      }
      sol[r * 64 + c] = sum;
    }
  }
}