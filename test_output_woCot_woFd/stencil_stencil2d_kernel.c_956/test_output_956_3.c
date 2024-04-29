#pragma ACCEL kernel

int main()
{
  int orig[8192];
  int sol[8192];
  int filter[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  stencil(orig,sol,filter);
  return 0;
}