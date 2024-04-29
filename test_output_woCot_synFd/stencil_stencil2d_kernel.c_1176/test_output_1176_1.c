*/

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 337; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = (((336 + 1) * (336 + 1)) * (k / 9)) + (((336 + 1) * (j - 1)) + (i - 1));
        s += ((orig[idx]) * (filter[k]));
      }
      sol[(((336 + 1) * (j - 1)) + (i - 1))] = s;
    }
  }
//#pragma endscop
}