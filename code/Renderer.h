
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef float r32;
typedef double r64;
typedef float f32;
typedef double f64;
typedef bool b32;
#define F32MAX FLT_MAX
#define F32MIN -FLT_MAX
#define U32MAX ((u32)-1)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define Assert assert 

//macros operate on 32 bits by default so we need to specify the use of long long (64 bits)
#define Kilobytes(value) ((value)*1024LL)
#define Megabytes(value) (Kilobytes(value) * 1024LL)
#define Gigabytes(value) (Megabytes(value) * 1024LL)
#define Terabytes(value) (Gigabytes(value) * 1024LL)

#include "./Renderer_math.h"


struct Dimension2d
{
    i32 Width;
    i32 Height;
};


struct Camera
{
    v3 Position;
    v3 Direction;
    mat4 Matrix;
};

struct game_screen_buffer
{
    i32 Width;
    i32 Height;
    i32 *Memory;
    i32 Pitch;
    i32 BytesPerPixel;
    f32 *ZBuffer;

};

struct vertex
{
    v3 Coord;
    i32 Color;
};
struct mesh
{
   i32 VertexCount;
   vertex *Vertices;

   i32 TriCount;
   v3i *TriangleVerticesIndex;
};

struct scene
{
    i32 MeshCount;
    mesh *Meshes;
};

struct game_memory
{
    u8 *Memory;
    b32 IsInitialized;

    scene GameScene;
};

