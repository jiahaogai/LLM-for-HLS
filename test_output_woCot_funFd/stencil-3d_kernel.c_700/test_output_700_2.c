Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[390][390][390],double sol[32][32][32])
{
  long r;
  long q;
  long p;
  long s;
  long t;
  long u;
  double B[390][390][390];
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (r = 1; r < 390 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 390 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 390 - 1; p++) {
        for (s = 0; s < 32; s++) {
          for (t = 0; t < 32; t++) {
            for (u = 0; u < 32; u++) {
              tmp = ((double )0);
              B[r][q][p] = ((double )0);
              
#pragma ACCEL PARALLEL reduction=B
              for (v = 0; v < 390; v++) {
                tmp += ((double )(orig[v][q][p])) * ((double )(u_dm[s][v]));
                B[r][q][p] += ((double )(t_dm[t][v])) * tmp;
              }
            }
          }
        }
      }
    }
  }
/* Standardize from: for(r = 1; r < 390 - 1; r++) {...} */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 390 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 390 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 390 - 1; p++) {
        sol[0][q][p] = B[r][q][p];
      }
    }
  }
/* Standardize from: for(r = 1; r < 390 - 1; r++) {...} */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 390 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 390 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{32}
      for (p = 1; p < 390 - 1; p++) {
        double tmp_1;
        double min = ((double )1e99);
        int tmp_2;
        int tmp_3;
        int tmp_4;
        int tmp_5;
        tmp_1 = sol[0][q][p];
        tmp_2 = 1;
        tmp_3 = 1;
        tmp_4 = 390 - 2;
        tmp_5 = 390 - 2;
        for (s = tmp_2; s <= tmp_4; s++) {
          for (