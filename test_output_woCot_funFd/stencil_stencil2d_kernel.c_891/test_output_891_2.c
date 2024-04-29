c
#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int flatten_i;
  int flatten_j;
  int pad_size = 1;
  int index;
  int upper_bound_i = 400 - 1 + 2 * 1;
  int upper_bound_j = 400 - 1 + 2 * 1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_i:
  for (i = 1 + 1; i < upper_bound_i + 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1 + 1; j < upper_bound_j + 1; j++) {
      flatten_i = i - 1;
      flatten_j = j - 1;
      index = flatten_i * 400 + flatten_j;
      sol[i][j] = ((filter[0] * orig[i][j]) + (filter[1] * (orig[i][(j - 1)] + orig[i][(j + 1)])) + (filter[2] * (orig[(i - 1)][j] + orig[(i + 1)][j]))) + (filter[3] * orig[(i - 1)][(j - 1)]);
      sol[i][j] += ((filter[4] * orig[i][(j - 1)]) + (filter[5] * (orig[i][(j - 2)] + orig[i][(j + 2)])) + (filter[6] * (orig[(i - 1)][(j - 1)] + orig[(i - 1)][(j + 1)] + orig[(i + 1)][(j - 1)] + orig[(i + 1)][(j + 1)]))) + (filter[7] * orig[(i - 2)][(j - 1)]);
      sol[i][j] += ((filter[8] * orig[(i - 1)][(j + 1)]) + (filter[9] * (orig[(i - 2)][(j + 1)] + orig[(i + 2)][(j + 1)])) + (filter[10] * (orig[(i - 1)][(j + 2)] + orig[(i + 1)][(j + 2)])));
      sol[i][j] += ((filter[11] * orig[(i + 1)][(j + 1)]) + (filter[12] * (orig[(i + 2)][(j + 1)] + orig[(i + 2)][(j - 1)])) + (filter[13] * (orig[(i + 1)][(j - 2)] + orig[(i + 1)][(j + 2)])));
      sol[i][j] += ((filter[14] * orig[(i + 2)][(j - 1)]) + (filter[15] * (orig[(i + 2)][(j - 2)] + orig[(i + 2)][(j + 2)])) + (filter[16] * orig[(i + 2)][(j + 2)]));
    }
  }
}