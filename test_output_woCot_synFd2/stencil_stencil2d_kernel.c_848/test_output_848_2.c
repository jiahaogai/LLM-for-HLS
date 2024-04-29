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
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 33; c++) {
      i = r - 1;
      j = c - 1;
      k = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{32}
      while (i < 32) {
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{8}
        while (j < 32) {
          sol[r * 32 + c] += orig[i * 32 + j] * filter[k++];
          j++;
        }
        i++;
        j = c - 1;
      }
    }
  }
}