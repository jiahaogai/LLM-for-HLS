  
 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{64}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 0; j < 240 - 1; j++) {
        double  _val_27 = 0.0;
        double  _val_28 = 0.0;
        double  _val_29 = 0.0;
        double  _val_30 = 0.0;
        double  _val_31 = 0.0;
        double  _val_32 = 0.0;
        double  _val_33 = 0.0;
        double  _val_34 = 0.0;
        double  _val_35 = 0.0;
	_val_27 = ex[i][j + 1] - ex[i][j];
	_val_28 = ey[i + 1][j] - ey[i][j];
	_val_29 = hz[i][j + 1] - hz[i][j];
	_val_30 = ex[i + 1][j + 1] - ex[i + 1][j];
	_val_31 = ey[i + 1][j + 1] - ey[i + 1][j];
	_val_32 = hz[i + 1][j + 1] - hz[i + 1][j];
	_val_33 = hz[i + 1][j] - hz[i + 1][j];
	_val_34 = hz[i][j] - hz[i][j + 1];
	_val_35 = _val_29 + _val_33;
        ey[i][j] = _val_31 + (_val_28 * _val_35);
        _ecm[i][j] = _val_32 - (_val_27 * _val_34 + _val_28 * _val_35);
        ex[i][j] = _val_30 + (_val_27 * _val_34 + _val_29 * _val_35);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (j = 0; j < 240; j++) {
        hz[i][j] = _ecm[i][j];
      }
    }
  }
}
