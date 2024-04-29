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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp_orig = orig[i];
    tmp_sol = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0 || k > 8191) {
        filter_elem = 0;
      }
       else {
        filter_elem = filter[j];
      }
      tmp = tmp_sol;
      tmp_sol += filter_elem * orig[k];
    }
    sol[i] = tmp_sol;
  }
}