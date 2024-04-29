#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        ti = i - 4 + k;
        tj = j - 4 + k;
        tk = k - 4;
        idx = ti * 64 + tj * 8 + tk;
        val = 0;
        fit:
        for (k = 0; k < 9; k++) {
          val += filter[k] * orig[idx + k];
        }
        sol[i * 64 + j] = val;
      }
    }
  }
}