

/* Eigendecomp: Eigendecomposition of a symmetric matrix.
 *
 * [V,D] = Eigendecomp(A) computes the eigendecomposition of a square matrix
 *   A. V is a matrix whose columns are the eigenvectors of A. D is a
 *   diagonal matrix whose elements are the corresponding eigenvalues of A.
 */
 #pragma ACCEL kernel

void kernel_eigendecomp(int m,double A[40][40],double D[40],double V[40][40])
{
  int i;
  int j;
  int k;
  int l;
  double b;
  double r;
  double f;
  double t;
  double b1;
  double max;
  double mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  triagloop:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    eigtkloop:
    for (k = i; k < 40; k++) {
      b = A[k][i];
      r = sqrt((((A[k][i] * A[k][i]) + (A[i][i] * A[i][i])) - (A[k][i] * A[i][k])));
      if (k == i) {
        if (b > 0.0) {
          r = -r;
        }
        D[i] = A[i][i] + r;
      }
      else {
        if (b >= 0.0) {
          f = 1.0 / (2.0 * b);
          t = f * ((A[i][i] - A[k][k]) + r);
        }
        else {
          f = -1.0 / (2.0 * b);
          t = f * ((A[i][i] - A[k][k]) - r);
        }
        D[k] = b + t;
        mul = f * A[i][k];
        eigtvlloop:
        for (j = i; j < 40; j++) {
          A[k][j] = A[k][j] - mul * A[i][j];
        }
        eigtvecloop:
        for (j = i; j < 40; j++) {
          b1 = A[j][i];
          A[j][i] = A[j][k] - mul * A[j][k];
          A[j][k] = b1;
        }
      }
      max = -3.141592653589793e+0;
      eigtvec2loop:
      for (l = 0; l < 40; l++) {
        if (l != i && l != k) {
          if (A[l][i] > max) {
            max = A[l][i];
          }
        }
      }
      vcolloop:
      for (l = 0; l < 40; l++) {
        if (l != i && l != k) {
          if (A[l][i] >= max * 0.0001) {
            mul = A[l][i] / (A[l][i] - max);
            V[l][i] = mul * V[l][i] - V[l][k];
          }
        }
      }
    }
  }
}
