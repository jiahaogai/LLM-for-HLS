`sol[i] = filter[0] * orig[i] + filter[1] * orig[i + 1] + ... + filter[8] * orig[i + 8]`


where the index `i` is an index into the flattened 2D array. The function iterates across the 2D array in `orig` by processing 8 elements at a time in each iteration. Each iteration also involves 8 additions and 1 multiplication.


The following figure shows a 16-element matrix that is passed to the function as the `orig` argument. Each element of the `orig` array is shown in its 1-D representation in the figure.


 
![](stencil_8c_fig01.png)


The function iterates over the 2D array by processing 8 rows at a time. The following figure shows the operation of the function on the matrix in `orig`. The blue arrows show the elements that are processed in each iteration.


 
![](stencil_8c_fig02.png)


The following figure shows the result of applying the filter kernel to the matrix in `orig`. The black arrows show the elements that are updated in each iteration.


 
![](stencil_8c_fig03.png)


The function `stencil` loops across the 2D array, flattens the 2D indices into 1D array indices, and then computes the result by applying the filter kernel.


#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 337; j++) {
      idx = i * 337 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + 1)) + (filter[2] * (center + 337))) + ((filter[3] * center) + (filter[4] * (center + 1)) + (filter[5] * (center + 337))) + ((filter[6] * center) + (filter[7] * (center + 1)) + (filter[8] * (center + 337)));
    }
  }
}