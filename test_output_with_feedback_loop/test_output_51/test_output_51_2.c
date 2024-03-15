#pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double C4[25][30],double B[25][23][30])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  double temp1;
  double mul1;
  double mul2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    loop_q:
    for (q = 0; q < 30; q++) {
      C4[r][q] = A[r][0][q] * B[r][0][q];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    loop_p:
    for (p = 1; p < 20; p++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      loop_s:
      for (s = 0; s < 30; s++) {
        C4[r][s] += A[r][p][s] * B[r][p][s];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r_1:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q_1:
    for (q = 0; q < 30; q++) {
      temp1 = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_p_1:
      for (p = 0; p < 23; p++) {
        mul1 = A[r][p][q] * B[r][p][q];
        mul2 = A[r][p][q] * C4[r][q];
        temp1 = temp1 + mul1 + mul2;
      }
      A[r][0][q] = temp1;
    }
  }
}