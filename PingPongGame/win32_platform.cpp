#include <Windows.h>

static bool run = true;

class Render {
public:
    void* memory;
    int width;
    int height;

    BITMAPINFO bitmap_info;
};

Render render;

#include "platform_common.cpp"
#include "rendering.cpp"
#include "game.cpp"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;
    switch (uMsg)
    {
    case WM_CLOSE:
    case WM_DESTROY: {
        run = false;
    } break;

    case WM_SIZE: {
        RECT rect;
        GetClientRect(hwnd, &rect);
        render.width = rect.right - rect.left;
        render.height = rect.bottom - rect.top;

        int size = render.width * render.height * sizeof(unsigned int);

        if (render.memory) VirtualFree(render.memory, 0, MEM_RELEASE);
        render.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        render.bitmap_info.bmiHeader.biSize = sizeof(render.bitmap_info.bmiHeader);
        render.bitmap_info.bmiHeader.biWidth = render.width;
        render.bitmap_info.bmiHeader.biHeight = render.height;
        render.bitmap_info.bmiHeader.biPlanes = 1;
        render.bitmap_info.bmiHeader.biBitCount = 32;
        render.bitmap_info.bmiHeader.biCompression = BI_RGB;

    } break;

    default: {
        result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    }
    return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpszClassName = L"Game Window Class";
    window_class.lpfnWndProc = window_callback;

    RegisterClass(&window_class);

    HWND window = CreateWindow(window_class.lpszClassName, L"Ping-Pong", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
    HDC hdc = GetDC(window);

    Input input = {};

    float deltaTime = 0.016666f;
    LARGE_INTEGER frameBeginTime;
    QueryPerformanceCounter(&frameBeginTime);

    float perfFreq;
    {
        LARGE_INTEGER perf;
        QueryPerformanceFrequency(&perf);
        perfFreq = (float)perf.QuadPart;
    }





    while (run) {
        //inputs
        MSG message;

        for (int i = 0; i < btn_count; i++) {
                input.btn[i].changed = false;  
        }

        while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
            switch (message.message) {
            case WM_KEYUP:
            case WM_KEYDOWN: {
                unsigned int vk_code = (unsigned int)message.wParam;
                bool is_down = ((message.lParam & (1 << 31)) == 0);

                switch (vk_code) {
                case VK_UP: {
                    input.btn[btn_up].changed = is_down != input.btn[btn_up].is_down;
                    input.btn[btn_up].is_down = is_down;
                }break;
                case VK_DOWN: {
                    input.btn[btn_down].changed = is_down != input.btn[btn_down].is_down;
                    input.btn[btn_down].is_down = is_down;
                    
                }break;
                case VK_LEFT: {
                    input.btn[btn_left].changed = is_down != input.btn[btn_left].is_down;
                    input.btn[btn_left].is_down = is_down;
                }break;
                case VK_RIGHT: {
                    input.btn[btn_right].changed = is_down != input.btn[btn_right].is_down;
                    input.btn[btn_right].is_down = is_down;
                }break;
                case VK_RETURN: {
                    input.btn[btn_enter].changed = is_down != input.btn[btn_enter].is_down;
                    input.btn[btn_enter].is_down = is_down;
                }break;
                case 'W': {
                    input.btn[btn_W].changed = is_down != input.btn[btn_W].is_down;
                    input.btn[btn_W].is_down = is_down;
                    
                }break;
                case 'S': {
                    input.btn[btn_S].changed = is_down != input.btn[btn_S].is_down;
                    input.btn[btn_S].is_down = is_down;
                }break;


                }

            } break;


            default: {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }

            }

        }

         
        //simulate
        simulateGame(&input, deltaTime);

        //render
        StretchDIBits(hdc, 0, 0, render.width, render.height, 0, 0, render.width, render.height, render.memory, &render.bitmap_info, DIB_RGB_COLORS, SRCCOPY);



        LARGE_INTEGER frameEndTime;
        QueryPerformanceCounter(&frameEndTime);
        deltaTime = (float)(frameEndTime.QuadPart - frameBeginTime.QuadPart) / perfFreq;
        frameBeginTime = frameEndTime;

    }
}

