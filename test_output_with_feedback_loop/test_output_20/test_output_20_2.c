#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
  for (j = 1; j <= q; j++) {
    tmp2 = 0.0;
    tmp4 = 0.0;
    tmp5 = 0.0;
    tmp6 = 0.0;

#pragma ACCEL PIPELINE auto{__PIPE__L2}

#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (i = 1; i <= p; i++) {
      b1 = b[i * (q + 1)];
      b2 = b[i * (q + 1) + q];
      a11 = a[i][i];
      a12 = a[i][j];
      a21 = a[j][i];
      a22 = a[j][j];
      tmp1 = s * b1;
      tmp3 = s * b2;
      tmp2 += a12 * tmp1;
      x[i] += tmp1;
      x[j] += a12 * tmp3;
      tmp4 += a11 * tmp1;
      tmp5 += a22 * tmp3;
      tmp6 += a21 * (x[i] - x[j]) + a12 * (x[j] - tmp);
    }
    x[j] = (x[j] - tmp2) / (-a22 * tmp4 + a11);
    tmp = x[j];
  }
}