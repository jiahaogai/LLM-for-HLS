#pragma ACCEL kernel

void stencil(int orig[25][20],int sol[25][20],int filter[3][3])
{
  int i;
  int j;
  int ii;
  int jj;
  int t;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  for (i = 1; i < 24; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 19; j++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (ii = i - 1; ii <= i + 1; ii++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (jj = j - 1; jj <= j + 1; jj++) {
          t += filter[ii - (i - 1)][jj - (j - 1)] * orig[ii][jj];
        }
      }
      sol[i][j] = t;
    }
  }
//#pragma endscop
}