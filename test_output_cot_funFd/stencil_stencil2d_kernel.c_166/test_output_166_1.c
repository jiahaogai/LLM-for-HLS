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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (fi = -1; fi <= 1; fi++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        inner_middle:
        for (fj = -1; fj <= 1; fj++) {
          tj = j + fj;
          ti = i + fi;
          val += filter[fj + 1] * orig[ti * 8 + tj];
        }
      }
      sol[i * 8 + j] = val;
    }
  }
}