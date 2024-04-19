#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DT;
  double B1;
  double B2;
  double mul1;
  double mul2;
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
//#pragma scop
  DX = 1.0 / ((double )60);
  DY = 1.0 / ((double )60);
  DT = 1.0 / ((double )40);
  B1 = 2.0;
  B2 = 1.0;
  mul1 = B1 * DT / (DX * DX);
  mul2 = B2 * DT / (DY * DY);
  a = -mul1 / 2.0;
  b = 1.0 + mul1;
  c = a;
  d = -mul2 / 2.0;
  e = 1.0 + mul2;
  f = d;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = ((double )0);
      p[i][0] = ((double )0);
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        v[i][j] = ((a * ( u[i][j + 1] - u[i][j - 1] ) ) + ( b * ( u[i + 1][j] - u[i - 1][j] ) ) + ( c * ( u[i + 1][j + 1] - u[i - 1][j - 1] ) ) + ( d * ( u[i][j] - u[i - 1][j - 1] ) ) + ( e * ( u[i + 1][j - 1] - u[i - 1][j + 1] ) )) / ((double )12.0);
        p[i][j] = ((f * ( v[i][j] - v[i][j - 1] ) ) + ( g * ( v[i][j + 1] - v[i][j - 1] ) )) / DX;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j < 59; j++) {
        u[i][j] = u[i][j] + PARA_L2;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3_0}
      for (j = 1; j < 59; j++) {
        q[i][j] = ((a * ( v[i][j] - v[i][j + 1] ) ) + ( b * ( v[i + 1][j] - v[i][j + 1] ) ) + ( c * ( v[i + 1][j + 1] - v[i][j + 1] ) ) + ( d * ( v[i][j] - v[i - 1][j + 1] ) ) + ( e * ( v[i + 1][j - 1] - v[i][j - 1] ) ) + ( f * ( v[i][j - 1] - v[i - 1][j - 1] ) )) / ((double )4.0);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3_1}
      for (j = 1; j < 59; j++) {
        v[i][j] = v[i][j] + PARA_L3;
      }
    }
  }
//End Column Sweep
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (t = 1; t <= 39; t++) {
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L4_0}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4_0}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4_0}
    for (i = 1; i < 59; i++) {
      u[i][0] = ((double )0);
      q[i][0] = ((double )0);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4_1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4_1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4_1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4_1_0}
      for (j = 1; j < 59; j++) {
        u[i][j] = u[i][j] + PARA_L4_1;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4_2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4_2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4_2}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4_