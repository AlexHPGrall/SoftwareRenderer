#include <windows.h>
#include <stdint.h>
#include <float.h>
#include <assert.h>

#include "./Renderer.h"
//#include "./Renderer_math.h"
#include "./Win32_Renderer.h"
#include "./Renderer.cpp"

static b32 GlobalRunning;
static win32_image_buffer GlobalBackBuffer;

static void
Win32DisplayBufferInWindow(HDC DeviceContext, i32 Width, i32 Height,
                    win32_image_buffer *Buffer)
{
    StretchDIBits(
            DeviceContext,
            0,
            0,
            Width,
            Height,
            0,
            0,
            Buffer->Width,
            Buffer->Height,
            (void *) Buffer->Memory,
            &Buffer->Info,
            DIB_RGB_COLORS,
            SRCCOPY);
}

static Dimension2d
Win32GetWindowDimensions(HWND Window)
{

    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    Dimension2d Result={};
    Result.Width = ClientRect.right - ClientRect.left;
    Result.Height= ClientRect.bottom- ClientRect.top;
    
    return Result;
}

LRESULT CALLBACK MainWindowCallBack(HWND   Window, UINT   Msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT Result ={};
    switch(Msg)
    {
        case(WM_DESTROY):
        case(WM_CLOSE):
        case(WM_QUIT):
        GlobalRunning = false;
        break;
        case(WM_PAINT):
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            Dimension2d Dimension = Win32GetWindowDimensions(Window);

            Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height,
                    &GlobalBackBuffer);
            EndPaint(Window, &Paint);
        }
    }
    Result = DefWindowProc(Window, Msg, wParam, lParam);
    return Result;
}
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    WNDCLASSEX WindowClass ={};
    WindowClass.cbSize = sizeof(WNDCLASSEX); 
    WindowClass.lpfnWndProc = MainWindowCallBack;
    WindowClass.style =CS_VREDRAW | CS_HREDRAW;
    WindowClass.hInstance = hInst;
    WindowClass.lpszClassName= "RendererWindowClassName";
     
    if(RegisterClassEx(&WindowClass))
    {
        HWND Window = CreateWindowEx(WS_EX_CLIENTEDGE,
                WindowClass.lpszClassName, 
                "Software Renderer",
                WS_VISIBLE |WS_OVERLAPPEDWINDOW, 
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                hInst,
                0); 
        if(Window)
        {

            GlobalBackBuffer ={};
            GlobalBackBuffer.Width = 1280;
            GlobalBackBuffer.Height = 720;
            GlobalBackBuffer.BytesPerPixel = 4;
            GlobalBackBuffer.Pitch = GlobalBackBuffer.Width *GlobalBackBuffer.BytesPerPixel;
            GlobalBackBuffer.Info.bmiHeader.biSize = sizeof(GlobalBackBuffer.Info.bmiHeader);
            GlobalBackBuffer.Info.bmiHeader.biWidth = GlobalBackBuffer.Width;
            GlobalBackBuffer.Info.bmiHeader.biHeight = GlobalBackBuffer.Height;
            GlobalBackBuffer.Info.bmiHeader.biPlanes = 1;
            GlobalBackBuffer.Info.bmiHeader.biBitCount =32;
            GlobalBackBuffer.Info.bmiHeader.biCompression = BI_RGB;
            i32 BitmapMemorySize = GlobalBackBuffer.Width*GlobalBackBuffer.Height
                                    *GlobalBackBuffer.BytesPerPixel;
            GlobalBackBuffer.Memory = 
                (i32 *)VirtualAlloc(0,BitmapMemorySize, 
                        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            i32 *Pixel = GlobalBackBuffer.Memory;
            for(i32 Y=0; Y<720; ++Y)
            {
                for(i32 X=0; X<1280;++X)
                {
                    v4 Red =BGRAUnpack4x8(0x00ff0000);
                    Red *= 1/255.0f;
                    v4 Green =BGRAUnpack4x8(0x0000ff00);
                    Green *= 1/255.0f;
                    v4 Blue = BGRAUnpack4x8(0x000000ff);
                    Blue *=1/255.0f;
                    v4 C1 = Lerp(Red, (f32)X/1279.0f, Green);
                    v4 C2 = Lerp(Red, (f32)Y/719.0f, Blue);
                    v4 Color= C1 + C2;
                    Color.rgb = {Clamp(0.0f, Color.r, 1.0f),
                                Clamp(0.0f, Color.g, 1.0f),
                                Clamp(0.0f, Color.b, 1.0f)};
                    Color *= 255.0f;
                    i32 PixelColor =BGRAPack4x8(Color); 
                    *Pixel++=PixelColor; 
                }
            }
            MSG msg = { };
                //NOTE(Alex): WM_PAINT bypasses the message queue 
                //so it needs to be handled in the callback function
            GlobalRunning = true;
            game_screen_buffer GameBuffer={};
            GameBuffer.Width = GlobalBackBuffer.Width;
            GameBuffer.Height= GlobalBackBuffer.Height;
            GameBuffer.Memory= GlobalBackBuffer.Memory;
            GameBuffer.Pitch= GlobalBackBuffer.Pitch;
            GameBuffer.BytesPerPixel= GlobalBackBuffer.BytesPerPixel;
            GameBuffer.ZBuffer = (f32 *) VirtualAlloc(0, BitmapMemorySize, 
                                        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            game_memory GameMemory ={};
            GameMemory.Memory = (u8 *)  VirtualAlloc(0,Megabytes(1), 
                                        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            while(GlobalRunning)
            {
                while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) )
                {

                    TranslateMessage(&msg);
                    DispatchMessage(&msg);

                }

                Renderer(&GameBuffer, &GameMemory);

                Dimension2d WindowDimensions=Win32GetWindowDimensions(Window);
                HDC DeviceContext = GetDC(Window);
                Win32DisplayBufferInWindow(DeviceContext, 
                            WindowDimensions.Width, WindowDimensions.Height, &GlobalBackBuffer);
                ReleaseDC(Window, DeviceContext);
            }    
        }
    }
    return 0;
}

