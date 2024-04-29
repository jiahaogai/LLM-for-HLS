Code: #pragma ACCEL kernel

void kernel_stencil(int tj,int ti,int C0,int C1,double orig[27][27][27],double sol[27][27][27])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 27; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 27; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (p = 0; p < 27; p++) {
        double sum = 0.0;
        i = r - 1;
        while (i < r + 2) {
          j = q - 1;
          while (j < q + 2) {
            k = p - 1;
            while (k < p + 2) {
              if (i < 0 || i > 26 || j < 0 || j > 26 || k < 0 || k > 26) {
                sum += ((double )0);
              }
              else {
                sum += orig[i][j][k];
              }
              k++;
            }
            j++;
          }
          i++;
        }
        sol[r][q][p] = sum;
      }
    }
  }
//#pragma endscop
}