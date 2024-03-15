
 #pragma ACCEL kernel

void kernel_gemm(double m1[4096],double m2[4096],double prod[4096])
{
  double tmp_d[4096];
  double mul;
  int i;
  int j;
  int k;

#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
  matmul:
  for (i = 0; i < 64; i++) {
    tmp_d[i] = ((double )0);
  }
  mul_lbl2:
  for (i = 0; i < 64; i++) {
    mul_lbl3:
    for (j = 0; j < 64; j++) {
      tmp_d[j] += m1[i * 64] * m2[i * 64 + j];
    }
  }
  add_lbl4:
  for (i = 0; i < 64; i++) {
    prod[i * 64] = tmp_d[i];
  }
}
