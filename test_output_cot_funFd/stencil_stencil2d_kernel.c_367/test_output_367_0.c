#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int pt;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 9; j++) {
      pt = i - 4 + j;
      if (pt < 0) {
        pt += 8192;
      }
      else {
        if (pt > 8191) {
          pt -= 8192;
        }
      }
      t += orig[pt] * filter[j];
    }
    sol[i] = t;
  }
}