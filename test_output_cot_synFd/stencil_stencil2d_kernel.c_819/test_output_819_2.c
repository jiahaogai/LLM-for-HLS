#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int flidx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      flidx = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        flidx += filter[k] * orig[idx + dir[k]];
      }
      sol[idx] = flidx;
    }
  }
}