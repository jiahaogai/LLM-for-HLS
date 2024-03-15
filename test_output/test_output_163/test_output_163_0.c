
   
int bbgemm(double m1[4096],double m2[4096],double prod[4096])
{
  int i;
  int k;
  int j;
  int jj;
  int kk;
  int i_row;
  int k_row;
  double temp_x;
  double mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopjj:
/* Standardize from: for(jj = 0;jj < 64;jj += 8) {...} */
  for (jj = 0; jj <= 7; jj++) {
    int _in_jj = 0 + 8L * jj;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopkk:
/* Standardize from: for(kk = 0;kk < 64;kk += 8) {...} */
    for (kk = 0; kk <= 7; kk++) {
      int _in_kk = 0 + 8L * kk;
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 0; i < 64; ++i) {
        
#pragma ACCEL PIPELINE auto{}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopk:
        for (k = 0; k < 8; ++k) {
          i_row = i * 64;
          k_row = (k + _in_kk) * 64;
          temp_x = m1[i_row + k + _in_kk];
          loopj:
          for (j = 0; j < 8; ++j) {
            mul = temp_x * m2[k_row + j + _in_jj];
            prod[i_row + j + _in_jj] += mul;
          }
        }
      }
    }
    kk = _in_kk;
  }
  jj = _in_jj;
}
