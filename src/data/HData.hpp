#pragma once
#include <array>
#include "glaze/glaze.hpp"
#include "Platform.hpp"


namespace imkanji
{

constexpr auto numberOfHadamitzkyKanji = 2141ULL;

// clang-format off
constexpr std::array<const char *, numberOfHadamitzkyKanji> hadamitzkyStrings{
    // 1-100
    "2a0.1+1+3+e", "0a1.1+1+1+n", "0a2.1+1+4+n", "0a3.1+2+4,1+n", "4c0.1+1+42+e", "3s2.2+3+24,16+e", "0a4.27+4+14,1+n",
    "2j2.2+2+11,16+e", "0a2.13+1+12+n", "2o0.1+1+16+e", "0a2.15+1+12+n", "2k0.1+1+12+e", "2r2.1+5+20,11+e",
    "4c2.3+2+42,14+e", "2k1.2+1+12,2+e", "0a3.8+4+14,1+e", "4b0.1+1+43+e", "4c4.1+6+42,43+e", "4c14.1+7+42,73,39+e",
    "4d0.1+1+44+e", "3a0.1+1+21+e", "4a0.1+1+41+e", "8a0.1+1+72+e", "3b0.1+1+22+e", "0a5.25+4+41,1+n", "0a3.18+1+34+n",
    "3n0.1+1+35+n", "0a4.40+4+24,2+n", "2s7.1+5+20,64,2+e", "8d0.1+1+74+e", "2m1.2+4+14,2+n", "2m1.2+2+13,1+e",
    "0a3.2+6+16,2+n", "3o0.1+1+36+e", "5f0.1+1+58+e", "4d5.1+6+44,58+e", "2f0.1+1+8+n", "2o2.1+2+16,8+e",
    "2f2.1+6+12,8+n", "3s5.1+3+24,46,2+e", "3b3.5+2+22,37+e", "4c6.2+7+42,22,37+e", "8e4.3+5+75,42+e",
    "0a5.29+2+22,15+n", "0a6.16+4+15,12,11+n", "0a5.1+4+3,2,2+n", "2o7.3+8+16,43,8+e", "3i6.5+7+29,49,17+e",
    "2k2.2+4+12,15+e", "3b3.7+2+22,16,2+e", "2a2.10+2+3,1+e", "0a2.3+1+3+n", "0a5.22+4+36,20+n", "3d0.1+1+24+e",
    "5c0.1+1+55+e", "6e0.1+1+65+e", "3c0.1+1+23+e", "7d0.1+1+70+e", "0a7.5+2+43,2+n", "2a4.2+6+3,41+e",
    "2a5.6+6+3,41,1+e", "5c1.1+2+55,2+e", "5c2.1+1+68+n", "8e6.1+5+75,65+e", "6e2.2+6+65,9+e", "7a0.1+1+67+e",
    "7a7.6+7+67,24,14+e", "3i3.1+6+29,4,2+e", "0a7.6+4+62,1+n", "4h0.1+1+48+e", "0a8.9+4+41,42+n", "0a6.20+4+24,14,2+n",
    "0a5.5+6+13,1,2+n", "2k7.1+2+12,20,16+e", "0a5.20+9+38,12+n", "3d2.15+9+24,12+e", "3n3.3+2+35,39+e", "5a0.1+1+53+e",
    "4g4.2+6+47,27+e", "0a8.15+4+24,39,12+n", "0a3.14+1+30+n", "3d3.12+9+24,30+e", "2m3.1+6+13,30+e", "0a4.23+4+3,20+n",
    "0a6.6+8+30,13,1+n", "2d8.15+10+7,54,24+e", "2a8.14+7+3,54,24+e", "0a5.24+4+12,16,1+n", "2a4.16+2+3,46+e",
    "3s3.1+3+24+e", "2r6.1+4+43,24+n", "2q8.7+11+19,43,24+e", "4d8.8+12+44,32,15+e", "0a4.2+4+14,2,2+n",
    "0a8.2+2+57,13,4+n", "0a9.5+2+44,32,1+n", "4k0.1+1+51+e", "4k5.4+6+51,22,15+e", "5f4.4+2+58,51+e", "2g0.1+1+8+e",
    // 101-200
    "5f2.2+2+58,8+e", "3e0.1+1+25+e", "2c0.1+1+6+e", "3e2.1+6+25,6+e", "3m3.1+2+33,25+e", "3m7.6+12+33,41,25+e",
    "2r3.1+4+43,2+n", "8d5.2+2+74,42,2+e", "3n4.2+12+35,20,6+e", "3m2.1+2+33,6+e", "2j2.4+2+11,12+e", "0a5.36+4+25,2+n",
    "2o2.3+2+16,12+e", "2j4.3+2+11,16,12+e", "4a6.24+7+21,25,15+e", "0a6.25+2+25,15,2+n", "3a6.20+7+21,25,15+e",
    "3b3.1+6+22,12,2+e", "3a3.4+6+21,12,2+e", "2a3.4+6+3,12,2+e", "5b0.1+1+54+e", "2a5.1+6+3,54+e",
    "3a5.20+7+21,22,17+e", "5d3.1+6+56,24+e", "5d2.2+6+56,17+e", "2o2.2+2+16,17+e", "4a4.1+6+41+e", "4a8.39+8+41+e",
    "6f0.1+1+66+e", "6f6.1+2+66,39,12+e", "4c6.6+2+42,22,39+e", "5b8.2+12+54,42,51+e", "7c0.1+1+69+e",
    "0a6.8+4+15,12,1+n", "3a4.16+7+21,15,1+e", "2p8.1+9+18,42,35+e", "0a4.5+2+4,16+n", "3n3.2+12+35,16,1+e",
    "0a3.6+1+38+n", "3m5.12+12+33,38,16+e", "0a4.21+4+34,1+n", "0a7.9+4+42,22+n", "4f7.1+6+46,42,22+e",
    "3n1.1+4+35,2+e", "5c4.7+4+55,35,2+e", "4a5.3+6+41,55+e", "4k9.18+13+51,55,41+e", "2o7.2+12+16,55,14+e",
    "2q9.14+11+19,55,16+e", "2q7.18+11+19,43,1+e", "7d6.5+7+70,49,24+e", "4m0.1+1+40+e", "4m4.3+6+40,50+e",
    "3b9.6+7+22,42,27+e", "4f1.1+2+46,2+e", "2a5.19+7+3,46,2+e", "2a7.1+6+3,67+e", "2a4.19+12+3,4,17+e",
    "2a4.18+12+3,24,1+e", "6f6.12+12+66,24,3+e", "8e0.1+1+75+e", "8e3.1+5+75,24+e", "3d7.10+2+24,68+e",
    "4c4.13+4+42,22,2+e", "3m7.1+2+33,27,10+e", "3m6.4+12+33,22,17+e", "3r6.3+9+40,22,17+e", "3q5.4+9+18,24,13+e",
    "2m7.2+12+13,44,24+e", "3r4.4+9+40,24,1+e", "3r5.3+9+40,24,12+e", "2k3.1+2+12,24+e", "4i5.2+10+49,24,12+e",
    "5b8.3+10+54,41,50+e", "5b11.1+10+54,68,41+e", "7b8.7+13+68,50+e", "0a5.23+9+40,12+n", "3m3.4+2+33,12,2+e",
    "3m8.3+8+33,42,3+e", "6a4.4+6+61,18,12+e", "2j3.1+2+11,26+e", "5f2.1+6+58,14+e", "2t2.1+14+20,12+e", "0a2.4+1+14+n",
    "5f7.4+2+58,62,2+e", "3i9.2+15+29,22,4+e", "3i8.2+15+29,41,4+e", "2d8.13+6+7,42,22+e", "2j6.3+12+11,24,35+e",
    "2j8.6+12+11,24,20+e", "4a3.11+6+41,37+e", "2a3.6+6+3,37+e", "2d7.12+6+7,39,24+e", "3n6.3+4+35,55,2+e",
    "2f4.1+15+16+e", "3k3.3+12+32,16,1+e", "2a6.13+7+3,32,16+e", "2r4.2+5+20,24,1+e", "3d3.10+2+24,20,2+e",
    "0a6.11+2+36,20,1+n",
    // 201-300
    "3a9.25+7+21,32,36+e", "2k3.4+4+14,16,1+n", "3m5.4+2+33,34,4+e", "2n4.1+2+15,40,2+e", "4c1.3+2+42,2+e",
    "4d7.2+2+44,42,22+e", "3b4.10+2+22,16+e", "4b4.10+2+43,22,1+e", "4k8.9+7+51,43,22+e", "4c4.12+10+42,15,2+e",
    "6a3.7+6+61,15,2+e", "3h0.1+1+28+e", "0a5.19+2+34,15+n", "3d5.14+10+24,34,15+e", "3d9.27+16+24,34,15+e",
    "3h1.1+6+28,2+e", "3h8.3+7+28,64,17+e", "3h7.2+6+28,5+e", "3g6.1+6+27,64+e", "2t5.2+14+20,34,15+e",
    "4h7.3+7+48,34,15+e", "4h6.4+7+48,15,3+e", "2a4.20+4+3,20+e", "6b0.1+1+62+e", "4i9.1+10+49,62,25+e",
    "9a9.1+10+76,62,34+e", "0a9.18+12+69,1,2+n", "5d9.1+6+56,69,1+e", "0a6.5+4+30+n", "3d6.15+8+24+e",
    "2g9.1+6+8,69,2+e", "2a11.1+15+3,69,8+e", "3n4.3+15+35,20,8+e", "2k6.1+7+12,8+e", "4i7.6+16+49,14,8+e",
    "0a11.5+7+42,22,14+n", "3a6.16+7+21,24,12+e", "7a6.8+7+67,24,12+e", "3p4.3+12+22,20,16+e", "7b0.1+1+68+e",
    "5g7.2+2+55,68+e", "6a0.1+1+61+e", "6a7.5+7+61,22,20+e", "7a7.9+7+67,22,20+e", "4i6.1+6+49,22,6+e",
    "2j6.4+12+11,43,17+e", "3a7.10+7+21,11,17+e", "4c2.1+2+42,12+e", "3k6.13+12+32,42,12+e", "3k2.1+2+32,1,2+e",
    "3k6.19+2+32,41,3+e", "0a5.37+4+32,1,2+n", "3k9.21+12+32,41,1+e", "2a2.6+6+3,13+e", "3k4.7+8+32,3,13+e",
    "2a3.3+6+3,52+e", "2j7.3+12+11,49,16+e", "2j8.2+12+11,51,16+e", "4i10.1+12+49,51,35+e", "2h6.12+12+9,35,20+e",
    "4n2.1+11+52,15+e", "4k9.21+2+51,52,24+e", "4c8.10+2+42,65,9+e", "2h2.3+9+9,12+e", "4b2.3+9+43,12+e",
    "3d2.10+2+24,14+e", "2f5.3+10+16,24,15+e", "3b3.8+9+22,12,2+e", "2c3.1+9+6,12,2+e", "4i4.2+2+49,22,1+e",
    "6a4.12+2+61,22,1+e", "0a8.6+4+57,4+n", "2j11.2+2+11,57,42+e", "3s6.1+2+24,14,16+e", "2m3.3+4+38,1,1+n",
    "9a7.6+10+76,24,16+e", "9a9.3+10+76,54,31+e", "5b6.4+2+54,22,15+e", "0a13.3+12+16,46,1+e", "3g0.1+1+27+e",
    "4g0.1+1+47+e", "4g6.1+7+47,22,37+e", "10a0.1+1+78+e", "10a4.4+6+78,40,2+e", "11b0.1+1+80+e", "3o7.9+2+36,40,1+e",
    "0a4.33+4+12,1,2+n", "2o4.1+2+16,46+e", "3a6.19+7+21,46,16+e", "11a0.1+1+79+e", "2o11.3+12+16,46,52+e",
    "7a13.4+7+67,46,52+e", "7a8.13+7+67,32,3+e", "4f0.1+1+46+e", "4f0.2+4+46,2+e", "3m5.2+2+33,46,2+e",
    "4f5.9+12+46,42,2+e", "4f7.3+6+46,68+e", "6a9.7+7+61,42,21+e", "3n6.2+2+35,42,12+e",
    // 301-400
    "4n9.2+10+52,42,35+e", "2n4.2+2+15,39,2+e", "2n7.2+12+15,51,39+e", "4k7.17+2+51,38,24+e", "0a5.26+4+41,1+n",
    "0a5.27+4+41,1+n", "3d5.3+6+24,41,1+e", "4e3.1+6+45,22+e", "0a5.39+4+42,2+n", "4e5.1+6+45,42,2+e",
    "0a5.28+4+34,15+n", "8a5.6+6+72,34,15+e", "8a6.3+6+72,77+e", "4a6.5+6+41,77+e", "0a4.31+4+34,1+n",
    "3e8.6+7+25,39,26+e", "2f8.8+7+16,39,26+e", "2k2.1+2+12,9+e", "6b4.4+6+62,12,2+e", "5d4.3+6+56,12,2+e",
    "0a7.3+1+77+n", "8b0.1+1+77+e", "8b4.1+6+77,49+e", "2p2.2+9+18,9+e", "8b4.5+6+77,18,9+e", "3m5.6+2+33,40,20+e",
    "8b8.3+7+77,33,40+e", "6f8.12+12+66,33,40+e", "5d2.1+6+56,16+e", "2a7.5+6+3,42,14+e", "2a6.2+6+3,24,12+e",
    "0a5.38+4+24,12+n", "2a3.2+6+3,22+e", "2a4.9+6+3,46+e", "4a11.18+6+41,73,15+e", "4a8.11+6+41,24,14+e",
    "3d2.13+11+24,15+e", "4c2.5+11+42,15+e", "3s4.3+3+24,12,2+e", "7a2.1+6+67,12+e", "8a2.3+6+72,12+e",
    "7a8.16+6+67,43,24+e", "0a8.7+4+42,14,20+n", "3a11.13+7+21,42,33+e", "6a6.8+7+61,3,4+e", "6a6.7+7+61,24,3+e",
    "5b4.3+2+54,42+e", "4c9.2+7+42,54+e", "8e9.5+5+75,54,42+e", "7b12.2+16+68,54,42+e", "3c10.12+7+23,68,24+e",
    "0a5.33+4+34,20+n", "4c5.1+6+42,34,20+e", "3k5.5+2+32,34,20+e", "9a9.7+4+76,42,14+e", "3m5.8+2+33,14,3+e",
    "3a4.6+6+21,34,1+e", "3a5.16+7+21,46,2+e", "4a9.29+12+41,42,5+e", "3k13.15+12+32,41,42+e", "2a5.10+6+3,15,13+e",
    "4c5.3+6+42,15,13+e", "2s7.2+7+20,9,18+e", "0a5.35+4+42,2+n", "3a5.6+6+21,42,2+e", "2j5.5+10+11,37,12+e",
    "0a6.27+4+42,16+n", "2o6.5+2+16,32,20+e", "2o14.2+2+16,24,18+e", "2p11.1+2+18,57,42+e", "0a3.12+1+28+n",
    "7a3.5+6+67,28+e", "6a3.5+6+61,28+e", "3b7.11+4+22,28,13+e", "3i8.4+7+29,42,37+e", "3i4.2+7+29,20,9+e",
    "6c5.4+7+63,24,16+e", "3q6.1+9+18,32,9+e", "3a9.35+6+21,32,18+e", "3q7.4+9+18,32,26+e", "5i5.3+9+60,14,20+e",
    "4k13.5+7+51,54,42+e", "2a13.6+7+3,54,42+e", "4j0.1+1+49+e", "2b5.1+6+5,49+e", "6e12.1+6+65,42,52+e",
    "4b6.15+16+43,17,13+e", "4k10.14+12+51,43,17+e", "4d10.6+13+43,44,17+e", "3d2.12+4+24,14+e", "3a5.30+6+21,24,14+e",
    "2a5.21+6+3,24,14+e", "3k7.10+8+32,24,3+e", "3k5.30+2+32,24,14+e", "4j10.2+10+49,24,14+e", "3d7.1+6+24,68+e",
    "0a4.12+2+14,1,2+n", "9a4.5+10+76,14,1+e", "3j4.1+10+31,32,1+e", "8e4.6+5+75,32,1+e",
    // 401-500
    "8e3.3+5+75,12,2+e", "8e6.7+5+75,34,16+e", "", "7a7.12+7+67,24,16+e", "2o7.4+12+16,46,34+e", "",
    "4a10.25+7+41,46,16+e", "6f5.5+2+66,28,2+e", "2o5.1+2+16,28,2+e", "3d2.9+2+24,16+e", "3e5.8+7+25,26,11+e",
    "3e5.4+6+25,41,1+e", "", "", "3f7.2+16+26,40,20+e", "", "", "2j9.7+12+11,24,16+e", "2q9.18+11+19,24,20+e",
    "3b2.2+2+22,17+e", "", "", "", "", "3e6.11+2+25,24,14+e", "", "", "2k8.1+12+12,55,16+e", "2k6.2+2+12,55,2+e", "",
    "", "", "2f6.1+6+16,47,20+e", "", "", "3i7.1+7+29,22,13+e", "3n5.3+2+35,13,11+e", "", "7c4.3+7+69,4,17+e",
    "2a4.14+7+3,4,17+e", "", "8c4.2+2+73,41+e", "2q8.1+11+19,73+e", "", "2q9.10+11+19,69,20+e", "2q7.2+11+19,69+e",
    "2q6.9+11+19,34,16+e", "2q4.5+11+19,18,9+e", "3b4.7+6+22,18,9+e", "", "", "2q4.3+11+19,50+e",
    "2q10.4+11+19,57,22+e", "3s7.10+3+24,57,22+e", "2q9.8+11+19,46,22+e", "4b8.11+10+43,32,4+e", "",
    "3c6.8+7+23,22,37+e", "3i6+7+29,22,37+e", "", "5f4.7+2+58,3,16+e", "3c5.22+7+23,24,8+e", "", "3m9.3+12+33,32,22+e",
    "", "6a5.9+7+61,49,2+e", "4i2.1+2+49,2+e", "4c5.13+4+42,34,4+e", "4i7.5+12+49,55,14+e", "5d4.1+6+56,44+e", "", "",
    "", "", "3a9.8+15+21,42,43+e", "", "4b8.12+10+43,42,12+e", "4c5.15+2+42,40,1+e", "2j6.1+8+11,30,3+e", "", "", "",
    "", "6b6.9+12+62,34,20+e", "2m2.2+4+13,11+e", "", "4n9.5+2+52,35,13+e", "", "2p12.4+9+18,41,13+e", "", "",
    "4i5.1+6+49,38,1+e", "", "6a6.5+7+61,22,24+e", "", "0a8.8+4+42,41+n", "7a8.2+6+67,42,41+e", "", "3m3.2+2+33,37+e",
    "",
    // 501-600
    "3d2.11+2+24,17+e", "3a5.28+7+21,24,17+e", "3e5.9+7+25,24,17+e", "3n7.2+12+35,24,16+e", "3n8.4+12+35,24,22+e", "",
    "0a8.1+6+4,13,1+n", "", "", "0a7.8+4+41,24+n", "2q7.4+11+19,41,24+e", "", "", "", "", "", "", "4b8.4+6+43,44,4+e",
    "2n7.1+2+15,68+e", "", "", "", "", "7e3.2+6+71,28+e", "", "3a7.1+6+21,71+e", "", "", "0a5.16+4+51,2+n", "", "",
    "0a9.19+4+41,32,1+n", "", "4n3.2+17+52,38+e", "7a6.18+6+67,52,38+e", "3d12.13+4+24,34+e", "4a12.1+6+41,52,17+e", "",
    "0a9.4+4+10,21,1+n", "", "10a8.4+7+78,24,3+e", "", "2n4.3+2+15,18,7+e", "", "", "", "", "", "2i3.1+2+20,12,1+e",
    "2k4.4+4+22+n", "", "2k4.5+4+22+n", "3k5.12+2+32,24,12+e", "3k5.24+12+32,24,12+e", "", "7c5.3+7+69,22,9+e",
    "6a5.11+7+61,22,9+e", "3a8.30+7+21,11,12+e", "", "", "", "", "", "", "3a10.17+7+21,32,24+e", "", "3s4.1+3+24,41+e",
    "", "", "2a5.15+6+3,18,12+e", "", "", "", "", "0a4.25+4+18,12+n", "3e8.4+7+25,42,18+e", "", "", "", "",
    "3p0.1+1+22+e", "", "", "", "4a6.35+16+41,12,20+e", "", "", "2a6.24+12+3,51,1+e", "", "", "3c2.2+6+23,17+e", "", "",
    "", "", "4c5.14+13+43,13,2+e", "2d9.6+7+7,42,13+e", "", "", "2b4.5+6+39+n",
    // 601-700
    "4c7.11+13+42,39,2+e", "", "7a8.7+7+67,44+e", "", "", "", "4a12.8+7+41,34,24+e", "", "10a5.2+7+78,46,2+e", "", "",
    "3c8.15+7+23,35,20+e", "", "", "3n9.3+12+35,68,20+e", "", "", "", "2a9.4+15+3,68,16+e", "", "", "", "",
    "2d7.9+7+7,33,4+e", "", "", "4e6.3+4+45,30,9+e", "2d11.1+6+7,45,30+e", "", "4e1.1+6+45,2+e", "",
    "4e5.4+7+45,43,1+e", "", "4a5.32+12+41,43,1+e", "", "", "2b8.3+7+5,35,37+e", "", "0a4.18+4+34,2+n", "", "", "", "",
    "", "4c9.4+7+42,35,4+e", "", "", "4c8.5+4+42,22,2+e", "", "", "", "", "", "0a3.28+4+12,2+n", "4d11.4+13+44,22,16+e",
    "", "2d8.4+7+7,22,16+e", "", "", "", "0a10.11+10+52,30,4+n", "", "", "", "", "", "", "2o10.1+12+16,55,46+e", "", "",
    "", "", "", "4b10.9+16+43,22,39+e", "", "", "", "3i6.1+6+29,39,12+e", "", "3a9.13+6+21,32,28+e", "", "", "", "", "",
    "", "", "", "", "", "", "5e2.1+6+57,8+e", "", "", "", "4b4.6+6+43,7,9+e", "3b5.9+2+54,12,1+n",
    "3b9.16+10+54,12,7+n", "", "",
    // 701-800
    "5b8.4+16+54,24,12+e", "", "3d4.18+2+24,22,2+e", "", "3a6.12+6+21,14,1+e", "3a3.5+6+21,14,1+e", "3q2.1+9+18,17+e",
    "", "", "", "3m8.7+12+33,51,16+e", "3a11.1+6+21,79+e", "", "", "2q9.17+11+19,46,40+e", "", "", "", "", "", "",
    "2g3.1+6+8,24+e", "", "", "3b11.3+7+22,58,42+e", "", "", "3a9.37+6+21,52,24+e", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "4c5.7+2+42,22,15+e", "", "", "", "", "2n8.1+4+15,24,16+e", "4c8.3+7+42,24,15+e", "", "", "",
    "", "", "6a6.11+7+61,40,15+e", "6a8.2+6+61,41,42+e", "", "7b8.6+13+68,34,1+e", "3p4.4+2+22,40,2+e", "",
    "7b5.9+13+68,52,3+e", "7b5.4+2+68,28,16+e", "7b6.7+13+68,49,5+e", "", "", "", "", "", "", "", "", "", "",
    "5f5.4+13+58,18,8+e", "", "", "", "3k5.28+12+32,42,1+e", "", "2a8.22+7+3,42,32+e", "", "", "", "", "", "", "", "",
    "", "2q2.3+11+19,3+e", "", "", "", "", "", "", "", "", "", "3q7.2+9+18,22,3+e",
    // 801-900
    "2j6.2+2+11,3,12+e", "", "", "", "", "", "3d4.23+4+24,39,2+e", "", "", "4b7.2+6+43,27,10+e", "", "2m3.5+6+13+e", "",
    "2q12.3+11+19,28,32+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "3k10.14+12+32,55,30+e", "", "",
    "2q10.5+11+19,24,12+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "2b5.3+7+5,3,1+e", "",
    "", "", "", "", "", "", "", "", "", "", "", "3a7.16+7+21,43,35+e", "", "", "5c6.1+6+55,77+e", "", "", "", "",
    "4c8.8+12+42,24,35+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "6d0.1+1+64+e", "", "", "", "", "", "", "",
    // 901-1000
    "", "", "", "", "", "", "", "", "", "", "", "", "2q6.2+11+19,39,12+e", "", "", "", "3m4.5+2+33,16,12+e",
    "5a4.1+7+53,32,1+e", "", "", "", "", "", "", "", "", "", "", "", "", "2a7.8+6+3,61,2+e", "", "", "", "", "", "", "",
    "3i9.4+7+29,42,49+e", "", "", "4d8.4+7+44,32,12+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "3k8.25+12+32,41,35+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "2d7.7+7+7,49,12+e",
    "", "8d3.2+2+74,39+e", "", "", "", "", "", "", "", "", "3d4.22+12+24,16,1+e", "", "", "", "", "", "", "", "", "",
    "", "", "",
    // 1001-1100
    "", "", "", "3s5.2+3+24,12+e", "2a8.36+6+3,24,12+e", "", "", "", "", "3i5.2+6+56,35,15+e", "", "", "", "", "", "",
    "", "", "", "", "3c5.5+6+23,42,2+e", "", "", "", "", "", "", "", "3r5.1+9+40,42,2+e", "", "", "", "", "", "", "",
    "", "", "", "2q8.3+11+19,48,15+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "3c4.18+7+23,20,9+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "4k8.18+13+51,4,13+e", "", "", "", "",
    "", "", "", "", "", "", "", "", "2j2.5+4+11,1,2+e", "", "", "", "", "", "", "", "", "", "", "", "",
    // 1101-1200
    "", "", "2e5.2+6+7,18,2+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "3m10.1+4+33,39,5+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "5h0.1+1+59+e", "", "", "", "3b10.4+7+22,59,24+e", "", "", "", "", "", "", "", "", "", "", "", "3q6.3+9+18,46,19+e",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "3p3.1+2+22,24+e", "", "", "", "", "", "",
    // 1201-1300
    "", "", "", "", "", "", "", "", "", "", "4a4.4+6+41,49+e", "", "0a5.42+4+32,20+n", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "3a5.15+7+21,42,2+e", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "3a8.31+7+21,24,35+e", "", "",
    "", "3a5.14+7+21,2+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "6f4.1+2+66,34,2+e", "3a5.1+6+21,54+e",
    // 1301-1400
    "", "", "", "", "", "", "", "4k6.17+7+51,55,2+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    // 1401-1500
    "", "5i7.7+9+60,43,1+e", "5i5.2+9+60,18,9+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "4k3.2+7+51,11,2+e", "2j5.4+12+11,51,2+e", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "",
    // 1501-1600
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "5b2.2+2+54,12+e", "", "", "", "", "", "", "0a5.32+4+32,4+n", "", "", "", "", "", "", "", "", "",
    // 1601-1700
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "7d7.2+7+70,43,1+e", "", "", "3a14.5+7+21,73,39+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    // 1701-1800
    "", "", "4k5.19+13+51,25,9+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    // 1801-1900
    "", "", "", "", "6e4.2+6+65,51+e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "3e7.2+6+25,77+e", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    // 1901-2000
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "",
    // 2001-2100
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "",
    // 2101-2141
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", ""};
// clang-format on

struct HData
{
  static HData fromString(uint64_t index, const char * in)
  {
    HData res{};

    res.hIndex = index;

    if (strcmp(in, "") == 0)
      return res;

    String buffer = in;
    auto splitBuf = split(buffer, '+', false);

    res.hString = splitBuf[0];
    res.image = static_cast<uint8_t>(std::stoul(splitBuf[1].data()));

    if (splitBuf[3] == "e")
      res.isFirst = true;
    else if (splitBuf[3] == "n")
      res.isFirst = false;
    else
      throw std::runtime_error{"error parsing index " + std::to_string(index)};

    splitBuf = split(splitBuf[2].data(), ',', false);
    for (const auto & buf: splitBuf)
      res.radicals.push_back(static_cast<Index>(std::stoul(buf.data())));
    return res;
  }

  bool isFirst{};
  uint8_t image{};
  Index hIndex{};
  String hString{};
  std::vector<Index> radicals{};
};

std::vector<HData> readHdata();

} // namespace imkanji

template<>
struct glz::meta<imkanji::HData>
{
  using T = imkanji::HData;
  static constexpr auto value = object(
      "hIndex", &T::hIndex, "hString", &T::hString, "image", &T::image, "radicals", &T::radicals, "isFirst", &T::isFirst);
};