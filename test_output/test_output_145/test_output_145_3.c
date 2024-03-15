
 #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 1; j < 13; j++) {
     dy[0] = dy[1];
     dy[1] = out[0] - ex[0];
     for (i = 1; i < 120; i++) {
        dy[i + 1] = dy[i] + (out[i + 1] - ex[i]);
     }
     dout = dy[119];
     ex[0] = ex[1];
     eout = ey[119];
     ey[0] = 1.0 + dex * dout;
     for (i = 1; i < 120; i++) {
        ex[i] = ex[i + 1];
        ey[i] = 1.0 / (1.0 + dex * dy[i]);
     }
     beta[j] = dout * eout;
     tmp = 1.0;
     y[0] = tmp;
     for (i = 0; i < 120; i++) {
        y[i] = tmp = y[i] - beta[j] * dy[i];
     }
     out[0] = y[0];
     for (i = 0; i < 119; i++) {
        out[i + 1] = y[i + 1] - beta[j] * dy[i + 1];
     }
  }
}
 
void kernel_jacobi_1(int tsteps,int n,double A[120][120],double B[120][120])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}

  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (t = 0; t < 40; t++) {
     
#pragma ACCEL PIPELINE auto{__PIPE__L2}
     
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
     
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (i = 1; i < 120 - 1; i++) {
       
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 120 - 1; j++) {
        B[i][j] = 0.2 * (A[i][j] - (A[i][j - 1] + A[i][1 + j] + A[i - 1][j] + A[1 + i][j]));
      }
    }
     
#pragma ACCEL PIPELINE auto{__PIPE__L3}
     
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
     
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 120 - 1; i++) {
       
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 120 - 1; j++) {
        A[i][j] = 0.2 * (B[i][j] - (B[i][j - 1] + B[i][1 + j] + B[i - 1][j] + B[1 + i][j]));
      }
    }
  }
//#pragma endscop
}
