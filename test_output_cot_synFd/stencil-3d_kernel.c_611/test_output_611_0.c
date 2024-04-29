#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[2][2][2],long sol[2][2][2])
{
  long i;
  long j;
  long k;
  long ko;
  long kd;
  long jn;
  long jd;
  long in;
  long id;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  sum0 = 0;
  sum1 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  ko = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  while (ko < 2) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    kd = ko + 1;
    if (kd < 2) {
      ko = ko + 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      jn = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (jn < 2) {
        jd = jn + 2;
        if (jd < 4) {
          jn = jn + 1;
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          in = 0;
          
#pragma ACCEL PARALLEL FACTOR=auto{2}
          while (in < 2) {
            id = in + 2;
            if (id < 4) {
              in = in + 1;
              sum0 = ((orig[ko][kd][jd] + orig[ko][kd][id]) + (orig[ko][kd - 1][jd] + orig[ko][kd - 1][id])) + ((orig[ko - 1][kd][jd] + orig[ko - 1][kd][id]) + (orig[ko - 1][kd - 1][jd] + orig[ko - 1][kd - 1][id]));
              sum1 = (orig[ko][kd][jd + 1] + orig[ko][kd][id + 1]) + (orig[ko][kd - 1][jd + 1] + orig[ko][kd - 1][id + 1]) + (orig[ko - 1][kd][jd + 1] + orig[ko - 1][kd][id + 1]) + (orig[ko - 1][kd - 1][jd + 1] + orig[ko - 1][kd - 1][id + 1]);
              mul0 = sum0 * C0;
              mul1 = sum1 * C1;
              sol[ko][kd][jd] = mul0;
              sol[ko][kd][id] = mul1;
              sol[ko][kd - 1][jd] = mul0;
              sol[ko][kd - 1][id] = mul1;
              sol[ko - 1][kd][jd] = mul0;
              sol[ko - 1][kd][id] = mul1;
              sol[ko - 1][kd - 1][jd] = mul0;
              sol[ko - 1][kd - 1][id] = mul1;
            }
          }
        }
      }
    }
  }
}