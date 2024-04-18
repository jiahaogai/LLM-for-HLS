#pragma ACCEL kernel

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
  double C1;
  double C2;
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double a;
  double b;
  double c;
  double d;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  DY = 1.0 / ((double )60);
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
  C1 = 3.0 * DX_2 * DY_2;
  C2 = 3.0 * DX_4 * DY_4;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      d = DX_2 * (v[i][0] - 2.0 * v[i][1] + v[i][2]);
      c = DX_4 * (v[i][0] - 4.0 * v[i][1] + 3.0 * v[i][2] - 4.0 * v[i][3] + v[i][4]);
      b = DX_6 * (3.0 * v[i][1] - 6.0 * v[i][2] + 4.0 * v[i][3] - 1.0 * v[i][4] + 4.0 * v[i][5]);
      a = DX_6 * (-6.0 * v[i][1] + 12.0 * v[i][2] - 30.0 * v[i][3] + 20.0 * v[i][4] - 6.0 * v[i][5] + 4.0 * v[i][6]);
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        tmp = ((double )(((int )((a * (j - 2) + b) * (j - 2) + c) * (j - 2) + d) * (j - 2)));
        mul1 = u[i][j] - tmp * p[i][j];
        mul2 = v[i][j] - tmp * q[i][j];
        u[i][j] = mul1;
        v[i][j] = mul2;
      }
    }
//End Column Sweep
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 1; i < 59; i++) {
      d = DY_2 * (u[0][i] - 2.0 * u[1][i] + u[2][i]);
      c = DY_4 * (u[0][i] - 4.0 * u[1][i] + 3.0 * u[2][i] - 4.0 * u[3][i] + u[4][i]);
      b = DY_6 * (3.0 * u[1][i] - 6.0 * u[2][i] + 4.0 * u[3][i] - 1.0 * u[4][i] + 4.0 * u[5][i]);
      a = DY_6 * (-6.0 * u[1][i] + 12.0 * u[2][i] - 30.0 * u[3][i] + 20.0 * u[4][i] - 6.0 * u[5][i] + 4.0 * u[6][i]);
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        tmp = ((double )(((int )((a * (j - 2) + b) * (j - 2) + c) * (j - 2) + d) * (j - 2)));
        mul3 = p[i][j] - tmp * u[i][j];
        mul4 = q[i][j] - tmp * v[i][j];
        p[i][j] = mul3;
        q[i][j] = mul4;
      }
    }
  }
//End Row Sweep
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 1; i < 59; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (j = 1; j < 59; j++) {
      u[i][j] = ((double )((int )(40.0 * u[i][j])));
      v[i][j] = 0.0;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  for (i = 1; i < 59; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (j = 1; j < 59; j++) {
      p[i][j] = 1.0;
      q[i][j] = 1.0;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
  for (i = 1; i < 59; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    for (j = 1; j < 5