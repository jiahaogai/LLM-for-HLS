
 #pragma ACCEL PIPELINE auto{__PIPE__L0}
 
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
 
#pragma ACCEL PARALLEL FACTOR=auto{2}
 for (t = 0; t < 40; t++) {
  tmp = dt * DX;
 
#pragma ACCEL PIPELINE auto{__PIPE__L1}
 
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
 
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 39; i++) {
    sb = s[0] - e[i];
    bb = b[i] - 2 * a[i] + a[0];
    aa = a[i] - a[0];
    cc = e[i] - d[i] - aa * dp[i] / dx;
    dd = d[i] - d[0] - aa / dx * (fp[i] - fp[0] - sb * (d[0] - b[0]) / bb);
    cp[i] = cp[i] - dd * cc / (bb * dd + eps);
    dp[i] = dd + cc * cp[i] / dd;
    fp[i] = fp[i] + cc * dp[i] / dd + sb * cp[i];
    d[i] = d[i] + g[i] * tmp;
    g[i] = g[i] + aa * tmp;
    a[i] = a[i] + dp[i] * tmp;
    b[i] = b[i] + cp[i] * tmp;
    e[i] = e[i] + dd * tmp;
  }
  d[0] = 1.0;
  e[0] = 0.0;
  f[0] = 0.0;
  g[0] = 0.0;
  a[0] = 1.0;
  b[0] = 0.0;
}
