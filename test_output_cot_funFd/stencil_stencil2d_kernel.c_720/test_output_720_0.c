#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        result = ((filter[0] * orig[i + 0 + (8 * j)]) + (filter[1] * orig[i + 1 + (8 * j)]) + (filter[2] * orig[i + 2 + (8 * j)]) + (filter[3] * orig[i + 3 + (8 * j)]) + (filter[4] * orig[i + 4 + (8 * j)]) + (filter[5] * orig[i + 5 + (8 * j)]) + (filter[6] * orig[i + 6 + (8 * j)]) + (filter[7] * orig[i + 7 + (8 * j)]) + (filter[8] * orig[i + 8 + (8 * j)])) >> 15;
        sol[i + (8 * j)] = result;
      }
    }
  }
}