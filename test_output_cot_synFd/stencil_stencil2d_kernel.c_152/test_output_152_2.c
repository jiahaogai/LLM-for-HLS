#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int ai;
  int aj;
  int tmp;
  int bi;
  int bj;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      tmp = 0;
      bi = i - 8;
      bj = j - 8;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (ai = 0; ai < 8; ai++) {
        
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
        for (aj = 0; aj < 8; aj++) {
          ti = bi + ai;
          tj = bj + aj;
          tmp += filter[ai * 8 + aj] * orig[ti * 8192 + tj];
        }
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}