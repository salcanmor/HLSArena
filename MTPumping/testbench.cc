// ===========================================================================
// 
//       Filename:  testbench.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/11/2018 09:41:18 PM
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  zhenbin.wu@gmail.com
//        Company:  UIC, CMS@LPC, CDF@FNAL
// 
// ===========================================================================

 
#include <stdint.h>
#include "stdio.h"
#include "dsp_builtins.h"
 
#define N 10
#define M 16
 
 
// #ifdef __HLS_SYN__
#if 1
int32_t mult_accum(int16_t a[N][M], int16_t b[N][M], bool ap_clk_div2);
int32_t mult_accum_ref(int16_t a[N][M], int16_t b[N][M], bool ap_clk_div2);
#else
int32_t mult_accum(int16_t a[N][M], int16_t b[N][M]) {
  bool ap_clk_div2 = 0;
#endif
 
int main() {
  int16_t a[N][M];
  int16_t b[N][M];
  for (int i = 0; i < M; i++) {
          for(int j = 0; j < N; j++) {
               a[j][i]=i*N + j +1;
               b[j][i]=i*N + j +2;
        //a[j][i] = 1;
        //b[j][i] = 2;
          }
  }
 
  int32_t result_pump = mult_accum(a, b,0);
  int32_t result_HLS = mult_accum_ref(a, b,0);
 
  int32_t result_exp =0;
 
  for (int i = 0; i < M; i++) {
          for(int j = 0; j < N; j++) {
               result_exp = result_exp + a[j][i]*b[j][i];
          }
  }
 
 
 
    //printf("result_gold=%x\n", result_gold);
    //printf("result=%x\n", result);
    //printf("result_exp=%x\n", result_exp);
 
    //std::cout <<  "result_HLS="<< result_HLS<< std::endl;
    std::cout <<  "result_pump="<< result_pump<< std::endl;
    std::cout <<  "result_exp="<< result_exp<< std::endl;
 
  //if (result_gold == result)
    //return 0;
  return 0; 
}
