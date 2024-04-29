#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[9])
{
  int i;
  int j;
  int fltr;
  int up;
  int upl;
  int dn;
  int dnl;
  int lft;
  int rht;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 25 - 1; j++) {
      up = orig[i - 1][j];
      upl = orig[i - 1][j - 1];
      dn = orig[i - 1][j + 1];
      dnl = orig[i - 1][j + 2];
      lft = orig[i][j - 1];
      rht = orig[i][j + 1];
      sol[i][j] = ((0 + up + upl + dn + dnl + lft + rht) - orig[i][j]) * filter[0] + ((up + upl) - orig[i][j]) * filter[1] + ((dn + dnl) - orig[i][j]) * filter[2] + ((lft + rht) - orig[i][j]) * filter[3] + orig[i][j] * filter[4];
    }
  }
}