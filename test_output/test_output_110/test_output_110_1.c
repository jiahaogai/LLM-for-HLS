

7. For the inner loop, perform parallel reduction on variable "x" with the factor determined automatically:
   - Use: `#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1_2}`

8. For the outer loop, perform parallel reduction on variable "sum" with the factor determined automatically:
   - Use: `#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1_3}`

  
#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double tmp_z = 0.0;
    double AiJ;
    double uij;
    double xij;
    double yij;
    double zij;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      AiJ = A[i][j];
      uij = u1[i] * u1[j];
      xij = x[i] * x[j];
      yij = y[i] * y[j];
      zij = z[i] * z[j];
      tmp += AiJ * (uij + xij + yij + zij);
      tmp_x += AiJ * (u1[j] + xij);
      tmp_y += AiJ * (y[j] + yij);
      tmp_z += AiJ * (z[j] + zij);
    }
    z[i] = beta * z[i] + tmp;
    y[i] = beta * y[i] + tmp_x;
    x[i] = beta * x[i] + tmp_y;
    w[i] = beta * w[i] + tmp_z;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double yi = y[i];
    double xi = x[i];
    double zi = z[i];
    double uj[400];
    double vj[400];
    double mul[400];
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      uj[j] = u1[j] * yi + v1[j] * zi;
      vj[j] = u1[j] * xi + v1[j] * yi;
    }
    
#pragma ACCEL PARALLEL reduction=mul FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      mul[j] = alpha * A[i][j] * ( uj[j] + vj[j] );
    }
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      w[i] += mul[j];
    }
  }
}
