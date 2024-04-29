#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int fl;
  int fm;
  int fu;
  int ml;
  int mm;
  int mu;
  int ul;
  int um;
  int uu;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 4; j++) {
      fl = orig[i - 1][j - 1];
      fm = orig[i - 1][j];
      fu = orig[i - 1][j + 1];
      ml = orig[i][j - 1];
      mm = orig[i][j];
      mu = orig[i][j + 1];
      ul = orig[i + 1][j - 1];
      um = orig[i + 1][j];
      uu = orig[i + 1][j + 1];
      sol[i][j] = ((fl + fm + fu) + (ml + mm + mu) + (ul + um + uu)) - (((2) * (ml + mm + mu)) + ((1) * (ul + um + uu)));
    }
  }
//#pragma endscop
}