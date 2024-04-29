#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    middle:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      t += filter[j] * orig[k];
    }
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
    sol[i] = t;
  }
}