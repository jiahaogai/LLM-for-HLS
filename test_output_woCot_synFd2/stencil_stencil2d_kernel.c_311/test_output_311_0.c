#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int pt = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{14}
    inner:
    for (j = 0; j < 9; j++) {
      t += orig[i + j - pt] * filter[j];
    }
    sol[i] = t;
  }
}