#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8190; j++) {
      idx = i * 8190 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + -8190)) + (filter[2] * (center + -8190 * 2))) + ((filter[3] * center) + (filter[4] * (center + -8190)) + (filter[5] * (center + -8190 * 2))) + ((filter[6] * center) + (filter[7] * (center + -8190)) + (filter[8] * (center + -8190 * 2)));
    }
  }
}