#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt[9];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = ((int )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 9; j++) {
      pt[j] = filter[j];
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64 - 2; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        t += orig[i * 64 + j + k] * pt[k];
      }
      sol[i * 64 + j + 1] = t;
    }
  }
}