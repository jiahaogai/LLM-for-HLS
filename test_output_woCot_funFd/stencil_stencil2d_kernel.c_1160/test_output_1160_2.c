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
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp_orig = 0;
    tmp_sol = 0;
    
#pragma ACCEL PARALLEL reduction=tmp_orig FACTOR=auto{2}
    inner:
    for (j = 0; j < 9; j++) {
      filter_elem = filter[j];
      
#pragma ACCEL PARALLEL reduction=tmp_sol FACTOR=auto{1}
      middle:
      for (k = 0; k < 8; k++) {
        tmp = filter_elem * orig[i * 8 + k - 4];
        tmp_sol += tmp;
        tmp_orig += orig[i * 8 + k - 4] * tmp;
      }
    }
    sol[i] = tmp_sol;
    orig[i] = tmp_orig;
  }
}