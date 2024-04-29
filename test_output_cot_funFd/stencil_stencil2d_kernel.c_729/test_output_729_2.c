#pragma ACCEL kernel

void stencil(double orig[4][4],double sol[4][4],double filter[3][3])
{
  int i;
  int j;
  int k;
  int jj;
  int kk;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (jj = -1; jj <= 1; jj++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (kk = -1; kk <= 1; kk++) {
          sol[i][j] += filter[jj + 1][kk + 1] * orig[i + jj][j + kk];
        }
      }
    }
  }
//#pragma endscop
}