#pragma ACCEL kernel

void stencil(int orig[25][20][30],int sol[25][20][30],int filter[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (p = 0; p < 30; p++) {
        int sum = 0;
        int i;
        int j;
        int k;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{21}
	for (k = 0; k < 30; k++) {
          i = r - 1 + k;
          if (i < 0) {
            i = -i;
          }
          if (i > 24) {
            i = 48 - i;
          }
          
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
	  for (j = 0; j < 20; j++) {
            int value_i_j = orig[i][q][j];
            int weight_k = filter[k];
            sum += value_i_j * weight_k;
          }
        }
        sol[r][q][p] = sum;
      }
    }
  }
//#pragma endscop
}