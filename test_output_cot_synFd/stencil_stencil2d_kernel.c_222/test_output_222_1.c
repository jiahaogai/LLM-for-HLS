#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((8192 * (j - 1)) + i) * 4;
      sol[result + 0] = orig[result + 0] + filter[0] * (orig[result + -8192 + 0] + orig[result + 8192 + 0]) + filter[1] * (orig[result + -1 + 0] + orig[result + 1 + 0]) + filter[2] * (orig[result + -8192 + 0] + orig[result + 8192 + 0] + orig[result + -1 + 0] + orig[result + 1 + 0]);
      sol[result + 1] = orig[result + 1] + filter[0] * (orig[result + -8192 + 1] + orig[result + 8192 + 1]) + filter[1] * (orig[result + -1 + 1] + orig[result + 1 + 1]) + filter[2] * (orig[result + -8192 + 1] + orig[result + 8192 + 1] + orig[result + -1 + 1] + orig[result + 1 + 1]);
      sol[result + 2] = orig[result + 2] + filter[0] * (orig[result + -8192 + 2] + orig[result + 8192 + 2]) + filter[1] * (orig[result + -1 + 2] + orig[result + 1 + 2]) + filter[2] * (orig[result + -8192 + 2] + orig[result + 8192 + 2] + orig[result + -1 + 2] + orig[result + 1 + 2]);
      sol[result + 3] = orig[result + 3] + filter[0] * (orig[result + -8192 + 3] + orig[result + 8192 + 3]) + filter[1] * (orig[result + -1 + 3] + orig[result + 1 + 3]) + filter[2] * (orig[result + -8192 + 3] + orig[result + 8192 + 3] + orig[result + -1 + 3] + orig[result + 1 + 3]);
    }
  }
}