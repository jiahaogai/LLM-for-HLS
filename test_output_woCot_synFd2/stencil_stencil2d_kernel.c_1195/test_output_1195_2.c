**Filter Coefficients:**  

  -1 -2 -1
  -2  7 -2
  -1 -2 -1


#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      result = ((0 + 
        filter[0] * (orig[i - 1 + (j - 1) * 8192] + orig[i - 1 + (j + 0) * 8192] + orig[i - 1 + (j + 1) * 8192] + orig[i + 0 + (j - 1) * 8192] + orig[i + 0 + (j + 0) * 8192] + orig[i + 0 + (j + 1) * 8192] + orig[i + 1 + (j - 1) * 8192] + orig[i + 1 + (j + 0) * 8192] + orig[i + 1 + (j + 1) * 8192])) + 
        filter[1] * (orig[i - 1 + (j - 1) * 8192] + orig[i - 1 + (j + 1) * 8192] + orig[i + 1 + (j - 1) * 8192] + orig[i + 1 + (j + 1) * 8192])) + 
        filter[2] * (orig[i - 1 + (j - 1) * 8192] + orig[i - 1 + (j + 0) * 8192] + orig[i - 1 + (j + 1) * 8192] + orig[i + 0 + (j - 1) * 8192] + orig[i + 0 + (j + 1) * 8192] + orig[i + 1 + (j - 1) * 8192] + orig[i + 1 + (j + 0) * 8192] + orig[i + 1 + (j + 1) * 8192]);
      sol[i + j * 8192] = result;
    }
  }
}