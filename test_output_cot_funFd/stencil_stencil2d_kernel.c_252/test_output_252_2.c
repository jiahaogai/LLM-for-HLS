#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int flatten_filter[81];
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 80; i < 320 - 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 80; j < 320 - 80; j++) {
      flatten_filter[(idx++)] = filter[0];
      flatten_filter[(idx++)] = filter[1];
      flatten_filter[(idx++)] = filter[2];
      flatten_filter[(idx++)] = orig[i - 80][j - 80];
      flatten_filter[(idx++)] = filter[3];
      flatten_filter[(idx++)] = filter[4];
      flatten_filter[(idx++)] = filter[5];
      flatten_filter[(idx++)] = orig[i - 80][j + 79];
      flatten_filter[(idx++)] = filter[6];
      flatten_filter[(idx++)] = filter[7];
      flatten_filter[(idx++)] = filter[8];
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (idx = 0; idx < 81; idx++) {
        sol[i][j] += flatten_filter[idx] * 4;
      }
    }
  }
}