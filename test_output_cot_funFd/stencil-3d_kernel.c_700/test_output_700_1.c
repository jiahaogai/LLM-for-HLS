#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[390][390][390],double sol[32][32][32])
{
  long i;
  long j;
  long k;
  long t1;
  long t2;
  long t3;
  double E[390];
  double W[390];
  double N[390];
  double S[390];
  double T[390];
  double B[390];
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (i = 1; i < 390 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 390 - 1; j++) {
      for (k = 1; k < 390 - 1; k++) {
        t1 = i - 1;
        t2 = j - 1;
        t3 = k - 1;
        E[t3] = orig[t1][t2][t3 + 1];
        W[t3] = orig[t1][t2][t3 - 1];
        N[t3] = orig[t1][t2][t3 + 390];
        S[t3] = orig[t1][t2][t3 - 390];
        T[t3] = orig[t1][t2][t3 + 190];
        B[t3] = orig[t1][t2][t3 - 190];
        tmp = 0.111111 * (E[t3] + W[t3] + N[t3] + S[t3] + T[t3] + B[t3]);
        sol[i - 1][j - 1][k - 1] = tmp;
      }
    }
  }
}