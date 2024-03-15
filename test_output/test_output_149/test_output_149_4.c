
 #pragma ACCEL kernel

void kernel_big(int tsteps,int n,double u[60][60],double v[60][60],double w[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DT;
  double B1;
  double B2;
  double mul1;
  double mul2;
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;

  
#pragma ACCEL PIPELINE auto{off}

/* DX = 1.0/(60.0) */
  DX = 1.0 / ((double )60);
/* DY = 1.0/(60.0) */
  DY = 1.0 / ((double )60);
/* DT = 1.0/(40.0) */
  DT = 1.0 / ((double )40);
/* B1 = 2.0*D*DY*DY */
  B1 = ((double )2) * DY * DY * DX * DX;
/* B2 = 2.0*D*DX*DX */
  B2 = ((double )2) * DX * DX * DY * DY;
/* A = -D*D*DY*DY - 1.0 */
  a = (-DX * DX * DY * DY - 1.0);
/* C = -D*D*DX*DX - 1.0 */
  c = (-DX * DX * DY * DY - 1.0);
/* E = 2.0*D*DY*DY */
  e = ((double )2) * DY * DY * DX;
/* F = 2.0*D*DX*DX */
  f = ((double )2) * DX * DX * DY;
/* B0 = B1 + B2 */
  b = B1 + B2;
/* mul1 = A*B0 */
  mul1 = a * b;
/* mul2 = F*B1 - C*B2 */
  mul2 = f * B1 - c * B2;
/* P = u*/
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 40; t++) {
/* Q = V - DT*(B1*Ux - B2*Uy) */
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 59; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 1; i < 59; i++) {
        q[j][i] = v[j][i] - DT * (B1 * (u[j][i] - u[j][i - 1]) - B2 * (u[j][i] - u[j - 1][i]));
      }
    }
/* U = P + DT*( 1/2*(- 4*P + 3*Q + 2*R) - D*D*Ux - (D*D/2)*Uy ) */
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 1; j < 59; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (i = 1; i < 59; i++) {
        u[j][i] = p[j][i] + DT * (mul1 * ( - ((4 * p[j][i]) + (3 * q[j][i]) + (2 * r[j][i])) - (u[j][i] * B1) - (0.5 * u[j][i] * b * DY)) + mul2 * ( - (u[j][i] * B2) - (0.5 * u[j][i] * b * DX)));
      }
    }
/* R = W - DT*( D*D*Ux - 1.0*Uy ) */
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (j = 1; j < 59; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (i = 1; i < 59; i++) {
        r[j][i] = w[j][i] - DT * (a * (u[j][i] - u[j][i - 1]) - b * (u[j][i] - u[j - 1][i]));
      }
    }
/* V = W + DT*(1/2*(4*R - 3*P + 1*Q) - D*D*Uy - (D*D/2)*Ux ) */
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (j = 1; j < 59; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (i = 1; i < 59; i++) {
        v[j][i] = w[j][i] + DT * (mul1 * ( - (4 * r[j][i]) + (3 * p[j][i]) + (1 * q[j][i]) - (u[j][i] * B1) - (0.5 * u[j][i] * a * DY)) + mul2 * ( - (u[j][i] * B2) - (0.5 * u[j][i] * a * DX)));
      }
    }
  }
}
