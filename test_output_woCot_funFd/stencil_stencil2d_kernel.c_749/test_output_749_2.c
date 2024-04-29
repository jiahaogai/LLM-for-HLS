Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 9; j++) {
      sol[i] += filter[j] * orig[i + [-8, -7, -1, 0, 1, 7, 8]} [j];
    }
  }
}