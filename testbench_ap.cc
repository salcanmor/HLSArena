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
#include "ap_fixed.h"
#include <iostream>

#define N 10
#define M 16
 
 
// #ifdef __HLS_SYN__
#if 1
ap_fixed<32, 10> mult_accum(ap_fixed<16, 10> a[N][M], ap_fixed<16, 10> b[N][M], bool ap_clk_div2);
ap_fixed<32, 10> mult_accum_ref(ap_fixed<16, 10> a[N][M], ap_fixed<16, 10> b[N][M], bool ap_clk_div2);
#else
ap_fixed<32, 10> mult_accum(ap_fixed<16, 10> a[N][M], ap_fixed<16, 10> b[N][M]) {
  bool ap_clk_div2 = 0;
#endif
 
int main() {
  ap_fixed<16, 10> a[N][M];
  ap_fixed<16, 10> b[N][M];
  for (int i = 0; i < M; i++) {
          for(int j = 0; j < N; j++) {
               //a[j][i]=i*N /j ;
               //b[j][i]=(i*N +1)/j;
               a[j][i]=i + j +1.5;
               b[j][i]=i + j +2.5;
               std::cout << "a " << a[j][i] <<" b " << b[j][i] << std::endl;
        //a[j][i] = 1;
        //b[j][i] = 2;
          }
  }
 
  ap_fixed<32, 10> result_pump = mult_accum(a, b,0);
  ap_fixed<32, 10> result_HLS = mult_accum_ref(a, b,0);
 
  ap_fixed<32, 10> result_exp =0;
 
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
