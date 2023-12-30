 //#pragma ACCEL kernel

void kernel_atax(double A[3900][3900],double x[3900],double y[3900],double tmp[3900],double D[3900],double alpha,double beta,double outer_prod,double inn_prod)
{
  int i;
  int j;
  for (i = 0; i < 3900; i++) 
    y[i] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{3900}
  
#pragma ACCEL PARALLEL FACTOR=auto{3900}
  for (i = 0; i < 3900; i++) 
    tmp[i] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{3900}
  
#pragma ACCEL PARALLEL FACTOR=auto{3900}
  for (i = 0; i < 3900; i++) 
    D[i] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{3900}
  
#pragma ACCEL PARALLEL FACTOR=auto{3900}
  for (i = 0; i < 3900; i++) 
    for (j = 0; j < 3900; j++) 
      tmp[i] += A[i][j] * x[j];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{3900}
  
#pragma ACCEL PARALLEL FACTOR=auto{3900}
  for (i = 0; i < 3900; i++) 
    y[i] = beta * y[i];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{3900}
  
#pragma ACCEL PARALLEL FACTOR=auto{3900}
  for (i = 0; i < 3900; i++) 
    y[i] += alpha * (tmp[i] * inn_prod + outer_prod * D[i]);
}
