#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}
 
#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{2}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long NX;
  long NY;
  long NZ;
  long P;
  long Q;
  long R;
  long m;
  long n;
  long o;
  long p;
  long q;
  long r;
  long s;
  long h;
  long h2;
  long h3;
  NX = 32;
  NY = 32;
  NZ = 32;
  P = 1;
  Q = 1;
  R = 1;
  m = NX + 2 * P;
  n = NY + 2 * Q;
  o = NZ + 2 * R;
  h = NX / 2 + P;
  h2 = (NY / 2 + Q) * (NX + 2 * P);
  h3 = (NZ / 2 + R) * (NY + 2 * Q) * (NX + 2 * P);
  for (i = 0; i < 32768; i++) 
    sol[i] = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (k = 0; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 32; i++) {
        idx = i + P + (j + Q) * (m) + (k + R) * h2;
        s = orig[idx] + ((i == 0) ? 1 : (i == 31) ? 1 : 0) * orig[idx - 1] + ((j == 0) ? 1 : (j == 31) ? 1 : 0) * orig[idx - m] + ((k == 0) ? 1 : (k == 31) ? 1 : 0) * orig[idx - h3];
        sol[idx] = s;
      }
    }
  }
}