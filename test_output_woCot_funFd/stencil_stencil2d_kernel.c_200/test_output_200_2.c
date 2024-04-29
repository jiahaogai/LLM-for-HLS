#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int index;
  int lower;
  int upper;
  lower = 1;
  upper = 8190;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8190; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (k = -4; k < 5; k++) {
        index = (i + k) * 8192 + j;
        tmp_orig = orig[index];
        tmp_sol += filter[k + 4] * tmp_orig;
      }
      sol[index] = tmp_sol;
    }
  }
//#pragma endscop
}