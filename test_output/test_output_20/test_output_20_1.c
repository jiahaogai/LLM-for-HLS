  \p2 #pragma ACCEL PIPELINE auto{off}
 
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  for (j = 1; j < 120; j++) {
     dj = ((double )j) - 1.0;
     tmpj = 0.0;
     tij = 0.0;
     si = 0.0;
     qmc = ((double )((double )4.0 * M_PI));
     _in_14:
    for (i = 1; i < 120; i++) {
      d = ((double )i) - 1.0;
      e = dj / d;
      e2 = e * e;
      u = e2;
      u = u * u;
      u = u * u;
      u = u * u;
      u = u * u;
      u = u * u;
      u = u * u;
      force = u * (e * (3.0 * sqrt(e) ) + 1.0) ;
      phi = qmc / (sqrt(d * d_jm1) * (d + d_jm1) );
      tmp = A[i] * B[j];
      si += tmp;
      tij += force * phi * tmp;
    }
     tmpj = si * D[j];
     A[j] = tmpj + tij;
  }
}
