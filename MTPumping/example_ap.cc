// ===========================================================================
// 
//       Filename:  example.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/11/2018 09:40:101 PM
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  zhenbin.wu@gmail.com
//        Company:  UIC, CMS@LPC, CDF@FNAL
// 
// ===========================================================================

#include "dsp_builtins.h"
 
#define N 10
#define M 16
 
#pragma SDS data access_pattern(a:SEQUENTIAL, b:SEQUENTIAL)
/*
#if 0
extern bool ap_clk_div2;
ap_fixed<32, 10> mult_accum(ap_fixed<16, 10> a[N][M], ap_fixed<16, 10> b[N][M]) {
#else
*/
// #ifdef __HLS_SYN__
#if 1
ap_fixed<32, 10> mult_accum(ap_fixed<16, 10> a[N][M], ap_fixed<16, 10> b[N][M], bool ap_clk_div2) {
#else
ap_fixed<32, 10> mult_accum(ap_fixed<16, 10> a[N][M], ap_fixed<16, 10> b[N][M]) {
  bool ap_clk_div2 = 0;
#endif
// #endif
  ap_fixed<32, 10> result=0;
  ap_fixed<32, 10> Accum[N];
#pragma HLS array_partition variable=a complete dim=1
#pragma HLS array_partition variable=b complete dim=1
#pragma HLS array_partition variable=Accum complete dim=1
 
  for (int i = 0; i < M; i+=2) {
          #pragma HLS pipeline
          bool clear = (i == 0);
          for(int j = 0; j < N; j++) {
          #pragma HLS unroll
            ap_fixed<16, 10> sampa1, sampa2, sampb1, sampb2;
               sampa1 = a[j][i];
               sampa2 = a[j][i+1];
               sampb1 = b[j][i];
               sampb2 = b[j][i+1];
        //      Accum = (clear) ? 0 : Accum;
               //Accum[j] = __builtin_mac16x2(sampa1, sampa2, sampb1, sampb2, 0, clear, ap_clk_div2);
        Accum[j] = __builtin_mac16x2(sampa1, sampa2, sampb1, sampb2, Accum[j], clear, ap_clk_div2);
       
 
          }
  }
 
  for (int i = 0; i < N ; i++) {
#pragma HLS unroll
    result += Accum[i];
  }
  return result;
}

ap_fixed<32, 10> mult_accum_ref(ap_fixed<16, 10> a[N][M], ap_fixed<16, 10> b[N][M], bool ap_clk_div2) {
  ap_fixed<32, 10> result=0;
  ap_fixed<32, 10> Accum[N];

  for (int i = 0; i < M; i+=2) {
          bool clear = (i == 0);
          for(int j = 0; j < N; j++) {
            ap_fixed<16, 10> sampa1, sampa2, sampb1, sampb2;
               sampa1 = a[j][i];
               sampa2 = a[j][i+1];
               sampb1 = b[j][i];
               sampb2 = b[j][i+1];
        //      Accum = (clear) ? 0 : Accum;
               //Accum[j] = __builtin_mac16x2(sampa1, sampa2, sampb1, sampb2, 0, clear, ap_clk_div2);
               Accum[j] = sampa1 * sampb1 + sampb2 * sampa2;
       
          }
  }
 
  for (int i = 0; i < N ; i++) {
    result += Accum[i];
  }
  return result;
}
