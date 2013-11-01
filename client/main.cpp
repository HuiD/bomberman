#include "gui/mainwindow.h"
#include "../util/scheduler.h"

std::string g_progname;

int main(int argc, char *argv[])
{
	g_progname = argv[0];
	g_logger.setLogFile(g_progname + ".log");

	g_window.init();
	g_window.show();

	while (!g_window.isClosed())
		g_window.poll();

	g_sched.stop();
	return 0;
}

