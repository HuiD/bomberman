#ifndef __MAIN_APP_H
#define __MAIN_APP_H

#include "decl.h"

class MainApp : public wxApp
{
public:
	bool OnInit();
	int32_t OnExit();
};

DECLARE_APP(MainApp)

#endif //__MAIN_APP_H

