#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[50],double u2[40],double v2[50],double w[50],double x[40],double y[50],double z[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L4}
    for (j = 0; j < 50; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L5}
    for (j = 0; j < 50; j++) {
      x[i] += beta * A[i][j] * y[j];
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{__PARA__L6}
    for (j = 0; j < 40; j++) {
      w[i] += alpha * A[j][i] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 40; i++) {
    z[i] = beta * z[i] + y[0] * v1[0] + y[1] * v1[1] + y[2] * v1[2] + y[3] * v1[3] + y[4] * v1[4] + y[5] * v1[5] + y[6] * v1[6] + y[7] * v1[7] + y[8] * v1[8] + y[9] * v1[9] + y[10] * v1[10] + y[11] * v1[11] + y[12] * v1[12] + y[13] * v1[13] + y[14] * v1[14] + y[15] * v1[15] + y[16] * v1[16] + y[17] * v1[17] + y[18] * v1[18] + y[19] * v1[19] + y[20] * v1[20] + y[21] * v1[21] + y[22] * v1[22] + y[23] * v1[23] + y[24] * v1[24] + y[25] * v1[25] + y[26] * v1[26] + y[27] * v1[27] + y[28] * v1[28] + y[29] * v1[29] + y[30] * v1[30] + y[31] * v1[31] + y[32] * v1[32] + y[33] * v1[33] + y[34] * v1[34] + y[35] * v1[35] + u1[0] * w[0] + u1[1] * w[1] + u1[2] * w[2] + u1[3] * w[3] + u1[4] * w[4];
  }
}