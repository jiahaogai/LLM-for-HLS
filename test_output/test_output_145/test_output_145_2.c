
 #pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 16; j < 96; j++) {
     tmp = ((double )a[j]);
     b[j] = 1.0 / tmp;
     d[j] = b[j] * ((double )a[j] * x[j] - y[j]) + d[j - 16];
     for (i = 16; i < 96; i++) {
        tmp = b[i] * a[j];
        e[i] = b[j] * a[i] + tmp * e[i];
        d[i] = tmp * d[i] + b[j] * (x[j] - x[i]) + d[i];
     }
     d[j] = -d[j];
     e[j] = -e[j];
  }
  double float_temp = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 16; i++) {
    float_temp = d[i];
    y[i] = float_temp;
    b[i] = e[i] * float_temp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 16; i++) {
    y[i + 16] = b[i] + y[i + 16];
  }
}
