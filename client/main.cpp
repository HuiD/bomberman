#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
	g_window.init();
	g_window.show();
	while (true)
		g_window.poll();

	return 0;
}

