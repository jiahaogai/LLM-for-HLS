#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    val = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 9; j++) {
      idx = i - 4 + j;
      if (idx < 0 || idx > 8191) {
        val += 0;
      }
       else {
        val += orig[idx] * filter[j];
      }
    }
    sol[i] = val;
  }
}