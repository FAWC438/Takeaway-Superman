#include <graphics.h>      // 就是需要引用这个图形库
#include <ege.h>
int main()
{
	initgraph(1200, 800);   // 初始化为640*480大小的窗口
	setbkcolor(WHITE);
	circle(200, 200, 100); // 画圆，圆心(200, 200)，半径100
	getch();               // 等待用户按键，按任意键继续
	closegraph();          // 关闭图形界面
	return 0;
}