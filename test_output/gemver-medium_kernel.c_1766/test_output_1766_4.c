#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double tmp_z = 0.0;
    double Ai;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      Ai = A[i][j];
      tmp += Ai * u1[j];
      Ai = A[i][j];
      tmp_x += Ai * v1[j];
      Ai = A[i][j];
      tmp_y += Ai * v2[j];
      Ai = A[i][j];
      tmp_z += Ai * w[j];
    }

    z[i] = beta * z[i] + tmp;
    y[i] = beta * y[i] + tmp_z;
    x[i] = alpha * x[i] + tmp_x;
    double new_fi = 0.0;
    double new_fj = 0.0;
    double Aj;
    
#pragma ACCEL PARALLEL reduction=new_fj FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      Aj = A[j][i];
      new_fj += Aj * x[j];
      Aj = A[j][i];
      new_fi += Aj * y[j];
    }

    fi = fi + new_fi;
    fj = fj + new_fj;
  }
}