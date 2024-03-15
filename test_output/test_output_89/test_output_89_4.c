
#pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double B[25][30][40],double C[20][30][50])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  double temp1;
  double temp2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (q = 0; q < 30; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (p = 0; p < 20; p++) {
        temp1 = ((double )0);
        temp2 = ((double )0);
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L5}
	for (s = 0; s < 30; s++) {
          for (t = 0; t < 40; t++) {
            temp1 += A[r][p][s] * B[r][s][t];
          }
        }
#pragma ACCEL PARALLEL reduction=C[p][q] FACTOR=auto{__PARA__L6}
	for (s = 0; s < 30; s++) {
          for (t = 0; t < 40; t++) {
            temp2 += A[r][p][s] * B[r][s][t];
          }
        }
        C[p][q] = C[p][q] + te1 * C[p][q];
        C[p][q] = temp1 + te2 * C[p][q];
      }
    }
  }
}
