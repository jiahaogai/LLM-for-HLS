#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8188; j++) {
      elem = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        elem += orig[i + ((k - 4) > -1 ? -((k - 4) > 8 ? 8 : (k - 4)) : 1)][j + ((k - 4) > -1 ? -((k - 4) > 8 ? 8 : (k - 4)) : 1)] * filter[k];
      }
      sol[i][j] = elem;
    }
  }
}