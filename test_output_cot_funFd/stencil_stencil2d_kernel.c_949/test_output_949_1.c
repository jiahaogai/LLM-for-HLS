Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{8}
Code: #pragma ACCEL PARALLEL FACTOR=auto{3}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{8}
Code: #pragma ACCEL PIPELINE auto{flatten}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
int main()
{
  int orig[8192] = {0};
  int sol[8192] = {0};
  int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_array(orig, 8192);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  stencil(orig, sol, filter);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  verify(sol, 8192, 15);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  return 0;
}