#ifndef RAYTRACING_SIMD_H
#define RAYTRACING_SIMD_H

#ifdef _WIN32
#include <windows.h>
#undef min
#undef max
#undef small
#define cpuid(info, x) __cpuidex(info, x, 0)
#else
#include <cpuid.h>
void cpuid(int info[4], int InfoType) {
    __cpuid_count(InfoType, 0, info[0], info[1], info[2], info[3]);
}
#endif

struct CPUInfo
{
//  Misc.
    bool HW_MMX = false;
    bool HW_x64 = false;
    bool HW_ABM = false;      // Advanced Bit Manipulation
    bool HW_RDRAND = false;
    bool HW_BMI1 = false;
    bool HW_BMI2 = false;
    bool HW_ADX = false;
    bool HW_PREFETCHWT1 = false;

//  SIMD: 128-bit
    bool HW_SSE = false;
    bool HW_SSE2 = false;
    bool HW_SSE3 = false;
    bool HW_SSSE3 = false;
    bool HW_SSE41 = false;
    bool HW_SSE42 = false;
    bool HW_SSE4a = false;
    bool HW_AES = false;
    bool HW_SHA = false;

//  SIMD: 256-bit
    bool HW_AVX = false;
    bool HW_XOP = false;
    bool HW_FMA3 = false;
    bool HW_FMA4 = false;
    bool HW_AVX2 = false;

//  SIMD: 512-bit
    bool HW_AVX512F = false;    //  AVX512 Foundation
    bool HW_AVX512CD = false;   //  AVX512 Conflict Detection
    bool HW_AVX512PF = false;   //  AVX512 Prefetch
    bool HW_AVX512ER = false;   //  AVX512 Exponential + Reciprocal
    bool HW_AVX512VL = false;   //  AVX512 Vector Length Extensions
    bool HW_AVX512BW = false;   //  AVX512 Byte + Word
    bool HW_AVX512DQ = false;   //  AVX512 Doubleword + Quadword
    bool HW_AVX512IFMA = false; //  AVX512 Integer 52-bit Fused Multiply-Add
    bool HW_AVX512VBMI = false; //  AVX512 Vector Byte Manipulation Instructions

    CPUInfo()
    {
        int info[4];
        cpuid(info, 0);
        int nIds = info[0];

        cpuid(info, 0x80000000);
        unsigned nExIds = info[0];

//  Detect Features
        if (nIds >= 0x00000001){
            cpuid(info,0x00000001);
            HW_MMX    = (info[3] & ((int)1 << 23)) != 0;
            HW_SSE    = (info[3] & ((int)1 << 25)) != 0;
            HW_SSE2   = (info[3] & ((int)1 << 26)) != 0;
            HW_SSE3   = (info[2] & ((int)1 <<  0)) != 0;

            HW_SSSE3  = (info[2] & ((int)1 <<  9)) != 0;
            HW_SSE41  = (info[2] & ((int)1 << 19)) != 0;
            HW_SSE42  = (info[2] & ((int)1 << 20)) != 0;
            HW_AES    = (info[2] & ((int)1 << 25)) != 0;

            HW_AVX    = (info[2] & ((int)1 << 28)) != 0;
            HW_FMA3   = (info[2] & ((int)1 << 12)) != 0;

            HW_RDRAND = (info[2] & ((int)1 << 30)) != 0;
        }
        if (nIds >= 0x00000007){
            cpuid(info,0x00000007);
            HW_AVX2   = (info[1] & ((int)1 <<  5)) != 0;

            HW_BMI1        = (info[1] & ((int)1 <<  3)) != 0;
            HW_BMI2        = (info[1] & ((int)1 <<  8)) != 0;
            HW_ADX         = (info[1] & ((int)1 << 19)) != 0;
            HW_SHA         = (info[1] & ((int)1 << 29)) != 0;
            HW_PREFETCHWT1 = (info[2] & ((int)1 <<  0)) != 0;

            HW_AVX512F     = (info[1] & ((int)1 << 16)) != 0;
            HW_AVX512CD    = (info[1] & ((int)1 << 28)) != 0;
            HW_AVX512PF    = (info[1] & ((int)1 << 26)) != 0;
            HW_AVX512ER    = (info[1] & ((int)1 << 27)) != 0;
            HW_AVX512VL    = (info[1] & ((int)1 << 31)) != 0;
            HW_AVX512BW    = (info[1] & ((int)1 << 30)) != 0;
            HW_AVX512DQ    = (info[1] & ((int)1 << 17)) != 0;
            HW_AVX512IFMA  = (info[1] & ((int)1 << 21)) != 0;
            HW_AVX512VBMI  = (info[2] & ((int)1 <<  1)) != 0;
        }
        if (nExIds >= 0x80000001){
            cpuid(info,0x80000001);
            HW_x64   = (info[3] & ((int)1 << 29)) != 0;
            HW_ABM   = (info[2] & ((int)1 <<  5)) != 0;
            HW_SSE4a = (info[2] & ((int)1 <<  6)) != 0;
            HW_FMA4  = (info[2] & ((int)1 << 16)) != 0;
            HW_XOP   = (info[2] & ((int)1 << 11)) != 0;
        }
    }

    bool is_mmx() { return HW_MMX; }
    bool is_x64() { return HW_x64; }
    bool is_abm() { return HW_ABM; }
    bool is_rdrand() { return HW_RDRAND; }
    bool is_bmi1() { return HW_BMI1; }
    bool is_bmi2() { return HW_BMI2; }
    bool is_adx() { return HW_ADX; }
    bool is_prefetchwt1() { return HW_PREFETCHWT1; }
    bool is_sse() { return HW_SSE; }
    bool is_sse2() { return HW_SSE2; }
    bool is_sse3() { return HW_SSE3; }
    bool is_ssse3() { return HW_SSSE3; }
    bool is_sse41() { return HW_SSE41; }
    bool is_sse42() { return HW_SSE42; }
    bool is_sse4a() { return HW_SSE4a; }
    bool is_aes() { return HW_AES; }
    bool is_sha() { return HW_SHA; }
    bool is_avx() { return HW_AVX; }
    bool is_xop() { return HW_XOP; }
    bool is_fma3() { return HW_FMA3; }
    bool is_fma4() { return HW_FMA4; }
    bool is_avx2() { return HW_AVX2; }
    bool is_avx512f() { return HW_AVX512F; }
    bool is_avx512cd() { return HW_AVX512CD; }
    bool is_avx512pf() { return HW_AVX512PF; }
    bool is_avx512er() { return HW_AVX512ER; }
    bool is_avx512vl() { return HW_AVX512VL; }
    bool is_avx512bw() { return HW_AVX512BW; }
    bool is_avx512dq() { return HW_AVX512DQ; }
    bool is_avx512ifma() { return HW_AVX512IFMA; }
    bool is_avx512vbmi() { return HW_AVX512VBMI; }

};


void checkHardwareProperties()
{
    auto info = CPUInfo();

    std::cout << "CPU INFO." << std::endl;
    std::cout << "mmx: " << info.is_mmx() << std::endl;
    std::cout << "x64: " << info.is_x64() << std::endl;
    std::cout << "abm: " << info.is_abm() << std::endl;
    std::cout << "rdrand: " << info.is_rdrand() << std::endl;
    std::cout << "bmi1: " << info.is_bmi1() << std::endl;
    std::cout << "bmi2: " << info.is_bmi2() << std::endl;
    std::cout << "adx: " << info.is_adx() << std::endl;
    std::cout << "prefetchwt1: " << info.is_prefetchwt1() << std::endl;
    std::cout << "sse: " << info.is_sse() << std::endl;
    std::cout << "sse2: " << info.is_sse2() << std::endl;
    std::cout << "sse3: " << info.is_sse3() << std::endl;
    std::cout << "ssse3: " << info.is_ssse3() << std::endl;
    std::cout << "sse41: " << info.is_sse41() << std::endl;
    std::cout << "sse42: " << info.is_sse42() << std::endl;
    std::cout << "sse4a: " << info.is_sse4a() << std::endl;
    std::cout << "aes: " << info.is_aes() << std::endl;
    std::cout << "sha: " << info.is_sha() << std::endl;
    std::cout << "avx: " << info.is_avx() << std::endl;
    std::cout << "xop: " << info.is_xop() << std::endl;
    std::cout << "fma3: " << info.is_fma3() << std::endl;
    std::cout << "fma4: " << info.is_fma4() << std::endl;
    std::cout << "avx2: " << info.is_avx2() << std::endl;
    std::cout << "avx512f: " << info.is_avx512f() << std::endl;
    std::cout << "avx512cd: " << info.is_avx512cd() << std::endl;
    std::cout << "avx512pf: " << info.is_avx512pf() << std::endl;
    std::cout << "avx512er: " << info.is_avx512er() << std::endl;
    std::cout << "avx512vl: " << info.is_avx512vl() << std::endl;
    std::cout << "avx512bw: " << info.is_avx512bw() << std::endl;
    std::cout << "avx512dq: " << info.is_avx512dq() << std::endl;
    std::cout << "avx512ifma: " << info.is_avx512ifma() << std::endl;
    std::cout << "avx512vbmi: " << info.is_avx512vbmi() << std::endl;
}


#endif //RAYTRACING_SIMD_H
