#pragma ACCEL kernel

void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 39; j++) {
      val = ((0 + filter[0]) * orig[i][j]) + ((0 + filter[1]) * orig[i][j - 1]) + ((0 + filter[2]) * orig[i][j + 1]) + ((0 + filter[3]) * orig[i - 1][j]) + ((0 + filter[4]) * orig[i - 1][j - 1]) + ((0 + filter[5]) * orig[i - 1][j + 1]) + ((0 + filter[6]) * orig[i + 1][j]) + ((0 + filter[7]) * orig[i + 1][j - 1]) + ((0 + filter[8]) * orig[i + 1][j + 1]);
      sol[i][j] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 39; j++) {
      orig[i][j] = sol[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 39; j++) {
      ti = ((5 + filter[0]) * orig[i][j]) + ((8 + filter[1]) * orig[i][j - 1]) + ((8 + filter[2]) * orig[i][j + 1]) + ((5 + filter[3]) * orig[i - 1][j]) + ((2 + filter[4]) * orig[i - 1][j - 1]) + ((2 + filter[5]) * orig[i - 1][j + 1]) + ((5 + filter[6]) * orig[i + 1][j]) + ((8 + filter[7]) * orig[i + 1][j - 1]) + ((8 + filter[8]) * orig[i + 1][j + 1]) - (4 * orig[i][j]);
      tj = ((8 + filter[0]) * orig[i][j]) + ((5 + filter[1]) * orig[i][j - 1]) + ((5 + filter[2]) * orig[i][j + 1]) + ((8 + filter[3]) * orig[i - 1][j]) + ((2 + filter[4]) * orig[i - 1][j - 1]) + ((2 + filter[5]) * orig[i - 1][j + 1]) + ((8 + filter[6]) * orig[i + 1][j]) + ((5 + filter[7]) * orig[i + 1][j - 1]) + ((5 + filter[8]) * orig[i + 1][j + 1]) - (4 * orig[i][j]);
      sol[i][j] = ((ti * ti) + (tj * tj)) / (8 * 8);
    }
  }
}