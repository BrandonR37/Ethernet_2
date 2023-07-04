
// Ethernet_2.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'pch.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// Símbolos principales


// CEthernet2App:
// Consulte Ethernet_2.cpp para obtener información sobre la implementación de esta clase
//

class CEthernet2App : public CWinApp
{
public:
	CEthernet2App();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
private:
	//CDialog* m_sListenSocket;
	//CDialog m_sConnectSocket;
	//CDialog* m_sConnectSocket;
};

extern CEthernet2App theApp;
