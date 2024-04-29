#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double E[8];
  double W[8];
  double N[8];
  double S[8];
  double T[8];
  double B[8];
  double M[8];
  double A;
  double BA;
  double BB;
  double CA;
  double CB;
  double CC;
  double CD;
  double DA;
  double DB;
  double DC;
  double DD;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  vloop:
  for (int v = 0; v < 27; v++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    iloop:
    for (int i = 0; i < 3; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      jloop:
      for (int j = 0; j < 3; j++) {
        kloop:
        for (int k = 0; k < 3; k++) {
          int l = k * 3 * 3 + j * 3 + i;
          E[0] = orig[l - 3 - 3 - 1];
          E[1] = orig[l - 3 - 3];
          E[2] = orig[l - 3 - 3 + 1];
          E[3] = orig[l - 3 - 1];
          E[4] = orig[l - 3];
          E[5] = orig[l - 3 + 1];
          E[6] = orig[l - 3 + 3 - 1];
          E[7] = orig[l - 3 + 3];
          W[0] = orig[l - 3 - 3 - 1];
          W[1] = orig[l - 3 - 3];
          W[2] = orig[l - 3 - 3 + 1];
          W[3] = orig[l - 3 - 1];
          W[4] = orig[l - 3];
          W[5] = orig[l - 3 + 1];
          W[6] = orig[l - 3 + 3 - 1];
          W[7] = orig[l - 3 + 3];
          N[0] = orig[l - 1 - 3 - 1];
          N[1] = orig[l - 1 - 3];
          N[2] = orig[l - 1 - 3 + 1];
          N[3] = orig[l - 1 - 1];
          N[4] = orig[l - 1];
          N[5] = orig[l - 1 + 1];
          N[6] = orig[l - 1 + 3 - 1];
          N[7] = orig[l - 1 + 3];
          S[0] = orig[l + 1 - 3 - 1];
          S[1] = orig[l + 1 - 3];
          S[2] = orig[l + 1 - 3 + 1];
          S[3] = orig[l + 1 - 1];
          S[4] = orig[l + 1];
          S[5] = orig[l + 1 + 1];
          S[6] = orig[l + 1 + 3 - 1];
          S[7] = orig[l + 1 + 3];
          T[0] = orig[l + 3 - 3 - 1];
          T[1] = orig[l + 3 - 3];
          T[2] = orig[l + 3 - 3 + 1];
          T[3] = orig[l + 3 - 1];
          T[4] = orig[l + 3];
          T[5] = orig[l + 3 + 1];
          T[6] = orig[l + 3 + 3 - 1];
          T[7] = orig[l + 3 + 3];
          B[0] = orig[l + 3 + 3 + 1];
          B[1] = orig[l + 3 + 3];
          B[2] = orig[l + 3 + 3 - 1];
          B[3] = orig[l + 3 + 1];
          B[4] = orig[l + 3];
          B[5] = orig[l + 3 - 1];
          B[6] = orig[l + 3 - 3 + 1];
          B[7] = orig[l + 3 - 3];
          M[0] = E[0] + S[0] + C0;
          M[1] = E[1] + S[1] + C0;
          M[2] = E[2] + S[2] + C0;
          M[3] = E[3] + S[3] + C0;
          M[4] = E[4] + S[4] + C0;
          M[5] = E[5] + S[5] + C0;
          M[6] = E[6] + S[6] + C0;
          M[7] = E[7] + S[7] + C0;
          sol[l] = (M[0] + M[4]) / (2.0 * C0) - ((W[0] + N[0]) + (B[4] + T[4])) / (4.0 * C0);
          A = (M[1] + M[5]) / (2.0 * C0) - ((W[1] + N[1]) + (B[5] + T[5])) / (4.0 * C0);
          BA = B[4] - A;
          CA = C0 * A;
          BB = B[5] - A;
          CB = C0 * B[5];
          CC = C0 * B[4];
          CD = C0 * M[4];
          DA = C0 * M[1];
          DB = CB - DA;
          DC = CC - CA;
          DD = CD - DA;
          sol[l + 1] = (BA * DA + BB * DC + BB * DA + BA * DD) / (BA + BB) - (W[4] + N[4] + T[4] + B[4]) / (2.0 * C0);
          sol[l + 3] = (BA * DB + BB * DC + BB * DB + BA * DD) / (BA + BB) - (W[2] + N[2] + T[2] + B[2]) / (2.0 * C0);
          sol[l + 5] = (BB * DB + BB * DD) / (2.0 * BB) - (T[2] + B[2]) / (2.0 * C0);
          sol[l + 2] = sol[l + 1] + M[2] / (2.0 * C0);
          sol[l + 6] = sol[l + 5] + M[6] / (2.0 * C0);
          sol[l + 4] = sol[l + 3] + M[5] / (2.0 * C0);
        }
      }
    }
  }
}