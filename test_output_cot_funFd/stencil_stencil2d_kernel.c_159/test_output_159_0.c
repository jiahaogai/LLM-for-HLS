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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    loopi:
    for (i = 1; i < 8191; i++) {
      t = 0;
      loopk:
      for (k = 0; k < 9; k++) {
        row = j + (-4 + k);
        col = i + (-4 + k);
        if (row < 0 || 8191 < row || col < 0 || 8191 < col) {
          /* skip FPU constraint when out-of-bound */
          t += filter[k] * 0;
        }
         else {
          t += filter[k] * orig[row * 8192 + col];
        }
      }
      sol[j * 8192 + i] = t;
    }
  }
}