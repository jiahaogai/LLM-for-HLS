#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int flatten_filter[81];
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{18}
    for (j = 1; j < 400 - 1; j++) {
      flatten_filter[idx] = filter[idx];
      idx++;
    }
    idx = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = ((flatten_filter[idx]) * orig[i][j]) + ((flatten_filter[idx + 1]) * orig[i][j + 1]) + ((flatten_filter[idx + 2]) * orig[i][j + 2]) + ((flatten_filter[idx + 3]) * orig[i + 1][j]) + ((flatten_filter[idx + 4]) * orig[i + 1][j + 1]) + ((flatten_filter[idx + 5]) * orig[i + 1][j + 2]) + ((flatten_filter[idx + 6]) * orig[i + 2][j]) + ((flatten_filter[idx + 7]) * orig[i + 2][j + 1]) + ((flatten_filter[idx + 8]) * orig[i + 2][j + 2]);
      idx++;
    }
  }
}