 The default value for the 'parallel' switch is auto{2}.
 #pragma ACCEL PIPELINE auto{off}
 
#pragma ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 32; t++) {
     dt = ((double )t) * 2.0;
     tmp = 0.0;
     dv = 0.0;
     zero = 0.0;
     rho = 0.0;
     for (i = 1; i <= 30; i++) {
        tmp += pow(f[i],2);
        l[i] = 2.0 * M_PI * y[i] * f[i];
        r[i] = 2.0 * M_PI * z[i] * f[i];
     }
     for (j = 1; j <= 30; j++) {
        if (j != 1) {
           u[j] = u[j] - b / tmp * (f[j] * g[j - 1] - f[j - 1] * g[j]);
        }
        b = s[j] - 2.0 * M_PI * (((double )(pow(sp[j],2) * u[j] * u[j] / (4.0 * M_PI * M_PI) - y[j] * u[j] * (g[j] - u[j]) / (2.0 * M_PI ) - z[j] * u[j] * (f[j] - 1.0) / (4.0 * M_PI))) + y[j] * y[j] / (4.0 * M_PI ) + z[j] * z[j] / (4.0 * M_PI )) - a / tmp * (g[j] - u[j]);
        a = a - b / tmp * (g[j] - u[j]);
        dv += f[j] * (y[j] * u[j]) - g[j] * (z[j] * u[j]);
        zero = g[j] - (((double )(sp[j] * u[j] * u[j] / (4.0 * M_PI) - y[j] * u[j])) / a);
        rho += f[j] * ((y[j] * u[j]) * (y[j] * u[j]) / (4.0 * M_PI ) + (z[j] * u[j]) * (z[j] * u[j]) / (4.0 * M_PI ) - (y[j] * zero) / a);
     }
     r[31] = 0.0;
     l[31] = 0.0;
     for (i = 30; i >= 1; i--) {
        l[i] = l[i] - b / tmp * (f[i] * g[i + 1] - f[i + 1] * g[i]);
        r[i] = r[i] - a / tmp * (g[i] - u[i]);
     }
     for (i = 1; i <= 30; i++) {
        s[i] = M_PI * (2.0 * (f[i] * u[i] - g[i]) - dv / a);
        w[i] = y[i] * u[i] - s[i];
        v[i] = z[i] * u[i] - (f[i] - 1.0) * s[i];
     }
     for (i = 1; i <= 30; i++) {
       g[i] = 2.0 * M_PI * y[i] * f[i] * u[i] / a;
       f[i] = ((f[i] * u[i]) * (g[i] - u[i]) - (y[i] * u[i]) * rho) / (g[i] - 2.0 * l[i] - r[i]);
    }
    f[31] = 1.0 - dv / a;
    g[31] = 0.0;
  }
}
