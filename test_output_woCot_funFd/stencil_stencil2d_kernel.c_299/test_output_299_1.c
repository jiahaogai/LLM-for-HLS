Code: #pragma ACCEL PIPELINE auto{off}`: Switch off the automatic pipeline flattening.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Tile the loop with a factor of 1.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations concurrently with a factor of 1.
- `#pragma ACCEL PIPELINE auto{off}`: Switch off the automatic pipeline flattening.
- `#pragma ACCEL TILE FACTOR=auto{8}`: Tile the loop with a factor of 8.
- `#pragma ACCEL PIPELINE auto{off}`: Switch off the automatic pipeline flattening.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Tile the loop with a factor of 1.
- `#pragma ACCEL PIPELINE auto{off}`: Switch off the automatic pipeline flattening.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Tile the loop with a factor of 1.
- `#pragma ACCEL PIPELINE auto{off}`: Switch off the automatic pipeline flattening.
- `#pragma ACCEL TILE FACTOR=auto{8}`: Tile the loop with a factor of 8.
- `#pragma ACCEL PIPELINE auto{off}`: Switch off the automatic pipeline flattening.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Tile the loop with a factor of 1.
- `#pragma ACCEL PIPELINE auto{off}`: Switch off the automatic pipeline flattening.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Tile the loop with a factor of 1.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int curRow;
        int curCol;
        curRow = i * 8 + j;
        curCol = k + pad;
        t += filter[pad + k] * orig[curRow * 8 + curCol];
      }
      sol[i * 8 + j] = t;
    }
  }
}