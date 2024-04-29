#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[9])
{
  int i;
  int j;
  int fltr;
  int up;
  int upr;
  int dn;
  int dnr;
  int lf;
  int lfr;
  int rg;
  int rgr;
  up = 1;
  upr = 1 + 25;
  dn = 25 - 1;
  dnr = 25 - 2;
  lf = 1;
  lfr = 1 + 1;
  rg = 25 - 1;
  rgr = 25 - 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 25; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      int k_col = lf;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      while (k_col <= rg) {
        int k_row = up;
        int fltr = filter[k_col - lf];
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
        while (k_row <= dn) {
          sol[i][j] += fltr * orig[k_row][k_col];
          k_row++;
        }
        k_col++;
      }
    }
  }
}