#include "tool.h"

mutex tool::mtx;

void tool::ShowConsoleCursor(bool Flag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursoInfo;
	GetConsoleCursorInfo(out, &cursoInfo);
	cursoInfo.bVisible = Flag;
	SetConsoleCursorInfo(out, &cursoInfo);
}

void tool::GotoXY(int x, int y) {
	COORD crd = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
}


//Draw character or array of character ('K', 'o', 'T') 
//Vẽ đường đi cho 1 một đối tượng
void tool::Draw(char* str, int i, point p[], point& _p) {

	// p[] contain the thuoc tinh tai vi tri ve
	mtx.lock(); //đảm bảo chỉ 1 luồng vẽ tại 1 thời điểm
	
	_p = p[i]; //Lưu lại vị trí hiện tại vào biến _p(ví dụ : enemy đang ở đây)
	tool::GotoXY(_p.getX(), _p.getY()); //Move the cursor cái con trỏ của console chứ không phải trỏ chuột
	cout << str; //In chuỗi ký tự ra màn hình tại vị trí đã di chuyển
	mtx.unlock();// Mở khóa để thread khác có thể vẽ
}

//ctool::Draw((char*)"K", i, p, _p);
//"K" là ký tự enemy
//i là bước thứ i
//p[] là đường đi đã được tính sẵn gồm nhiều cpoint
//_p là vị trí hiện tại sẽ được cập nhật