Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  int filter_row;
  int filter_col;
  int idx;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj(8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk(8) {
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_col(8) {
        k = 8 * j + k_col;
        orig_row = k - 4;
        orig_col = 8 * i - 4;
        sol_row = k;
        sol_col = i;
        sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
	loopfilter_row(9) {
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
	  loopfilter_col(9) {
	    filter_row = 4 + filter_row_tmp;
	    filter_col = 4 + filter_col_tmp;
	    idx = (orig_row + filter_row) * 8 + orig_col + filter_col;
	    sum += filter[filter_row * 9 + filter_col] * orig[idx];
	  }
	}
	sol[sol_row * 8 + sol_col] = sum;
	k_col++;
      }
    }
  }
}