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
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 32; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (((32 + 2) * (32 + 2)) * i) + (((32 + 2) * j) + k);
        s += ((double )filter[k]) * orig[idx];
      }
      sol[((32 + 2) * i) + j] = s;
    }
  }
//#pragma endscop
}