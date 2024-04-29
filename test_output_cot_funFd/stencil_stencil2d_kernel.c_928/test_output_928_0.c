#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[9])
{
  int i;
  int j;
  int fl;
  int oi;
  int oj;
  int si;
  int sj;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 25 - 1; j++) {
      fl = filter[0];
      oi = i - 1;
      sj = j - 1;
      inner:
      for (si = 0; si < 9; si++) {
        oj = oi;
        fl += filter[si] * orig[oj][sj];
        sj++;
      }
      sol[i][j] = fl;
    }
  }
}