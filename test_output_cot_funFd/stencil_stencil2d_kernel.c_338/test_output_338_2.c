#pragma ACCEL kernel

void stencil(int orig[25][20][30],int sol[25][20][30],int filter[20][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        int sum = 0;
        int i;
        int j;
        int s;
        for (i = -1; i <= 1; i++) {
          for (j = -1; j <= 1; j++) {
            for (s = 0; s < 30; s++) {
              int t_c_0 = r + i;
              int t_c_1 = q + j;
              int t_c_2 = p + s;
              if (t_c_0 < 0 || t_c_0 > 24 || t_c_1 < 0 || t_c_1 > 19 || t_c_2 < 0 || t_c_2 > 29) {
                sum += 0;
              }
               else {
                sum += orig[t_c_0][t_c_1][t_c_2];
              }
            }
          }
        }
        sol[r][q][p] = sum;
      }
    }
  }
//#pragma endscop
}