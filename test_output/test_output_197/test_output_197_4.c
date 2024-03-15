
//#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DX_2;
  double DY_2;
  double DX_4;
  double DY_4;
  double DX_6;
  double DY_6;
  double DX_8;
  double DY_8;
  double NDX;
  double NDY;
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double mul5;
  double add1;
  double add2;
  double u_pos;
  double v_pos;
  double u_neg;
  double v_neg;
  double p_pos;
  double q_pos;
  double p_neg;
  double q_neg;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  DY = 1.0 / ((double )60);
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
  DX_8 = DX_6 * DX_2;
  DY_8 = DY_6 * DY_2;
  NDX = -1.0 * DX;
  NDY = -1.0 * DY;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL WORKER FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL WORKER FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      DX_tmp = DX_2 * ((double )(4L - 2L * (long )i * (long) 1L));
      mul1 = DX_tmp * v[i][0];
      add1 = mul1 + v[i][1];
      p[i][0] = add1 + p[i][1];
      mul2 = DX_tmp * u[i][0];
      add2 = mul2 + u[i][1];
      q[i][0] = add2 + q[i][1];
      u_pos = u[i][0] + p[i][0];
      v_pos = v[i][0] + q[i][0];
      u_neg = u[i][0] - p[i][0];
      v_neg = v[i][0] - q[i][0];
      tmp = DX * DY;
      mul3 = tmp * v_pos;
      p_pos = mul3 + u_pos;
      mul4 = tmp * v_neg;
      p_neg = mul4 + u_neg;
      q_pos = mul5 = tmp * u_pos;
      q_neg = mul5 + v_neg;
      u[i][0] = u_pos + p_pos;
      v[i][0] = v_pos + q_pos;
      u[i][1] = u_pos + p_neg;
      v[i][1] = v_pos + q_neg;
      u[i][58] = u_neg + p_neg;
      v[i][58] = v_neg + q_neg;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL WORKER FACTOR=auto{1}
    for (j = 1; j < 59; j++) {
      DY_tmp = DY_2 * ((double )(4L - 2L * (long )j * (long) 1L));
      mul1 = DY_tmp * v[0][j];
      add1 = mul1 + v[1][j];
      p[0][j] = add1 + p[1][j];
      mul2 = DY_tmp * u[0][j];
      add2 = mul2 + u[1][j];
      q[0][j] = add2 + q[1][j];
      u_pos = u[0][j] + p[0][j];
      v_pos = v[0][j] + q[0][j];
      u_neg = u[0][j] - p[0][j];
      v_neg = v[0][j] - q[0][j];
      tmp = DX * DY;
      mul3 = tmp * v_pos;
      p_pos = mul3 + u_pos;
      mul4 = tmp * v_neg;
      p_neg = mul4 + u_neg;
      q_pos = mul5 = tmp * u_pos;
      q_neg = mul5 + v_neg;
      u[0][j] = u_pos + p_pos;
      v[0][j] = v_pos + q_pos;
      u[58][j] = u_neg + p_neg;
      v[58][j] = v_neg + q_neg;
    }
  }
//#pragma endscop
}
