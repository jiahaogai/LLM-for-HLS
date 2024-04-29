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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        ti = i + ((k % 3) - 1);
        tj = j + ((k / 3) - 1);
        tk = ((k % 3) == 0) ? 8 : 0;
        idx = ti * 256 + tj * 8 + tk;
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
    }
  }
}