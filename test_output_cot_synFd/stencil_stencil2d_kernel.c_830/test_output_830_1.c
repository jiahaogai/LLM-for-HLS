#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 1; i < 33; i++) {
      t = 0;
      loopk:
      for (k = 0; k < 9; k++) {
        row = j + (-1 + k);
        col = i + (-1 + ((k + 4) % 9));
        flit = (row * 32) + col;
        t += orig[flit] * filter[k];
      }
      sol[j * 32 + i] = t;
    }
  }
}