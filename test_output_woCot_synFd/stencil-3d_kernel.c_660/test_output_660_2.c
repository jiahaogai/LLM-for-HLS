#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long ni;
  long nj;
  long nk;
  long hni;
  long hnj;
  long hnk;
  long kup;
  long kdown;
  long jup;
  long jdown;
  long iup;
  long idown;
  long t;
  long ht;
  long hC0;
  long hC1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  ni = 32;
  nj = 32;
  nk = 32;
  hni = 32;
  hnj = 32;
  hnk = 4;
  kup = 1;
  kdown = 1;
  jup = 1;
  jdown = 1;
  iup = 1;
  idown = 1;
  t = 1;
  ht = 4;
  hC0 = 0;
  hC1 = 0;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (k = 0; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 32; i++) {
        idx = i + j * 32 + k * 32 * 32;
        ht = ((C0 * ((((orig[idx + 1] + orig[idx + 32]) + orig[idx + 16384]) + orig[idx - 32]) + orig[idx - 16384])) + (C1 * ((((orig[idx + 32 + 1] + orig[idx + 32 + 32]) + orig[idx + 32 + 16384]) + orig[idx + 32 - 16384]))));
        sol[idx] = ht;
      }
    }
  }
//#pragma endscop
}