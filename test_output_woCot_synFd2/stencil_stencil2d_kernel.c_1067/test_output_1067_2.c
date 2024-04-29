Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_loc;
  int max_loc;
  int min;
  int max;
  int range;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
/* Standardize from: for(i ... ) */
    for (i = 1; i < 8191; i++) {
      t = 0;
      loopk:
/* Standardize from: for(k ... ) */
      for (k = -4; k < 5; k++) {
        if ((8192 > ((i + 4) + k))) {
          if ((5 > ((j + 4) + k))) {
            t += ((orig[((i + 4) + k) * 8192 + ((j + 4) + k)] * filter[k + 4]));
          }
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
/* Standardize from: for(j ... ) */
  loopj:
  for (j = 1; j < 8191; j++) {
/* Standardize from: for(i ... ) */
    loopi:
    for (i = 1; i < 8191; i++) {
      min_loc = 8191;
      max_loc = 0;
      min = sol[i * 8192 + j];
      max = min;
      loopk:
/* Standardize from: for(k ... ) */
      for (k = -4; k < 5; k++) {
        if ((((i + 4) + k) < 8192) && (((j + 4) + k) < 8192)) {
          if (min > sol[((i + 4) + k) * 8192 + ((j + 4) + k)]) {
            min = sol[((i + 4) + k) * 8192 + ((j + 4) + k)];
            min_loc = ((i + 4) + k);
          }
          if (max < sol[((i + 4) + k) * 8192 + ((j + 4) + k)]) {
            max = sol[((i + 4) + k) * 8192 + ((j + 4) + k)];
            max_loc = ((i + 4) + k);
          }
        }
      }
      range = (max - min) > 0 ? (max - min) : -(max - min);
      sol[i * 8192 + j] = range == 0 ? 0 : (((sol[i * 8192 + j] - min) * 255) / range);
    }
  }
}