#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (r = 1; r < 33; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (c = 1; c < 33; c++) {
      i = r - 1;
      j = c - 1;
      k = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (i < r + 1) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        while (j < c + 1) {
          k++;
          sol[r * 32 + c] += orig[i * 32 + j] * filter[k];
          j++;
        }
        j = c - 1;
        i++;
      }
    }
  }
}