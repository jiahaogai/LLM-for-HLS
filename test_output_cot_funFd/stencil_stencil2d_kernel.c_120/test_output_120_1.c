Code: #pragma ACCEL PIPELINE auto{flatten}
Code: #pragma ACCEL TILE FACTOR=auto{4}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
int main()
{
  int i;
  int j;
  int k;
  int orig[8192];
  int sol[8192];
  int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_array(orig,8192);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  stencil(orig, sol, filter);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  verify(sol,8192,15);
  return 0;
}