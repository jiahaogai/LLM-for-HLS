#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int fi;
  int fj;
  int fk;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      val = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{126}
      for (k = -4; k <= 4; k++) {
        ti = i + k;
        fk = 4 + k;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (j = -4; j <= 4; j++) {
          tj = j + ti;
          fj = 4 + j;
          
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{32}
          for (k = -4; k <= 4; k++) {
            tk = k + tj;
            fi = 4 + k;
            val += filter[fk * 9 + fj * 3 + fi] * orig[tk];
          }
        }
      }
      sol[i / 8 * 64 + j / 8] = val;
    }
  }
}