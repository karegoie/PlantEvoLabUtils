#include <windows.h>
#include <stdio.h>

void gotoxy(int x, int y) // send position
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void cursor(int n) // hide or show cursor
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = n;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int main(void)
{
    POINT pt; //mouse pointer
    int x[50000];
    int y[50000];
    int sub_x[50000], sub_y[50000]; // sub_x, sub_y
    int check_mouse = 2; // for mouse control
    int i = 0; // for macro recording
    int n = 0;  // for macro performing
    int sleep_time = 10;

    system("mode con: cols=31 lines=13"); // fix display
    cursor(0);

    gotoxy(0, 0);
        puts("-----------------------");
    puts("|                       |");
    puts("|      Mouse Macro      |");
    puts("|                       |");
    puts("|   F5: 매크로 녹화     |");
    puts("|   F6: 매크로 추가녹화 |");
    puts("|   F7: 매크로 정지     |");
    puts("|   F8: 매크로 시작     |");
    puts("|   F10: 종료           |");
    puts("|   F11: 도움말         |");
    puts("-------------------------");
    
    while(1)
    {
        if(GetKeyState(VK_F10)<0) // press F10 key
        {
            return 0; // exit program
        }

        else if(GetKeyState(VK_F11)<0) // press F11 key
        {
            gotoxy(0, 0);
            puts("-----------------------");
            puts("|                       |");
            puts("|      Mouse Macro      |");
            puts("|                       |");
            puts("|   F5: 매크로 녹화     |");
            puts("|   >>처음부터 녹화     |");
            puts("|   F6: 매크로 추가녹화 |");
            puts("|   >>계속 이어 녹화    |");
            puts("|                       |");
            puts("|   녹화 뒤 매크로 정지 |");
            puts("|   후 매크로 시작을    |");
            puts("|   누르면 매크로가     |");
            puts("|   진행됩니다.         |");
            puts("|                       |");
            puts("-------------------------");
            
            while(1)
            {
                if(GetKeyState(27)<0) // press ESC key
                {
                    gotoxy(0, 0);
                    puts("-----------------------");
                    puts("|                       |");
                    puts("|      Mouse Macro      |");
                    puts("|                       |");
                    puts("|   F5: 매크로 녹화     |");
                    puts("|   F6: 매크로 추가녹화 |");
                    puts("|   F7: 매크로 정지     |");
                    puts("|   F8: 매크로 시작     |");
                    puts("|   F10: 종료           |");
                    puts("|   F11: 도움말         |");
                    puts("-------------------------");
                    break;
                }
            }
        }

        else if(GetKeyState(VK_F5)<0) // Macro again
        {
            for(i=0;i<=50000;i++)
            {
                x[i] = -858993460; y[i] = -858993460; // initialize
                sub_x[i] = -858993460; sub_y[i] = -858993460; // initialize for trash value. NOT A GOOD WAY
            }
            i=0;

            while(1)
            {
                GetCursorPos(&pt); // mouse pointer
                x[i] = pt.x; // x value save
                y[i] = pt.y; // y value save
                sub_x[i] = 0, sub_y[i] = 0; // save sub_x, sub_y
                i++; // i is for frame
                Sleep(sleep_time); // 1 frame per 0.01s

                if(GetKeyState(VK_LBUTTON)<0 && check_mouse>=1) // press left button
                {
                    sub_x[i] = x[i-1];
                    sub_y[i] = y[i-1];
                    x[i] = 5000;
                    y[i] = 5000;

                    check_mouse = 0;
                    i++;
                }

                else if(GetKeyState(VK_LBUTTON)>=0 && check_mouse == 0) // unpress left button
                {
                    sub_x[i] = x[i-1];
                    sub_y[i] = y[i-1];
                    x[i] = 6000;
                    y[i] = 6000;

                    check_mouse = 1;
                    i++;
                }

                if(GetKeyState(VK_F7)<0)
                {
                    break;
                }
                if(GetKeyState(VK_F10)<0)
                {
                    return 0;
                }
            }
        }
        else if(GetKeyState(VK_F8)<0) // perform macro
        {
            n = 0; // first frame
            while(1)
            {
                if(x[n]==5000) // press left button is "5000"
                {
                    mouse_event(MOUSEEVENTF_LEFTDOWN, sub_x[n], sub_y[n], 0, 0);
                    Sleep(1);
                }
                else if(x[n]==6000)
                {
                    mouse_event(MOUSEEVENTF_LEFTUP, sub_x[n], sub_y[n], 0, 0); 
                    Sleep(1);
                }
                if(x[n]==-858993460)
                {
                    n = 0; // if macro reaches last region, it repeats
                }
                
                SetCursorPos(x[n], y[n]); // mouse movement for selected position
                Sleep(sleep_time);

                n++;

                if(GetKeyState(VK_F7)<0)
                {
                    break;
                }

                if(GetKeyState(VK_F10)<0)
                {
                    return 0;
                }
            }
        }

        Sleep(sleep_time);
    }

    return 0; 
}

