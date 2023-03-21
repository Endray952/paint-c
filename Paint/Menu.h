#pragma once
#include "Framework.h"
#include "CommCtrl.h"

#define ED_SIZE 1
#define SP_SIZE 2
#define ED_RED 3
#define SP_RED 4
#define ED_GREEN 5
#define SP_GREEN 6
#define ED_BLUE 7
#define SP_BLUE 8


 //int create_win_ctrl(HWND hwnd);
int create_win_ctrl(HWND hwnd, int ed_x, int ed_y, int ed_w, int ed_h, HWND* hwnd_ed, HWND* hwnd_sp, int* cur_val, int sp_key, int ed_key);