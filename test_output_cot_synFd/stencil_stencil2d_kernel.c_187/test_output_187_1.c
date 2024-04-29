**Variables:**
- `orig`: Array of 32-bit integers.
- `sol`: Array of 32-bit integers.
- `filter`: Array of 32-bit integers.


**Preprocessor Definitions:**
- `N`: `32`

**Included File:**
`filter.h`



#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 32 + 1 - 1; i++) {
      idx = i + j * (32 + 1);
      val = orig[idx] + filter[0] * orig[idx - 1 + (32 + 1) * -1] + filter[1] * orig[idx - 1] + filter[2] * orig[idx - 1 + (32 + 1) * 1] + filter[3] * orig[idx + (32 + 1) * -1] + filter[4] * orig[idx + (32 + 1) * 1] + filter[5] * orig[idx - 1 + (32 + 1) * 2] + filter[6] * orig[idx + (32 + 1) * 2] + filter[7] * orig[idx - 1 + (32 + 1) * -2] + filter[8] * orig[idx + (32 + 1) * -2];
      sol[idx] = val;
    }
  }
}