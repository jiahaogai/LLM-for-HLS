
- Do not compile the loop below into a parallelized loop due to: DATA DEPENDENCE
  - View EID 0 of auto pipeline 0 as:
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}

for (i = 1; i < 99; i++) {
  y[i] = 0.0;
  x[i] = 0.0;
  s[i] = 0.0;
  r[i] = 1.0 / (double )i;
  p[i] = 1.0 / (double )((int )sqrt((double )i));
  q[i] = 1.0 / (double )((int )sqrt((double )(i + 1)));
  for (j = 1; j < 99; j++) {
    y[i] += r[j] * f(p[j] * (x[j] - x[i]) + x[i]);
    s[i] += r[j] * f(p[j] * (y[j] - y[i]) + y[i]);
  }
  q_tmp = q[i];
  x[i] -= s[i] / (y[i] + q_tmp * s[i]);
  y[i] -= q_tmp * s[i];
}

  #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}

for (i = 1; i < 99; i++) {
  e[i] = (y[i] - s[i]) / (q[i] * s[i]);
  t[i] = s[i] * (1.0 - pow(2.7182818284590450907938e-01,(- 1.0) * q[i] * e[i]));
  w[i] = t[i] * f(x[i]);
}

  #pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}

for (i = 1; i < 99; i++) {
  for (j = 1; j < 99; j++) {
    x[j] += e[i] * w[j];
  }
}
