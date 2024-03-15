 The default value for the _P_AFFINITY keyword is AUTO.
 #pragma ACCEL PIPELINE auto{__PIPE__L2}
 
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
 
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
 for (j = 1; j < 120; j++) {
  tmp = 1.0 / (1.0)...
      + 2.0;
  
#pragma ACCEL PARALLEL reduction=u FACTOR=auto{__PARA__L5}
  for (i = 1; i < 90; i++) {
    u[i] = u[i] + 1.0 / (1.0)...
        * (v[i] + v[i + 1] + v[i + 2] - u[i] - u[i + 1] - u[i + 2]);
  }
  v[1] = STENCIL_120(u);
 }
// Matrix multiplication A*B
      fori = 0;
      forj = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 1; j < 39; j++) {
      A[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (k = 1; k < 39; k++) {
        A[i][j] += B[i][k] * C[k][j];
      }
    }
  }
}
 
int main() {
   int i;
   int j;
   int k;
   int k_col;
   int i_row;
   int j_col;
   double tmp;
   double mul1;
   double mul2;
   double _in_A[39][39];
   double _in_B[39][39];
   double _in_C[39][39];
   double _out_AR[39][39];
   double _out_BR[39][39];
   double _out_CR[39][39];
   double _out_Q[39][39];
   double _out_P[39][39];
   double _out_S[39][39];
   double _out_R[39][39];
   double _out_Q1[39][39];
   double _out_P1[39][39];
   double _out_S1[39][39];
   double _out_R1[39][39];
   double _in_A_tmp_buf[39][39] = {({ 0 }) tmp_buf[j_col];
      }
      #pragma ACCEL PIPELINE auto{__PIPE__L3}
      #pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j_col = 1; j_col < 39 - 2; j_col++) {
        mul1 = _in_A[i][j_col + 1] * _in_B[j_col + 1][j];
        mul2 = _in_A[i][j_col + 2] * _in_B[j_col + 2][j];
        _out_AR[i][j] = _out_AR[i][j] - mul1 * _in_C[j_col + 1][j];
        _out_BR[i][j] = _out_BR[i][j] - mul1 * _in_C[j_col + 2][j];
        _out_CR[i][j] = _out_CR[i][j] - mul2 * _in_C[j_col + 2][j];
        _out_Q[i][j] = _out_Q[i][j] - mul1 * _out_P[j_col + 1][j];
        _out_P[i][j] = _out_P[i][j] - mul1 * _out_S[j_col + 1][j];
        _out_S[i][j] = _out_S[i][j] - mul1 * _out_R[j_col + 1][j];
        _out_R[i][j] = _out_R[i][j] - mul2 * _out_S[j_col + 2][j];
        tmp = 1.0 / (1.0)...
            - mul1.
            * mul1.
            - mul2.
            * mul2.
            + 2.0.
            * _in_A[i][j_col].
            * _in_B[j_col][j];
        _out_Q1[i][j] = tmp * _out_Q[i][j];
        _out_P1[i][j] = tmp * _out_P[i][j];
        _out_S1[i][j] = tmp * _out_S[i][j];
        _out_R1[i][j] = tmp * _out_R[i][j];
      }
    }
  }
//data consistency check
   fori = 0;
   forj = 0;
  for (i = 1; i < 39; i++) {
    for (j = 1; j < 39; j++) {
      tmp = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k_col = 1; k_col < 39; k_col++) {
        tmp += _out_A[i][k_col] * _out_B[k_col][j];
      }
      if (fabs(tmp - _out_Q[i][j]) > 1e-5) {
        assert(0);
      }
    }
  }
   fori = 0;
   forj = 0;
  for (i = 1; i < 39; i++) {
    for (j = 1; j < 39; j++) {
      tmp = 0.0;
      
#pragma ACCEL PIPELINE auto{__PIPE__L13}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L13}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L13}
      for (i_row = 1; i_row < 39; i_row++) {
        tmp += _out_A[i_row][i] * _out_P[i_row][j];
      }
      if (fabs(tmp - _out_P[i][j]) > 1e-5) {
        assert(0);
      }
    }
  }
   fori = 0;
   forj = 0;
  for (i = 1; i < 39; i++) {
    for (j = 1; j < 39; j++) {
      tmp = 0.0;
      
#pragma ACCEL PIPELINE auto{__PIPE__L14}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L14}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L14}
      for (i_row = 1; i_row < 39; i_row++) {
        tmp += _out_A[i_row][i] * _out_S[i_row][j];
      }
