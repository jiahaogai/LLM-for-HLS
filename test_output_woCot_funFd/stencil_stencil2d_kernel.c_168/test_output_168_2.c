#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
  int m;
  int n;
  int pad_size = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      sol[i][j] = 0.0;
      m = i - 1;
      if (m < 0) {
        m = 0;
      }
      n = j - 1;
      if (n < 0) {
        n = 0;
      }
      for (k = 0; k < 9; k++) {
        sol[i][j] += ((double )filter[k]) * orig[m][n];
        m++;
        if (m >= 400) {
          m = 399;
        }
        n++;
        if (n >= 400) {
          n = 399;
        }
      }
    }
  }
}