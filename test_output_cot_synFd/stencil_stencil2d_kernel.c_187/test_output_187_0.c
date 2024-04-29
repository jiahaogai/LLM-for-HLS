**Inputs:**

| Parameter | Size (Bytes) |
|-----------|---------------|
| orig | 8192 |
| sol | 8192 |
| filter | 9 |


**Outputs:**

| Parameter | Size (Bytes) |
|-----------|---------------|
| sol | 8192 |

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      t = 0;
      loopk:
      for (k = 0; k < 9; k++) {
        row = j + (-1 + k);
        col = i + (-1 + (k % 3));
        t += orig[row * 32 + col] * filter[k];
      }
      sol[j * 32 + i] = t;
    }
  }
}