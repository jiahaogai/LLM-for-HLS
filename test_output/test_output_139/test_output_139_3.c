
 #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 40; t++) {
     tmp = dt * D[0];
     D[0] = C[0] * (A[0] * u[0] + A[1] * u[1] + A[2] * u[2]) + D[0];
     D[1] = C[1] * (A[1] * u[0] + A[3] * u[1] + A[4] * u[2]) + D[1];
     D[2] = C[2] * (A[2] * u[0] + A[4] * u[1] + A[5] * u[2]) + D[2];
     q[0] = - ex[0] * D[0] + ey[0] * D[1] - hz[0] * D[2];
     q[1] = - ex[1] * D[0] + ey[1] * D[1] - hz[1] * D[2];
     q[2] = - ex[2] * D[0] + ey[2] * D[1] - hz[2] * D[2];
     p[0] = B[0] * q[0] - B[1] * q[1] + B[2] * q[2];
     p[1] = B[1] * q[0] - B[3] * q[1] + B[4] * q[2];
     p[2] = B[2] * q[0] - B[4] * q[1] + B[5] * q[2];
     r[0] += - fu[0] * u[0] - fv[0] * u[1] - fw[0] * u[2];
     r[1] += - fu[1] * u[0] - fv[1] * u[1] - fw[1] * u[2];
     r[2] += - fu[2] * u[0] - fv[2] * u[1] - fw[2] * u[2];
     u[0] += tmp * f[0];
     u[1] += tmp * f[1];
     u[2] += tmp * f[2];
     int _in_blk_0 = 0;
    int _in_blk_1 = 1;
    int _in_blk_2 = 2;
    int _in_prev = 0;
    int _in_idx = 1;
    int _out_idx = 0;
    D[_in_blk_0] = r[_out_idx++];
    D[_in_blk_1] = r[_out_idx++];
    D[_in_blk_2] = r[_out_idx++];
    Q[_in_blk_0] = p[_out_idx++];
    Q[_in_blk_1] = p[_out_idx++];
    Q[_in_blk_2] = p[_out_idx++];
    S[_in_blk_0] = u[_out_idx++];
    S[_in_blk_1] = u[_out_idx++];
    S[_in_blk_2] = u[_out_idx++];
    A[_in_blk_0][_in_blk_0] = ex[_in_idx];
    A[_in_blk_0][_in_blk_1] = ey[_in_idx];
    A[_in_blk_0][_in_blk_2] = hz[_in_idx];
    A[_in_blk_1][_in_blk_0] = ey[_in_idx];
    A[_in_blk_1][_in_blk_1] = ey[_in_prev];
    A[_in_blk_1][_in_blk_2] = hz[_in_prev];
    A[_in_blk_2][_in_blk_0] = hz[_in_idx];
    A[_in_blk_2][_in_blk_1] = hz[_in_prev];
    A[_in_blk_2][_in_blk_2] = ey[_in_prev];
    B[_in_blk_0][_in_blk_0] = q[_in_idx];
    B[_in_blk_0][_in_blk_1] = q[_in_prev];
    B[_in_blk_0][_in_blk_2] = q[_in_prev];
    B[_in_blk_1][_in_blk_0] = q[_in_prev];
    B[_in_blk_1][_in_blk_1] = q[_in_idx];
    B[_in_blk_1][_in_blk_2] = q[_in_prev];
    B[_in_blk_2][_in_blk_0] = q[_in_prev];
    B[_in_blk_2][_in_blk_1] = q[_in_prev];
    B[_in_blk_2][_in_blk_2] = q[_in_idx];
    C[_in_blk_0] = f[_in_idx];
    C[_in_blk_1] = f[_in_prev];
    C[_in_blk_2] = f[_in_prev];
  }
}
