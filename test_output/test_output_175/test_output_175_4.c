
-#pragma ACCEL kernel

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
  double D;
  double C1;
  double C2;
  double C1_2;
  double C1_4;
  double C2_2;
  double A1;
  double A2;
  double A3;
  double A4;
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
  double g;
  double h;
  double coeff;
  double _in_u;
  double _in_v;
  double _in_p;
  double _in_q;
  double _out_u;
  double _out_v;
  double _out_p;
  double _out_q;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3_0}
      for (j = 0; j < 59; j++) {
        DX = (((double )(((int )i - 1) - ((int )60 - 1))) * 1.0);
        DY = (((double )(((int )j - 1) - ((int )60 - 1))) * 1.0);
        DX_2 = DX * DX;
        DY_2 = DY * DY;
        DX_4 = DX_2 * DX_2;
        DY_4 = DY_2 * DY_2;
        D = 2.0 * (DX_2 + DY_2) - DX_4 - DY_4;
        C1 = exp(-(DX_4 - DY_4) / (2.0 * 2.10685678115243741622e-1));
        C2 = exp(-(DX_4 + DY_4) / (2.0 * 2.10685678115243741622e-1));
        C1_2 = C1 * C1;
        C1_4 = C1_2 * C1_2;
        C2_2 = C2 * C2;
//A1 = C1_4 * (D2 - D3 - D4 + D5);
//A2 = C2_4 * (D3 - D4 - A1);
//A3 = C1_4 * (D4 - D5 - A2);
//A4 = C2_4 * (D5 - D1 - A3 - A1);
        mul1 = D2 * C1_4;
        mul2 = D3 * C2_2;
        mul3 = D4 * C1_4;
        mul4 = D5 * C2_4;
        a = mul1 - mul2 - mul3 + mul4;
        b = mul2 - mul3 - a;
        c = mul3 - a;
        d = mul4 - a;
//u_t[i][j] =  a*B1 + b*B2 + c*B3 + d*B4 +u[i][j];
//v_t[i][j] =  a*B4 + b*B3 + c*B2 + d*B1  +v[i][j];
//p_t[i][j] = -a*C1 - b*C2 - c*C3 - d*C4  +p[i][j];
//q_t[i][j] = -a*D1 - b*D2 - c*D3 - d*D4  +q[i][j];
        _in_u = ((double )u[i][j]);
        _in_v = ((double )v[i][j]);
        _in_p = ((double )p[i][j]);
        _in_q = ((double )q[i][j]);
        coeff = 2.095876209165944e-05;
        A1 = coeff * C1_4 * (D2 - D3 - D4 + D5);
        A2 = coeff * C2_4 * (D3 - D4 - A1);
        A3 = coeff * C1_4 * (D4 - D5 - A2);
        A4 = coeff * C2_4 * (D5 - D1 - A3 - A1);
        _out_u = _in_u + coeff * (a * B1 + b * B2 + c * B3 + d * B4) + A1 * _in_u + A2 * _in_v + A3 * _in_p + A4 * _in_q;
        _out_v = _in_v + coeff * (a * B4 + b * B3 + c * B2 + d * B1) - (A1 + A2 + A3 + A4) * _in_u;
        _out_p = _in_p + coeff * (-a * C1 - b * C2 - c * C3 - d * C4) + (A1 * (_in_p - _in_u) + A2 * (_in_p - _in_v) + A3 * (_in_p - _in_p + _in_q) + A4 * (_in_p - _in_u - _in_v)) / 2.0;
        _out_q = _in_q + coeff * (-a * D1 - b * D2 - c * D3 - d * D4) + (A1 * (_in_q - _in_u) + A2 * (_in_q - _in_v) + A3 * (_in_q - _in_p - _in_q) + A4 * (_in_q - _in_u - _in_v)) / 2.0;
        u[i][j] = _out_u;
        v[i][j] = _out_v;
        p[i][j] = _out_p;
        q[i][j] = _out_q;
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (i = 0; i < 60; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6_1}
      for (j = 1; j < 59; j++) {
        DX = (((double )(((int )i - 1) - ((int )60 - 1))) * 1.0);
        DY = (((double )(((int )j - 1) - ((int )60 - 1))) * 1.0);
        DX_2 = DX * DX;
        DY_2 = DY * DY;
        DX_4 = DX_2 * DX_2;
        DY_4 = DY_2 * DY_2;
        D = 2.0 * (DX_2 + DY_2) - DX_4 - DY_4;
        C1 = exp