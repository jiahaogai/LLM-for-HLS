Code: -
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (r = 1; r < 33; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 33; c++) {
      i = r * 32 + c;
      sol[i] = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        j = k / 32;
        i = k - j * 32;
        sol[i] += filter[k] * orig[r * 32 + c];
      }
    }
  }
}