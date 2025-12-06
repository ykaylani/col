#ifndef COL_CT_H
#define COL_CT_H

struct alignas(16) float4x4a { float x[4], y[4], z[4], w[4]; }; //SSE
struct alignas(32) float8x4a { float x[8], y[8], z[8], w[8]; }; //AVX(2)

struct alignas(16) float4x3a { float x[4], y[4], z[4]; };
struct alignas(32) float8x3a { float x[8], y[8], z[8]; };

struct alignas(16) float16a { float i[16]; };
struct alignas(16) float4a { float i[4]; };
struct alignas(16) float3a { float i[3]; };
struct float3 {float x, y, z; };


#endif COL_CT_H