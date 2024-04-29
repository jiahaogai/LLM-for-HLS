#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int pass;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (pass = 0; pass < 40; pass++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (i = 0; i < 256; i++) {
      inner:
      for (j = 0; j < 256; j++) {
        t = 0;
        row:
        for (row = i - 4; row <= i + 4; row++) {
          col:
          for (j = j - 4; j <= j + 4; j++) {
            t += orig[row * 256 + j] * filter[row - i + 4 + 4 * (j - j)];
          }
        }
        sol[i * 256 + j] = t;
      }
    }
  }
//#pragma endscop
}