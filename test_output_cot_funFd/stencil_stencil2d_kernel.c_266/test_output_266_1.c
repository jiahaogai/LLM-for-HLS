**Optimized for:**
`[Orion_7_7_7]`

**Example:**

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
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 8; j++) {
      idx = i * 8 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[idx + ((k - 4) * 8)];
      }
      sol[idx] = val;
    }
  }
}