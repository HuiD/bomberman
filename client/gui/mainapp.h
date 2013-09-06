
#ifndef __MAIN_APP_H__
#define __MAIN_APP_H__

#include "decl.h"

class MainApp : public wxApp
{
public:
	bool OnInit();
	int32_t OnExit();
};

DECLARE_APP(MainApp)

#endif //__MAIN_APP_H__
