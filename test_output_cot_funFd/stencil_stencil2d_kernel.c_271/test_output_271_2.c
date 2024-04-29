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
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      val = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (fi = -4; fi <= 4; fi++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (fj = -4; fj <= 4; fj++) {
          ti = i + fi;
          tj = j + fj;
          if (ti >= 0 && ti < 256 && tj >= 0 && tj < 256) {
            val += orig[ti * 256 + tj] * filter[fi + 4] * filter[fj + 4];
          }
        }
      }
      sol[i * 256 + j] = val;
    }
  }
}