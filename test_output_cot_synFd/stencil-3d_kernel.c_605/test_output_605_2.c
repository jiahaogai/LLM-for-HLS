#pragma ACCEL kernel

void stencil3d(char C0,char C1,double orig[27],double sol[27])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (k = 0; k < 3; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 3; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 3; i++) {
        sol[INDEX(i, j, k)] = ((C0 * orig[INDEX(i - 1, j - 1, k - 1)]) + (C1 * (orig[INDEX(i - 1, j - 1, k)] + orig[INDEX(i - 1, j, k)] + orig[INDEX(i - 1, j + 1, k)] + orig[INDEX(i, j - 1, k)] + orig[INDEX(i, j, k)] + orig[INDEX(i, j + 1, k)] + orig[INDEX(i + 1, j - 1, k)] + orig[INDEX(i + 1, j, k)] + orig[INDEX(i + 1, j + 1, k)]))) + (C0 * orig[INDEX(i + 1, j + 1, k + 1)]) + (C1 * (orig[INDEX(i, j, k + 1)] + orig[INDEX(i + 1, j, k + 1)])) + (C1 * (orig[INDEX(i + 1, j + 1, k + 1)] + orig[INDEX(i + 1, j + 1, k + 2)]));
      }
    }
  }
//#pragma endscop
}