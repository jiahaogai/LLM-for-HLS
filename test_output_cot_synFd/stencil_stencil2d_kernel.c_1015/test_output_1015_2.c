Generated C code:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  int val;
  int up;
  int ua;
  int down;
  int da;
  int left;
  int a;
  int c;
  int right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 0; j < 32; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 0; k < 32; k++) {
      row = ((j + 0) * 32) + k;
      val = orig[row];
      up = 0;
      ua = 0;
      down = 0;
      da = 0;
      left = 0;
      a = 0;
      c = 0;
      right = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopx:
      for (flit = 0; flit < 8; flit++) {
        col = ((j + ((flit + 1) >> 1)) * 32) + k + ((flit & 1) << 2);
        if ((((flit + 1) >> 1) == 8) || (((flit + 1) >> 1) == 16)) {
          up = orig[row - 32];
          ua = filter[8];
        }
        if ((((flit + 1) >> 1) == 1) || (((flit + 1) >> 1) == 9)) {
          down = orig[row + 32];
          da = filter[9];
        }
        if (((flit >> 1) == 0) || ((flit >> 1) == 4)) {
          left = val;
          a = filter[4];
        }
        if (((flit >> 1) == 1) || ((flit >> 1) == 5)) {
          c = val;
        }
        if ((((flit + 1) >> 1) == 2) || (((flit + 1) >> 1) == 17)) {
          right = orig[col + 1];
          da = filter[5];
        }
        val = ((up + ua) + (val + a)) + ((down + da) + (right + c));
      }
      sol[row] = val;
    }
  }
}