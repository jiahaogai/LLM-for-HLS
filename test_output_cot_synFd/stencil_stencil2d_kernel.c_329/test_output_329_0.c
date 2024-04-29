#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      for (j = 0; j < 4; j++) {
        t += orig[k + j] * filter[j];
      }
    }
    sol[i] = t;
  }
}