### Function Body
 
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
  double DX_3;
  double DY_3;
  double DX_4;
  double DY_4;
  double DX_5;
  double DY_5;
  double KX;
  double KX_2;
  double KX_3;
  double KX_4;
  double KX_5;
  double KY;
  double KY_2;
  double KY_3;
  double KY_4;
  double KY_5;
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double mul5;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DY = 1.0 / ((double )60);
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_3 = DX_2 * DX;
  DY_3 = DY_2 * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_5 = DX_3 * DX_2;
  DY_5 = DY_3 * DY_2;
  KX = 2.0 * 3.141592653589793 * DX;
  KX_2 = 2.0 * 3.141592653589793 * DX_2;
  KX_3 = 2.0 * 3.141592653589793 * DX_3;
  KX_4 = 2.0 * 3.141592653589793 * DX_4;
  KX_5 = 2.0 * 3.141592653589793 * DX_5;
  KY = 2.0 * 3.141592653589793 * DY;
  KY_2 = 2.0 * 3.141592653589793 * DY_2;
  KY_3 = 2.0 * 3.141592653589793 * DY_3;
  KY_4 = 2.0 * 3.141592653589793 * DY_4;
  KY_5 = 2.0 * 3.141592653589793 * DY_5;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 40; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      DL1_1 = DX * ((double )((int )(-2)));
      DL1_2 = DX * ((double )((int )(-1)));
      DL1_3 = DX;
      DL1_4 = DX * ((double )((int )(1)));
      DL1_5 = DX * ((double )((int )(2)));
      PL1_1 = DL1_2 * DL1_2 - DL1_1 * DL1_3;
      PL1_2 = DL1_2 * DL1_3 - DL1_1 * DL1_4;
      PL1_3 = DL1_2 * DL1_4 - DL1_1 * DL1_5;
      PL1_4 = DL1_2 * DL1_5 - DL1_1 * DL1_6;
      QL1_1 = DL1_3 * DL1_3 - DL1_1 * DL1_4;
      QL1_2 = DL1_3 * DL1_4 - DL1_1 * DL1_5;
      QL1_3 = DL1_3 * DL1_5 - DL1_1 * DL1_6;
      QL1_4 = DL1_3 * DL1_6 - DL1_1 * DL1_7;
      ML1_1 = DL1_4 * DL1_4 - DL1_2 * DL1_2;
      ML1_2 = DL1_4 * DL1_5 - DL1_2 * DL1_3;
      ML1_3 = DL1_4 * DL1_6 - DL1_2 * DL1_4;
      ML1_4 = DL1_4 * DL1_7 - DL1_2 * DL1_5;
      NL1_1 = DL1_5 * DL1_5 - DL1_3 * DL1_3;
      NL1_2 = DL1_5 * DL1_6 - DL1_3 * DL1_4;
      NL1_3 = DL1_5 * DL1_7 - DL1_3 * DL1_5;
      NL1_4 = DL1_5 * DL1_8 - DL1_3 * DL1_6;
      ML2_1 = QL1_2 * QL1_2 - QL1_1 * QL1_3;
      ML2_2 = QL1_2 * QL1_3 - QL1_1 * QL1_4;
      ML2_3 = QL1_2 * QL1_4 - QL1_1 * QL1_5;
      ML2_4 = QL1_2 * QL1_5 - QL1_1 * QL1_6;
      NL2_1 = QL1_3 * QL1_3 - QL1_1 * QL1_4;
      NL2_2 = QL1_3 * QL1_4 - QL1_1 * QL1_5;
      NL2_3 = QL1_3 * QL1_5 - QL1_1 * QL1_6;
      NL2_4 = QL1_3 * QL1_6 - QL1_1 * QL1_7;
      LL2_1 = QL1_4 * QL1_4 - QL1_2 * QL1_2;
      LL2_2 = QL1_4 * QL1_5 - QL1_2 * QL1_3;
      LL2_3 = QL1_4 * QL1_6 - QL1_2 * QL1_4;
      LL2_4 = QL1_4 * QL1_7 - QL1_2 * QL1_5;
      ML3_1 = NL1_2 * NL1_2 - NL1_1 * NL1_3;
      ML3_2 = NL1_2 * NL1_3