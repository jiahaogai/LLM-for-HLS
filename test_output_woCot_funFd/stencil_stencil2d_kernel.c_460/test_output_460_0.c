#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp_orig = 0;
    tmp_sol = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 9; j++) {
      filter_elem = filter[j];
      tmp = orig[i + (-4 + j)];
      tmp_orig += filter_elem * tmp;
      tmp_sol += filter_elem * tmp;
    }
    sol[i] = tmp_sol;
    orig[i] = tmp_orig;
  }
}