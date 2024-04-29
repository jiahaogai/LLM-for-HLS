#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int fi;
  int fj;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      val = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (fi = -4; fi <= 4; fi++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (fj = -4; fj <= 4; fj++) {
          tj = fj + j;
          ti = fi + i;
          val += filter[fi + 4] * filter[fj + 4] * orig[ti * 8192 + tj];
        }
      }
      sol[i * 8192 + j] = val;
    }
  }
}