#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long NX;
  long NY;
  long NZ;
  long HX;
  long HY;
  long HZ;
  long Q0;
  long Q1;
  long Q2;
  long Q3;
  long mul1;
  long mul2;
  long P;
  NX = 32;
  NY = 32;
  NZ = 32;
  HX = 1;
  HY = 1;
  HZ = 1;
  Q0 = 1;
  Q1 = 1;
  Q2 = 1;
  Q3 = 1;
  mul1 = (-1 * Q0 * Q1 * Q2 * Q3);
  mul2 = (1 * Q0 * Q1 * Q2 * Q3);
  P = 4;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 32; k++) {
        idx = i * (NY * NZ) + j * (NZ) + k;
        sol[idx] = ((mul1 * orig[idx]) + (mul2 * ((((Q1 * (orig[idx + NZ] + orig[idx - NZ])) + (Q2 * (orig[idx + 1] + orig[idx - 1]))) + (Q3 * (orig[idx + NY] + orig[idx - NY]))) / P)));
      }
    }
  }
}