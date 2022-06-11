static mat4
InverseRotationAndTranslationMatrix(mat4 *Matrix)
{
    mat4 Result ={};
    Result.X= {Matrix->M[0][0],Matrix->M[1][0],Matrix->M[2][0], 0};
    Result.Y= {Matrix->M[0][1],Matrix->M[1][1],Matrix->M[2][1], 0};
    Result.Z= {Matrix->M[0][2],Matrix->M[1][2],Matrix->M[2][2], 0};
    Result.W.w = 1;
    Result.W.x = -(Matrix->W.x*Result.M[0][0] + 
            Matrix->W.y*Result.M[1][0]+Matrix->W.z*Result.M[2][0]);
    Result.W.y = -(Matrix->W.x*Result.M[0][1] +
            Matrix->W.y*Result.M[1][1]+Matrix->W.z*Result.M[2][1]);
    Result.W.z = -(Matrix->W.x*Result.M[0][2] +
            Matrix->W.y*Result.M[1][2]+Matrix->W.z*Result.M[2][2]);

    return Result;
}

static mat4
XRotationMatrix(f32 angle)
{
    mat4 Result = {};
    Result.M[3][3] = 1;
    Result.X.xyz = {1,0,0};
    Result.Y.yz = {cosf(angle), sinf(angle)};
    Result.Z.yz = {-sinf(angle), cosf(angle)};
    return Result;
}

static mat4
YRotationMatrix(f32 angle)
{
    mat4 Result = {};
    Result.M[3][3] = 1;
    Result.X.xyz = {cosf(angle),0,-sinf(angle)};
    Result.Y.y = 1;
    Result.Z.xyz = {sinf(angle), 0,cosf(angle)};
    return Result;
}

static mat4
ZRotationMatrix(f32 angle)
{
    mat4 Result = {};
    Result.M[3][3] = 1;
    Result.X.xy = {cosf(angle), sinf(angle)};
    Result.Y.xy = {-sinf(angle), cosf(angle)};
    Result.Z.z = 1;
    return Result;
}

static void
Renderer(game_screen_buffer *Buffer, game_memory *GameMemory)
{
    if(!GameMemory->IsInitialized)
    {
        //Memory layout: mesh struct1-mesh struct2-...-Vertices array 1-Vertices Index array 1
        //                    -Vertices array 2-Vertices Index array 2-... 
        GameMemory->GameScene.MeshCount =1;
        GameMemory->GameScene.Meshes = (mesh *)GameMemory->Memory;
        scene Scene = GameMemory->GameScene;
        mesh *Meshes = GameMemory->GameScene.Meshes;
#if 0
        Meshes[0].VertexCount =3;
        Meshes[0].Vertices = (vertex *)(Meshes +Scene.MeshCount);
        Meshes[0].TriCount = 1;
        Meshes[0].TriangleVerticesIndex = (v3i *)(Meshes[0].Vertices + Meshes[0].VertexCount);

        Meshes[0].Vertices[0].Coord={0,0,-5};
        Meshes[0].Vertices[0].Color=0xffffffff;
        Meshes[0].Vertices[1].Coord={5,0,-5};
        Meshes[0].Vertices[1].Color=0xffffffff;
        Meshes[0].Vertices[2].Coord ={0,5,-5};
        Meshes[0].Vertices[2].Color=0xffffffff;

        Meshes[0].TriangleVerticesIndex[0] ={0,1,2};

        Meshes[1].VertexCount =3;
        Meshes[1].Vertices = (vertex *)(Meshes[0].TriangleVerticesIndex +Meshes[0].TriCount);
        Meshes[1].TriCount = 1;
        Meshes[1].TriangleVerticesIndex = (v3i *)(Meshes[1].Vertices + Meshes[1].VertexCount);
        
        Meshes[1].Vertices[0].Coord={-1,-1,-10};
        Meshes[1].Vertices[0].Color=0x000000ff;
        Meshes[1].Vertices[1].Coord={-3,2,-10};
        Meshes[1].Vertices[1].Color=0x0000ff00;
        Meshes[1].Vertices[2].Coord ={-3,-3,-10};
        Meshes[1].Vertices[2].Color=0x00ff0000;

        Meshes[1].TriangleVerticesIndex[0] ={0,1,2};

#endif    
        
        Meshes[0].VertexCount =8;
        Meshes[0].Vertices = (vertex *)(Meshes +Scene.MeshCount);
        Meshes[0].TriCount =12; 
        Meshes[0].TriangleVerticesIndex = (v3i *)(Meshes[0].Vertices + Meshes[0].VertexCount);

        Meshes[0].Vertices[0].Coord={-2.5f,-2.5f,2.5f};
        Meshes[0].Vertices[0].Color=0xff00ffff;
        Meshes[0].Vertices[1].Coord={2.5f,-2.5f,2.5f};
        Meshes[0].Vertices[1].Color=0xffffff00;
        Meshes[0].Vertices[2].Coord ={2.5f,2.5f,2.5f};
        Meshes[0].Vertices[2].Color=0xff00ff0f;
        Meshes[0].Vertices[3].Coord={-2.5f,2.5f,2.5f};
        Meshes[0].Vertices[3].Color=0xfff000ff;
        Meshes[0].Vertices[4].Coord={-2.5f,-2.5f,-2.5f};
        Meshes[0].Vertices[4].Color=0xff0ff0ff;
        Meshes[0].Vertices[5].Coord ={2.5f,-2.5f,-2.5f};
        Meshes[0].Vertices[5].Color=0xff0f0ff0;
        Meshes[0].Vertices[6].Coord={2.5f,2.5f,-2.5f};
        Meshes[0].Vertices[6].Color=0xff0ff0f0;
        Meshes[0].Vertices[7].Coord ={-2.5f,2.5f,-2.5f};
        Meshes[0].Vertices[7].Color=0xffff0fff;

        Meshes[0].TriangleVerticesIndex[0] ={0,1,2};
        Meshes[0].TriangleVerticesIndex[1] ={0,2,3};
        Meshes[0].TriangleVerticesIndex[2] ={4,7,6};
        Meshes[0].TriangleVerticesIndex[3] ={4,6,5};
        Meshes[0].TriangleVerticesIndex[4] ={3,2,6};
        Meshes[0].TriangleVerticesIndex[5] ={3,6,7};
        Meshes[0].TriangleVerticesIndex[6] ={4,1,0};
        Meshes[0].TriangleVerticesIndex[7] ={4,5,1};
        Meshes[0].TriangleVerticesIndex[8] ={1,5,6};
        Meshes[0].TriangleVerticesIndex[9] ={1,6,2};
        Meshes[0].TriangleVerticesIndex[10] ={0,3,4};
        Meshes[0].TriangleVerticesIndex[11] ={3,7,4};
            

        GameMemory->IsInitialized = true;

    }
    
    mesh *Meshes = GameMemory->GameScene.Meshes;


    /*Keeping that around as a reminder for 16 bytes alignement
     *
    ZBufferAligned+= 15;
    ZBufferAligned= (ZBufferAligned) & (~15);
    */
    f32 *ZBuffer = Buffer->ZBuffer; 

    //clear buffers
    for(i32 *Pixel = Buffer->Memory, PixelIndex=0; PixelIndex < Buffer->Width *Buffer->Height; ++PixelIndex)
    {
        *Pixel++=0;
        ZBuffer[PixelIndex] = 0;
    }

    static f32 time=0;
    time += 1.0f/64.0f; 
        
    
    f32 ScreenHalfWidth = 1.0f;
    f32 ScreenHalfHeight = ScreenHalfWidth*((f32)Buffer->Height/(f32)Buffer->Width);

    f32 NearPlane = 1.0f;
    f32 FarPlane = 100.0f;

    mat4 ViewMatrix={};
    ViewMatrix.X={1,0,0,0};
    ViewMatrix.Y={0,1,0,0};
    ViewMatrix.Z={0,0,1,0};
    ViewMatrix.W={0,0,0,1};

    mat4 ProjectionMatrix={};
    ProjectionMatrix.X={NearPlane/ScreenHalfWidth,0,0,0};
    ProjectionMatrix.Y={0,NearPlane/ScreenHalfHeight,0,0};
    ProjectionMatrix.Z={0,0,1,-1};
    ProjectionMatrix.W={0,0,0,0};

    for(i32 MeshIndex =0; MeshIndex<GameMemory->GameScene.MeshCount; MeshIndex++)
    {
        mat4 YRotMat = YRotationMatrix(0.01f);
        mat4 XRotMat = XRotationMatrix(0.02f);
        
        mat4 RotMat = XRotMat *YRotMat;
        for(i32 VertIndex=0; VertIndex<Meshes[MeshIndex].VertexCount; ++VertIndex)
        {
            v4 Vert ={Meshes[MeshIndex].Vertices[VertIndex].Coord,1.0f}; 
            Vert = RotMat * Vert;
            //Vert = YRotMat * Vert;
           Meshes[MeshIndex].Vertices[VertIndex].Coord = Vert.xyz;
        }

        for(i32 TriangleIndex =0; TriangleIndex< Meshes[MeshIndex].TriCount; TriangleIndex++)
        {

            v3 pos = {0,0,-15.0f};
            //Triangle are wounded Counter-Clockwise
            v4 Triangle[3]={};
            Triangle[0].xyz 
                =Meshes[MeshIndex].Vertices[Meshes[MeshIndex].TriangleVerticesIndex[TriangleIndex].x].Coord 
                 +pos;
            Triangle[1].xyz 
                =Meshes[MeshIndex].Vertices[Meshes[MeshIndex].TriangleVerticesIndex[TriangleIndex].y].Coord 
                 +pos;
            Triangle[2].xyz 
                =Meshes[MeshIndex].Vertices[Meshes[MeshIndex].TriangleVerticesIndex[TriangleIndex].z].Coord 
                 +pos;
            
            //NOTE(Alex): More Debug Lighting 
            v3 TriangleNormal = NormalizeOrZero(Cross(Triangle[1].xyz - Triangle[0].xyz,
                                Triangle[2].xyz - Triangle[0].xyz));

            i32 Colors[3]={};
            Colors[0]
                =Meshes[MeshIndex].Vertices[Meshes[MeshIndex].TriangleVerticesIndex[TriangleIndex].x].Color; 
            Colors[1] 
                =Meshes[MeshIndex].Vertices[Meshes[MeshIndex].TriangleVerticesIndex[TriangleIndex].y].Color; 
            Colors[2] 
                =Meshes[MeshIndex].Vertices[Meshes[MeshIndex].TriangleVerticesIndex[TriangleIndex].z].Color; 


#if 0
            if(TriangleIndex == 1)
            {
                mat4 RotMat = ZRotationMatrix(time);

                Triangle[0] = RotMat*Triangle[0];
                Triangle[1] =RotMat*Triangle[1];
                Triangle[2] =RotMat*Triangle[2];
            }
            else
            {
                Triangle[0].z += -time;
                Triangle[1].z += -time;
                Triangle[2].z += -time;
            }
#endif 


            v4 ProjectedTriangle[3];

            ProjectedTriangle[0] = ProjectionMatrix *(ViewMatrix*Triangle[0]);
            ProjectedTriangle[1] = ProjectionMatrix *(ViewMatrix*Triangle[1]);
            ProjectedTriangle[2] = ProjectionMatrix *(ViewMatrix*Triangle[2]);

            //Note(Alex): Maybe a bit naive as far as fulstrum culling goes?
            if(ProjectedTriangle[0].w >= NearPlane && ProjectedTriangle[0].w <= FarPlane 
                    && ProjectedTriangle[1].w >= NearPlane && ProjectedTriangle[1].w <= FarPlane 
                    && ProjectedTriangle[2].w >= NearPlane && ProjectedTriangle[2].w <= FarPlane) 
            {
                v2 RasterizedTriangle[3];

                RasterizedTriangle[0] = ProjectedTriangle[0].xy*(1.0f/ProjectedTriangle[0].w);
                RasterizedTriangle[1] = ProjectedTriangle[1].xy*(1.0f/ProjectedTriangle[1].w);
                RasterizedTriangle[2] = ProjectedTriangle[2].xy*(1.0f/ProjectedTriangle[2].w);

                RasterizedTriangle[0].x +=1.0f;
                RasterizedTriangle[0].x *= (Buffer->Width/2.0f);
                RasterizedTriangle[0].y +=1.0f;
                RasterizedTriangle[0].y *= (Buffer->Height/2.0f);

                RasterizedTriangle[1].x +=1.0f;
                RasterizedTriangle[1].x *= (Buffer->Width/2.0f);
                RasterizedTriangle[1].y +=1.0f;
                RasterizedTriangle[1].y *= (Buffer->Height/2.0f);

                RasterizedTriangle[2].x +=1.0f;
                RasterizedTriangle[2].x *= (Buffer->Width/2.0f);
                RasterizedTriangle[2].y +=1.0f;
                RasterizedTriangle[2].y *= (Buffer->Height/2.0f);

                i32 MinX= (i32)Min(RasterizedTriangle[0].x,RasterizedTriangle[1].x,RasterizedTriangle[2].x);
                i32 MinY= (i32)Min(RasterizedTriangle[0].y,RasterizedTriangle[1].y,RasterizedTriangle[2].y);
                i32 MaxX= (i32)Max(RasterizedTriangle[0].x,RasterizedTriangle[1].x,RasterizedTriangle[2].x);
                i32 MaxY = (i32)Max(RasterizedTriangle[0].y,RasterizedTriangle[1].y,RasterizedTriangle[2].y);

                MinX = (i32) Max((f32) MinX, 0.0f); 
                MinY = (i32) Max((f32) MinY, 0.0f); 
                MaxX = (i32) Min((f32) MaxX, Buffer->Width-1.0f); 
                MaxY = (i32) Min((f32) MaxY, Buffer->Height-1.0f); 

                f32 Z0 = ProjectedTriangle[0].w;        
                f32 Z1 = ProjectedTriangle[1].w - Z0;
                f32 Z2 = ProjectedTriangle[2].w - Z0;

                for(i32 Y =MinY; Y<=MaxY; ++Y)
                {
                    for(i32 X=MinX; X<MaxX; ++X)
                    {
                        i32 w0 =(RasterizedTriangle[2].x-RasterizedTriangle[1].x)*(Y-RasterizedTriangle[1].y)
                            - (RasterizedTriangle[2].y-RasterizedTriangle[1].y)*(X-RasterizedTriangle[1].x);

                        i32 w1 =(RasterizedTriangle[0].x-RasterizedTriangle[2].x)*(Y-RasterizedTriangle[2].y)
                            - (RasterizedTriangle[0].y-RasterizedTriangle[2].y)*(X-RasterizedTriangle[2].x);

                        i32 w2 =(RasterizedTriangle[1].x-RasterizedTriangle[0].x)*(Y-RasterizedTriangle[0].y)
                            - (RasterizedTriangle[1].y-RasterizedTriangle[0].y)*(X-RasterizedTriangle[0].x);

                        if(w0>= 0 && w1 >= 0&& w2>=0)
                        {
                            f32 sum= (f32) (w0 +w1 +w2);
                            f32 l0 = (f32) w0/sum;
                            f32 l1 = (f32) w1/sum;
                            f32 l2 = (f32) w2/sum;

                            f32 ZP = Z0 + l1*Z1 + l2*Z2;
                            i32 PixelIndex = (Y* Buffer->Width) +X;
                            if(ZBuffer[PixelIndex] == 0 || ZBuffer[PixelIndex] > ZP)
                            {
                                ZBuffer[PixelIndex] = ZP;

                                /* Color interpolation code
                                 v4 Color0 =BGRAUnpack4x8(Colors[0]);
                                 Color0 *= 1/255.0f;
                                 v4 Color1 =BGRAUnpack4x8(Colors[1]);
                                 Color1 *= 1/255.0f;
                                 v4 Color2 =BGRAUnpack4x8(Colors[2]);
                                 Color2 *= 1/255.0f;

                                 v4 Color= l0*Color0 + l1*Color1 + l2*Color2;
                                 Color.rgb = {Clamp(0.0f, Color.r, 1.0f),
                                 Clamp(0.0f, Color.g, 1.0f),
                                 Clamp(0.0f, Color.b, 1.0f)};
                                 */
                                //NOTE(Alex): Debug Lighting Code 
                                //!!
                                v4 CubeColor = {1.0f, 0.5f, 0.31f,0.0f}; 
                                v4 LightColor = {1.0f,1.0f,1.0f,0.0f}; 
                                v3 LightPosition = {0,0,0};
                                v3 ViewPosition = LightPosition; 
                                f32 AmbientStrength =0.1f;
                                v4 Ambient= AmbientStrength * LightColor;

                                v3 PixPos = l0*Triangle[0].xyz + l1 * Triangle[1].xyz + l2*Triangle[2].xyz;
                                v3 LightDirection = NormalizeOrZero(LightPosition-PixPos);
                                f32 Diff=Max(Dot(TriangleNormal, LightDirection), 0.0f);
                                v4 Diffuse = Diff*LightColor;

#if 1
                                f32 SpecularStrenght = 0.5f;
                                v3 ViewDirection = NormalizeOrZero(ViewPosition - PixPos);
                                v3 ReflectDirection = Reflect(-LightDirection, TriangleNormal);
                                f32 Spec = Pow(Max(Dot(ViewDirection, ReflectDirection), 0.0f), 64.0f);
#endif
                                v4 Specular = SpecularStrenght * Spec * LightColor;

                                v4 Color = Hadamard(Diffuse + Ambient + Specular, CubeColor);
                                Color.rgb = {Clamp(0.0f, Color.r, 1.0f),
                                Clamp(0.0f, Color.g, 1.0f),
                                Clamp(0.0f, Color.b, 1.0f)};
                                Color *= 255.0f;
                                i32 PixelColor =BGRAPack4x8(Color); 
                                 
                                Buffer->Memory[PixelIndex] = PixelColor; 
                            }
                        }
                    }
                }
            }
        }
    }
};
