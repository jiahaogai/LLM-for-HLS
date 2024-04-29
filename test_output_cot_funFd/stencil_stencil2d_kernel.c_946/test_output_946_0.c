#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 9; j++) {
      tmp += filter[j] * orig[i + (_J_STride * j)];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    inner_1:
    for (j = 0; j < 32; j++) {
      sol[i + (_J_STride * j)] = tmp;
    }
  }
}