#define PI32 3.14159265359f
#define TAU32 6.28318530717958647692f

#include <math.h>
#include <intrin.h>

union v2i
{
    struct
    {
        i32 x,y;
    };
    struct
    {
        i32 u,v;
    };
    i32 E[2];
};

union v2
{
    struct
    {
        f32 x,y;
    };
    struct
    {
        f32 u,v;
    };
    f32 E[2];
};


union v3i
{
    struct
    {
        i32 x,y,z;
    };
    struct
    {
        i32 u,v,__;
    };
    struct
    {
        i32 r,g,b;
    };
    struct
    {
        v2i xy;
        i32 Ignored0_;
    };
    struct
    {
        i32 Ignored1_;
        v2i yz;
    };
    struct
    {
        v2i uv;
        i32 Ignored2_;
    };
    struct
    {
        i32 Ignored3_;
        v2i v__;
    };
    i32 E[3];
};

union v3
{
    struct
    {
        f32 x,y,z;
    };
    struct
    {
        f32 u,v,__;
    };
    struct
    {
        f32 r,g,b;
    };
    struct
    {
        v2 xy;
        f32 Ignored0_;
    };
    struct
    {
        f32 Ignored1_;
        v2 yz;
    };
    struct
    {
        v2 uv;
        f32 Ignored2_;
    };
    struct
    {
        f32 Ignored3_;
        v2 v__;
    };
    f32 E[3];
};
            
union v4
{
    struct
    {
        union
        {
            v3 xyz;
            struct
            {
                f32 x,y,z;
            };
        };
        f32 w;
    };
    struct
    {
        union
        {
            v3 rgb;
            struct
            {
                f32 r,g,b;
            };
        };
        f32 a;
    };
    struct
    {
        v2 xy;
        f32 Ignored0_;
        f32 Ignored1_;
    };
    struct
    {
        f32 Ignored3_;
        v2 yz;
        f32 Ignored4_;
    };
    struct
    {
        f32 Ignored5_;
        f32 Ignored6_;
        v2 zw;
    };
    f32 E[4];
    __m128 Vec;
};


union mat4
{
    struct
    {
        v4 X;
        v4 Y;
        v4 Z;
        v4 W;
    };
    struct
    {
        __m128 A;
        __m128 B;
        __m128 C;
        __m128 D;
    };
    v4 Columns[4];
    f32 M[4][4];
};



inline v2
V2i(u32 X, u32 Y)
{
    v2 Result = {(f32)X,(f32)Y};
    return Result;
}

inline v2
V2i(i32 X, i32 Y)
{
    v2 Result = {(f32)X,(f32)Y};
    return Result;
}

inline v2
V2(f32 X, f32 Y)
{
    v2 Result = {X,Y};
    return Result;
}

inline v3
V3(f32 X, f32 Y, f32 Z)
{
    v3 Result = {X,Y,Z};
    return Result;
}
inline v3
V3(v2 XY, f32 Z)
{
    v3 Result;

    Result.x = XY.x;
    Result.y = XY.y;
    Result.z = Z;

    return Result;
}
inline v4
V4(f32 X, f32 Y, f32 Z, f32 W)
{
    v4 Result = {X,Y,Z,W};
    return Result;
}
inline v4
V4(v3 XYZ, f32 W)
{
    v4 Result;

    Result.xyz = XYZ;
    Result.w = W;

    return Result;
}
inline u32 
RoundReal32ToUInt32(f32 F)
{
    u32 Result =(u32)(F+0.5f);
    return Result;
}
inline f32
SquareRoot(f32 A)
{
return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(A)));
}

inline f32
Square(f32 A)
{

    f32 Result = A*A;

    return Result;
}
inline f32
Pow(f32 A, f32 B)
{
    f32 Result =(f32)pow(A, B);

    return Result;
}
inline f32
Sin(f32 t)
{
    return sinf(t);
}
inline f32
Sin01(f32 t)
{
    f32 Result = Sin(PI32*t);
    return Result;
}
inline f32
Triangle01(f32 t)
{
    f32 Result = 2.0f*t;
    if(Result > 1.0f)
        Result = 2.0f - Result;
    return Result;
}

inline f32
Lerp(f32 A, f32 t, f32 B)
{
    f32 Result = (1.0f - t)*A + t*B;
    return Result;
}

inline i32
Clamp(i32 Min, i32 Value, i32 Max)
{
    i32 Result;
    if(Value<Min)
        Result = Min;
    else if(Value > Max)
        Result = Max;
    else
        Result = Value;

    return Result;
}
inline f32
Clamp(f32 Min, f32 Value, f32 Max)
{
    f32 Result;
    if(Value<Min)
        Result = Min;
    else if(Value > Max)
        Result = Max;
    else
        Result = Value;

    return Result;
}
inline f32 
SafeRatioN(f32 Numerator, f32 Divisor, f32 N)
{
    f32 Result =N;
    if(Divisor != 0.0f)
        Result = Numerator/Divisor;
    return Result;
}

inline f32
SafeRatio0(f32 Numerator, f32 Divisor)
{
    f32 Result = SafeRatioN(Numerator, Divisor, 0.0f);
    return Result;
}

inline f32
SafeRatio1(f32 Numerator, f32 Divisor)
{
    f32 Result = SafeRatioN(Numerator, Divisor, 1.0f);
    return Result;
}
inline f32
Clamp01(f32 A)
{
    f32 Result = Clamp(0.0f, A, 1.0f);
    return Result;
}
inline v2
Perp(v2 A)
{
    v2 Result = {-A.y, A.x};
    return Result;
}


inline v2
operator+(v2 A, v2 B)
{
    v2 Result = {A.x+B.x, A.y+B.y};
    return Result;
}
inline v2
operator-(v2 A, v2 B)
{
    v2 Result = {A.x-B.x, A.y-B.y};
    return Result;
}
inline v3
operator+(v3 A, v3 B)
{
    v3 Result = {A.x+B.x, A.y+B.y,A.z+B.z};
    return Result;
}
inline v3
operator-(v3 A, v3 B)
{
    v3 Result = {A.x-B.x, A.y-B.y,A.z-B.z};
    return Result;
}


inline v3
operator*(f32 A, v3 B)
{
    v3 Result = {A*B.x, A*B.y,A*B.z};
    return Result;
}


inline v3
operator*(v3 A, f32 B)
{
    v3 Result = B*A;
    return Result;
}

inline v4
operator+(v4 A, v4 B)
{
    v4 Result = {A.x+B.x, A.y+B.y,A.z+B.z,A.w+B.w};
    return Result;
}
inline v4
operator-(v4 A, v4 B)
{
    v4 Result = {A.x-B.x, A.y-B.y,A.z-B.z,A.w-B.w};
    return Result;
}


inline v4
operator*(f32 A, v4 B)
{
    v4 Result = {A*B.x, A*B.y,A*B.z,A*B.w};
    return Result;
}


inline v4
operator*(v4 A, f32 B)
{
    v4 Result = B*A;
    return Result;
}

inline v2
operator*(f32 A, v2 B)
{
    v2 Result = {A*B.x, A*B.y};
    return Result;
}


inline v2
operator*(v2 A, f32 B)
{
    v2 Result = B*A;
    return Result;
}
inline v2 &
operator+=(v2 &A, v2 B)
{
    A=A+B;
    return A;
}
inline v3 & 
operator+=(v3 &A, v3 B)
{
    A=A+B;
    return A;
}
inline v4 & 
operator+=(v4 &A, v4 B)
{
    A=A+B;
    return A;
}

inline v2 &
operator*=(v2 &A, f32 B)
{
    A=A*B;
    return A;
}
inline v3 & 
operator*=(v3 &A, f32 B)
{
    A=A*B;
    return A;
}

inline v4 & 
operator*=(v4 &A, f32 B)
{
    A=A*B;
    return A;
}
inline v2 
operator-(v2 &A)
{
    A= -1.0f *A;
    return A;
}

inline v3  
operator-(v3 A)
{
    return -1.0f* A;
}
inline v2
Lerp(v2 A, f32 t, v2 B)
{
    v2 Result = (1.0f - t)*A + t*B;
    return Result;
}
inline v3
Lerp(v3 A, f32 t, v3 B)
{
    v3 Result = (1.0f - t)*A + t*B;
    return Result;
}
inline v4
Lerp(v4 A, f32 t, v4 B)
{
    v4 Result = (1.0f - t)*A + t*B;
    return Result;
}

inline f32
Dot(v2 A, v2 B)
{
    f32 Result = A.x * B.x + A.y*B.y;
    return Result;
}
inline f32
Dot(v3 A, v3 B)
{
    f32 Result = A.x * B.x + A.y*B.y+ A.z*B.z;
    return Result;
}
inline f32
Dot(v4 A, v4 B)
{
    f32 Result = A.x * B.x + A.y*B.y+ A.z*B.z+ A.w*B.w;
    return Result;
}
inline v3
Cross(v3 A, v3 B)
{
    v3 Result;
    Result.x = A.y*B.z-A.z*B.y;
    Result.y = A.z*B.x - A.x*B.z;
    Result.z = A.x*B.y - A.y*B.x;

    return Result;
}

inline f32
LengthSq(v2 A)
{
    f32 Result = Dot(A,A);
    return Result;
}
inline f32
Length(v2 A)
{
    f32 Result = SquareRoot(LengthSq(A));
    return Result;
}
inline v2
Normalize(v2 A)
{
    v2 Result = (1.0f / Length(A))*A;
    return Result;
}
inline v2
NormalizeOrZero(v2 A)
{
    v2 Result ={};
    
    f32 LenSq = LengthSq(A);
    if(LenSq > Square(0.0001f))
    {
        Result = (1.0f/SquareRoot(LenSq))*A;
    }
    return Result;
}
inline f32
LengthSq(v3 A)
{
    f32 Result = Dot(A,A);
    return Result;
}
inline f32
Length(v3 A)
{
    f32 Result = SquareRoot(LengthSq(A));
    return Result;
}
inline v3
Normalize(v3 A)
{
    v3 Result = (1.0f / Length(A))*A;
    return Result;
}
inline v3
NormalizeOrZero(v3 A)
{
    v3 Result ={};
    
    f32 LenSq = LengthSq(A);
    if(LenSq > Square(0.0001f))
    {
        Result = (1.0f/SquareRoot(LenSq))*A;
    }
    return Result;
}

inline v2
Hadamard(v2 A, v2 B)
{
    v2 Result = {A.x *B.x, A.y*B.y};

    return Result;
}
inline v3
Hadamard(v3 A, v3 B)
{
    v3 Result = {A.x *B.x, A.y*B.y, A.z*B.z};

    return Result;
}
inline v4
Hadamard(v4 A, v4 B)
{
    v4 Result = {A.x *B.x, A.y*B.y, A.z*B.z, A.w*B.w};

    return Result;
}

inline v4
BGRAUnpack4x8(u32 Packed)
{
    v4 Result = {(f32)((Packed>>16) & 0xFF),
                 (f32)((Packed>>8) & 0xFF),
                 (f32)((Packed>>0) & 0xFF),
                 (f32)((Packed>>24) & 0xFF)};
            return Result;
}
inline v4
RGBAUnpack4x8(u32 Packed)
{
    v4 Result = {(f32)((Packed>>0) & 0xFF),
                 (f32)((Packed>>8) & 0xFF),
                 (f32)((Packed>>16) & 0xFF),
                 (f32)((Packed>>24) & 0xFF)};
            return Result;
}
inline u32
BGRAPack4x8(v4 Unpacked)
{
    u32 Result = ((RoundReal32ToUInt32(Unpacked.a) << 24) |
                  (RoundReal32ToUInt32(Unpacked.r) << 16) |
                  (RoundReal32ToUInt32(Unpacked.g) << 8)  |
                  (RoundReal32ToUInt32(Unpacked.b) << 0));

            return Result;
}
inline u32
RGBAPack4x8(v4 Unpacked)
{
    u32 Result = ((RoundReal32ToUInt32(Unpacked.a) << 24) |
                  (RoundReal32ToUInt32(Unpacked.b) << 16) |
                  (RoundReal32ToUInt32(Unpacked.g) << 8)  |
                  (RoundReal32ToUInt32(Unpacked.r) << 0));

            return Result;
}
inline v4
LinearTosRGB(v4 C)
{
    v4 Result;
    Result.r = SquareRoot(C.r);
    Result.g = SquareRoot(C.g);
    Result.b = SquareRoot(C.b);
    Result.a = C.a;
}
inline v4
sRGBLinearize(v4 C)
{
    v4 Result;
    Result.r=Square(C.r);
    Result.g=Square(C.g);
    Result.b=Square(C.b);
    Result.a=C.a;

    return Result;
}


inline v4
sRGBLinearize(f32 R, f32 G, f32 B, f32 A)
{
    v4 Result = {R,G,B,A};
    Result = sRGBLinearize(Result);
    return Result;
}

inline v4
SRGB255ToLinear1(v4 C)
{
    v4 Result;
    f32 inv255 = 1.0f/255.0f;

    Result.r = Square(inv255*C.r);
    Result.g = Square(inv255*C.g);
    Result.b = Square(inv255*C.b);
    Result.a=inv255*C.a;
    return Result;
}

inline v4
Linear1ToSRGB255(v4 C)
{
    v4 Result;
    f32 one255 = 255.0f;

    Result.r = one255*SquareRoot(C.r);
    Result.g = one255*SquareRoot(C.g);
    Result.b = one255*SquareRoot(C.b);
    Result.a=one255*C.a;
    return Result;
}
inline v4
operator*(mat4 M, v4 v)
{
    v4 Result ={};
    __m128 vx = _mm_set_ps1(v.x);
    __m128 vy = _mm_set_ps1(v.y);
    __m128 vz = _mm_set_ps1(v.z);
    __m128 vw = _mm_set_ps1(v.w);
    Result.Vec = _mm_add_ps(_mm_mul_ps(vx, M.A),
                           _mm_add_ps(_mm_mul_ps(vy, M.B),
                           _mm_add_ps(_mm_mul_ps(vz, M.C), _mm_mul_ps(vw, M.D))));

    return Result;

}
inline mat4
operator*(mat4 A, mat4 B)
{
    mat4 Result;
    Result.X = A*B.X;
    Result.Y = A*B.Y;
    Result.Z = A*B.Z;
    Result.W = A*B.W;
    return Result;
}

inline f32 
Max(f32 A, f32 B)
{
    return (A<B)?B:A;
}

inline f32 
Max(f32 A, f32 B, f32 C)
{
    return Max(A,Max(B,C));
}

inline f32 
Min(f32 A, f32 B)
{
    return (A<B)?A:B;
}

inline f32 
Min(f32 A, f32 B, f32 C)
{
    return Min(A, Min(B,C));
}

inline v3
Reflect(v3 Direction, v3 Normal)
{
    v3 Result = Direction - 2.0f*Dot(Direction, Normal)*Normal;
    return Result;
}

