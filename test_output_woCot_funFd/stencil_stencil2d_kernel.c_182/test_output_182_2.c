#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    t = orig[i] * filter[0];
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
    inner1:
    for (j = 1; j < 9; j++) {
      t += orig[i + j] * filter[j];
    }
    sol[i] = t;
  }
}