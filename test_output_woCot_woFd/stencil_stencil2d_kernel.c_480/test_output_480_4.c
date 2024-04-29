#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int flatten_i;
  int flatten_j;
  int range_l;
  int range_r;
  int range_t;
  int range_b;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      flatten_i = i - 1;
      flatten_j = j - 1;
      range_l = ((flatten_i - 1) * 400) + (flatten_j - 1);
      range_r = ((flatten_i - 1) * 400) + (flatten_j + 1);
      range_t = (flatten_i - 1) * 400;
      range_b = (flatten_i + 1) * 400;
      idx = ((flatten_i * 400) + flatten_j);
      val = orig[flatten_i][flatten_j] + filter[0] * orig[range_l] + filter[1] * orig[range_j] + filter[2] * orig[range_r] + filter[3] * orig[range_t] + filter[4] * orig[range_b] + filter[5] * orig[range_t + 400] + filter[6] * orig[range_b + 400] + filter[7] * orig[range_l + 400] + filter[8] * orig[range_r + 400];
      sol[flatten_i][flatten_j] = val;
    }
  }
}