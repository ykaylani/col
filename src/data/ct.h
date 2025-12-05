#ifndef COL_CT_H
#define COL_CT_H

struct alignas(64) float3x5a { float x[5], y[5], z[5]; };
struct alignas(64) float4x4a { float x[4], y[4], z[4], w[4]; };
struct alignas(64) float16a { float i[16]; };

struct alignas(16) float4x3a { float x[4], y[4], z[4]; };
struct alignas(16) float4a { float i[4]; };
struct alignas(16) float3a { float i[3]; };


#endif COL_CT_H