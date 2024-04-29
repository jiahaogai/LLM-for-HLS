int main()
{
  int i;
  int j;
  int k;
  int orig[8192];
  int sol[8192];
  int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_array(orig,sol);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  stencil(orig, sol, filter);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  verify(sol);
  return 0;
}