#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int i;
  int j;
  int k;
  int l;
  int r;
  int q;
  int p;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (k = -12; k <= 12; k++) {
        r = i + k;
#pragma ACCEL CONDITION = r < 400 && r > 0
        {
          q = k - 12;
          tmp = q * 4;
          p = j + q;
#pragma ACCEL CONDITION = p < 400 && p > 0
          {
            filter_elem = filter[tmp];
            tmp_orig = orig[r][p] * filter_elem;
            tmp_sol += tmp_orig;
          }
        }
      }
      sol[i][j] = tmp_sol;
    }
  }
}