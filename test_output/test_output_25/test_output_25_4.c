

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
  double DX_8;
  double DY_8;
  double NDX;
  double NDY;
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
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
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      mul1 = DX_2 * ((double )((int )((++tmp))));
      mul2 = DY * ((double )(60 - 1));
      a = u[0][i] - DT * ((((u[0][i] - u[0][(i - 1)] ) + (u[0][(i + 1)] - u[0][i])) * DX_2 ) + ((v[0][i] - v[0][(i - 1)]) * (DY2 ) + ((u[0][(i + 1)] - (double )2.0f * u[0][i] + u[0][(i - 1)]) * DY ) ));
      b = v[0][i] - DT * ((((v[0][i] - v[0][(i - 1)]) + (v[0][(i + 1)] - v[0][i])) * DX_2 ) + (((q[i] - q[((i - 1) + 1)]) * DY_2 ) + (v[0][(i + 1)] - (double )2.0f * v[0][i] + v[0][(i - 1)]) * DY ) );
      c = p[i][0] - DT * ( - 1.0 * (a) * (d) + (b) * ((double )((int )((++tmp)))) );
      d = p[i][60 - 1] - DT * ( - 1.0 * (a) * (c) - 1.0 * (b) * NDX );
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        mul3 = mul1 * ((double )((int )((++tmp))));
        mul4 = mul2 * ((double )((int )((++tmp))));
        e = u[j][i] - DT * ((((u[j][i] - u[j][(i - 1)]) + (u[j][(i + 1)] - u[j][i])) * DX_2 ) + ((v[j][i] - v[j][(i - 1)]) * (DY2 ) + ((u[j][(i + 1)] - (double )2.0f * u[j][i] + u[j][(i - 1)]) * DY ) ));
        f = v[j][i] - DT * ((((v[j][i] - v[j][(i - 1)]) + (v[j][(i + 1)] - v[j][i])) * DX_2 ) + (((q[i] - q[((j - 1) + 1) * 60]) * DY_2 ) + (v[j][(i + 1)] - (double )2.0f * v[j][i] + v[j][(i - 1)]) * DY ) ));
        p[j][i] = p[j][i] - DT * (a * (p[j][i] - p[j][(i - 1)]) - b * (p[j][i] - p[j][(i + 1)]) + d * (e - p[j][(i - 1)]) - c * (f - p[j][(i + 1)]));
      }
      p[0][i] = 0.0;
      p[60 - 1][i] = 0.0;
      u[0][i] = 0.0;
      v[0][i] = 0.0;
      q[i] = 0.0;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 1; i < 59; i++) {
      mul1 = DY_2 * ((double )((int )((++tmp))));
      mul2 = DX * ((double )(60 - 1));
      a = u[i][0] - DT * ((((u[i][0] - u[i][(0 - 1)]) + (u[i][(1 + 0)] - u[i][0])) * DY_2 ) + ((v[i][0] - v[i][(0 - 1)]) * (DX2 ) + ((u[i][(1 + 0)] - (double )2.0f * u[i][0] + u[i][(0 - 1)]) * DX ) ));
      b = v[i][0] - DT * ((((v[i][0] - v[i][(0 - 1)]) + (v[i][(1 + 0)] - v[i][0])) * DY_2 ) + (((p[i][(1 + 0)] - p[i][((0 - 1) + 1)]) * DX_2 ) + (v[i][(1 + 0)] - (double )2.0f * v[i][0] + v[i][(0 - 1)]) * DX ) );
      c = p[i][0] - DT * ( - 1.0