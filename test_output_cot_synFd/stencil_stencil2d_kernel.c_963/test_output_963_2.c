#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int r;
  int c;
  int value;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 1; j < 8191; j++) {
      r = i - 4;
      c = j - 4;
      value = 0;
      
#pragma ACCEL PARALLEL reduction=value FACTOR=auto{32}
      for (r = r; r < i + 5; r++) {
        
#pragma ACCEL PARALLEL reduction=value FACTOR=auto{32}
        for (c = c; c < j + 5; c++) {
          value += orig[r * 8192 + c] * filter[((r - (i - 4)) + 4) * 5 + ((c - (j - 4)) + 4)];
        }
      }
      sol[i * 8192 + j] = value;
    }
  }
}