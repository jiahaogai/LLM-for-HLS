#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,int nk,double A[400][500],double x1[400],double x2[500],double y_1[400],double y_2[500])
{
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{1}
    for (j = 0; j < 500; j++) {
      x1[i] += A[i][j] * y_2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{12}
    for (j = 0; j < 500; j++) {
      x2[j] += A[i][j] * y_1[i];
    }
  }
//#pragma endscop
}