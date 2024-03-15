
 #pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int cmd[4104])
{
  int r;
  int q;
  int p;
  int s;
  int r_col;
  int r_row;
  int r_slice;
  int s_col;
  int s_row;
  int s_slice;
  int elem_col;
  int elem_row;
  int elem_slice;
  int tmp;
  int tmp_row;
  int tmp_col;
  int tmp_slice;
  
#pragma ACCEL PIPELINE auto{off}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    loop_q:
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      loop_p:
      for (p = 0; p < 30; p++) {
        r_col = 0;
        tmp_col = 1;
        loop_rc:
        for (r_col = 0; r_col < 5; r_col++) {
          r_row = 0;
          tmp_row = 1;
          loop_rc_row:
          for (r_row = 0; r_row < 5; r_row++) {
            s_col = 0;
            tmp_col = ((4 - r_col) * 20);
            loop_s_col:
            for (s_col = 0; s_col < 4; s_col++) {
              s_row = 0;
              tmp_row = ((4 - r_row) * 20);
              loop_s_row:
              for (s_row = 0; s_row < 4; s_row++) {
                elem_col = 0;
                tmp_col = tmp_col + 1;
                loop_ec:
                for (elem_col = 0; elem_col < 4; elem_col++) {
                  elem_row = 0;
                  tmp_row = tmp_row + 1;
                  loop_er:
                  for (elem_row = 0; elem_row < 4; elem_row++) {
                    s_slice = 0;
                    tmp_slice = ((4 - s_col) * 30);
                    loop_s_slice:
                    for (s_slice = 0; s_slice < 4; s_slice++) {
                      s_slice = s_slice + 1;
                      tmp_slice = tmp_slice + 1;
                      sum = A[r][q][p] * B[r_col][r_row][s_col][s_row][s_slice] + sum;
                    }
                  }
                  tmp_row = ((4 - elem_row) * 20);
                }
                tmp_col = ((4 - elem_col) * 20);
              }
              tmp_row = ((4 - s_row) * 20);
            }
            tmp_col = ((4 - s_col) * 20);
          }
          tmp_row = ((4 - r_row) * 20);
        }
        tmp_slice = ((4 - s_col) * 30);
      }
      A[r][q][p] = sum;
    }
  }
}
