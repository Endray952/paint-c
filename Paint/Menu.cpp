#include "Menu.h"

 int create_win_ctrl(HWND hwnd, int ed_x, int ed_y, int ed_w, int ed_h, HWND* hwnd_ed, HWND* hwnd_sp, int* cur_val, int ed_key, int sp_key )
 {

     *hwnd_ed = CreateWindowA("edit", "",
         WS_CHILD | WS_VISIBLE | WS_TABSTOP
         | ES_LEFT | WS_BORDER,
         ed_x, ed_y, ed_w, ed_h,
         hwnd, (HMENU)(ed_key),
         (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);


     *hwnd_sp = CreateWindow(UPDOWN_CLASS, L"",
         WS_CHILD | WS_VISIBLE | WS_TABSTOP  
         | UDS_WRAP | UDS_ARROWKEYS | UDS_ALIGNRIGHT
         | UDS_SETBUDDYINT | WS_BORDER,
         ed_x, ed_y, ed_w, ed_h,
         hwnd, (HMENU)(sp_key),
         (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

     if (hwnd_sp != NULL) {

         SendMessage(*hwnd_sp, UDM_SETBUDDY, (LONG)*hwnd_ed, 0L);

         SendMessage(*hwnd_sp, UDM_SETRANGE, 0L, MAKELONG(ed_key == 1 ? 50:255, 0));

         SendMessage(*hwnd_sp, UDM_SETPOS, 0L, MAKELONG((int)(*cur_val), 0));
     }
     return 0;
 }
