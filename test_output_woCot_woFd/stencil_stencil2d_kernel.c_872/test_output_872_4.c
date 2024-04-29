#pragma ACCEL kernel

int main()
{
  int orig[8192];
  int sol[8192];
  int filter[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_array(orig, 8192);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  stencil(orig, sol, filter);
  return 0;
}