#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int bound;
  int d;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  bound = 8192 << 3;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop:
  for (i = 8; i < bound - 8; i++) {
    t = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    inner_loop:
    for (j = 0; j < 9; j++) {
      d = filter[j] << 3;
      t += orig[i - d + 8] * filter[j];
    }
    sol[i] = t;
  }
}