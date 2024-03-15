#pragma ACCEL kernel

void kernel_big(int tsteps,int n,double u[60][60],double v[60][60],double w[60][60],double x[60][60],double y[60][60],double z[60][60])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{112}
  for (t = 1; t <= 390; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j < 59; j++) {
        u[i][j] = ((double )0);
        v[i][j] = ((double )0);
        w[i][j] = ((double )0);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        double DU_J = 0.0;
        double DV_I = 0.0;
        double DW_I = 0.0;
        double _in_0 = 0.0;
        double _in_1 = 0.0;
        double _in_2 = 0.0;
        double _in_3 = 0.0;
        double _in_4 = 0.0;
        double _in_5 = 0.0;
        double _in_6 = 0.0;
        double _in_7 = 0.0;
        double _in_8 = 0.0;
        double _in_9 = 0.0;
        double _in_10 = 0.0;
        double _in_35 = u[i][j];
        u[i][j] = _in_35 + _in_35;
        _in_0 = u[i][j - 1];
        DU_J = _in_0 + _in_0;
        _in_1 = v[i - 1][j] ;
        DV_I = _in_1 + _in_1;
        _in_2 = w[i][j + 1];
        DW_I = _in_2 + _in_2;
        _in_3 = u[i][j + 1];
        x[i][j] = _in_3 + _in_3;
        _in_4 = v[i + 1][j] ;
        y[i][j] = _in_4 + _in_4;
        _in_5 = w[i + 1][j] ;
        z[i][j] = _in_5 + _in_5;
        _in_6 = DU_J * x[i][j];
        _in_7 = DV_I * y[i][j];
        _in_8 = DW_I * z[i][j];
        _in_9 = DU_J * y[i][j];
        _in_10 = DV_I * z[i][j];
        u[i][j] = _in_6 - _in_9;
        v[i][j] = _in_7 - _in_10;
        w[i][j] = _in_8 - _in_10;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 59; j++) {
        x[i][j] -= 0.5 * (u[i][j] - u[i][j - 1]);
        y[i][j] -= 0.5 * (v[i][j] - v[i - 1][j]);
        z[i][j] -= 0.5 * (w[i][j] - w[i][j + 1]);
      }
    }
  }
}