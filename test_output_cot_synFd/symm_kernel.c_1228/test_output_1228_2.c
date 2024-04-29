Code: #pragma ACCEL kernel  
  
void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])  
{  
  int rowA;  
  int colA;  
  int rowB;  
  int colB;  
  int rowC;  
  int colC;  
  double temp1;  
  double temp2;  
  
#pragma ACCEL PIPELINE auto{off}  
  
#pragma ACCEL TILE FACTOR=auto{1}  
  
#pragma ACCEL PARALLEL FACTOR=auto{15}  
  loop_rowA:  
  for (rowA = 0; rowA < 60; rowA++) {  
    
#pragma ACCEL PIPELINE auto{}  
    
#pragma ACCEL TILE FACTOR=auto{2}  
    
#pragma ACCEL PARALLEL FACTOR=auto{32}  
    loop_colA:  
    for (colA = 0; colA < 60; colA++) {  
      temp1 = 0.0;  
      
#pragma ACCEL PARALLEL reduction = temp1 FACTOR=auto{4}  
      loop_rowB:  
      for (rowB = 0; rowB < 60; rowB++) {  
        colB = rowB;  
        temp2 = A[rowA][rowB] * B[rowB][colA];  
        temp1 += temp2;  
      }  
  
      C[rowA][colA] = alpha * temp1 + beta * C[rowA][colA];  
    }  
  }  
}