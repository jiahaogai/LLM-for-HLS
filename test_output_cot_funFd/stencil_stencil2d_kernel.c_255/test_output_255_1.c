#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int fl;
  int up;
  int dn;
  int lf;
  int rt;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      fl = filter[0] * orig[i][j];
      up = orig[i - 1][j];
      dn = orig[i + 1][j];
      lf = orig[i][j - 1];
      rt = orig[i][j + 1];
      sol[i][j] = fl + up + dn + lf + rt;
    }
  }
}