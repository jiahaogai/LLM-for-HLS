
 #pragma ACCEL kernel

void kernel_doit(int nr,int nq,int np,double A[25][20][30],double B[25][30][40],double C[25][20][40])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (q = 0; q < 30; q++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      inner:
      for (p = 0; p < 20; p++) {
        float tmp = A[r][p][s] * B[r][s][q];
				clacc:
				for (i = 0; i < 40; i++) {
				  C[r][p][i] += tmp * A[r][p][t] * B[t][s][i];
				}
      }
    }
  }
}
