Code: #pragma ACCEL PIPELINE auto{}
Error: 
#pragma ACCEL PIPELINE auto{flatten}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{7}
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
int main()
{
  int orig[8192] __attribute__((__aligned__(64)));
  int sol[8192] __attribute__((__aligned__(64)));
  int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  init_array(orig, 8192);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  stencil(orig, sol, filter);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  verify(sol, 8192);
  return 0;
}