
// Ethernet_2Dlg.cpp: archivo de implementación
//

#include "pch.h"
#include "framework.h"
#include "Ethernet_2.h"
#include "Ethernet_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
private:
	//CDialog* m_sListenSocket;
	//CDialog* m_sConnectSocket;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de diálogo de CEthernet2Dlg



CEthernet2Dlg::CEthernet2Dlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_ETHERNET_2_DIALOG, pParent)
	, m_strName(_T(""))
	, m_strMessage(_T(""))
	, m_iPort(0)
	, m_iType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEthernet2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ESERVNAME, m_strName);
	DDX_Control(pDX, IDC_BCONNECT, m_ctlConnect);
	DDX_Text(pDX, IDC_EMSG, m_strMessage);
	DDX_Text(pDX, IDC_ESERVPORT, m_iPort);
	DDX_Control(pDX, IDC_LRECVD, m_ctlRecvd);
	DDX_Control(pDX, IDC_LSENT, m_ctlSent);
	DDX_Radio(pDX, IDC_RCLIENT, m_iType);
}

BEGIN_MESSAGE_MAP(CEthernet2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RCLIENT, &CEthernet2Dlg::OnRType)
	ON_BN_CLICKED(IDC_RSERVER, &CEthernet2Dlg::OnBnClickedRserver)
	ON_BN_CLICKED(IDC_BCONNECT, &CEthernet2Dlg::OnBnClickedBconnect)
	ON_BN_CLICKED(IDC_BSEND, &CEthernet2Dlg::OnBnClickedBsend)
END_MESSAGE_MAP()


// Controladores de mensajes de CEthernet2Dlg

BOOL CEthernet2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional
	m_iType = 0;
	m_strName = "loopback";
	m_iPort = 4000;

	UpdateData(FALSE);
	m_sConnectSocket.SetParent(this);
	m_sListenSocket.SetParent(this);

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CEthernet2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CEthernet2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CEthernet2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEthernet2Dlg::OnRType()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(TRUE);     
	// Which mode are we in?
	if (m_iType == 0)    
		// Set the appropriate text on the button8:
		m_ctlConnect.SetWindowText( __T("C&onectar") );
	else
		m_ctlConnect.SetWindowText( __T("&Escuchar") );
}


void CEthernet2Dlg::OnBnClickedRserver()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(TRUE);
	// Which mode are we in?7:
	if (m_iType == 0)
		// Set the appropriate text on the button8:
		m_ctlConnect.SetWindowText(__T("C&onectar"));
	else
		m_ctlConnect.SetWindowText(__T("&Escuchar"));
}


void CEthernet2Dlg::OnBnClickedBconnect()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	GetDlgItem(IDC_BCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ESERVNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ESERVPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RCLIENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RSERVER)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICTYPE)->EnableWindow(FALSE);

	if (m_iType == 0) {
		m_sConnectSocket.Create();
		m_sConnectSocket.Connect(m_strName, m_iPort);
	}
	else {
		m_sListenSocket.Create(m_iPort);
		m_sListenSocket.Listen();

	}
}


void CEthernet2Dlg::OnAccept()
{
	// TODO: Agregar aquí el código de implementación.
	m_sListenSocket.Accept(m_sConnectSocket);

	GetDlgItem(IDC_EMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATICMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BCLOSE)->EnableWindow(TRUE);
}


void CEthernet2Dlg::OnBnClickedBsend()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	int iLen;
	int iSent;
	UpdateData(TRUE);
	if (m_strMessage != "") {
		iLen = m_strMessage.GetLength();
		iSent = m_sConnectSocket.Send(LPCTSTR(m_strMessage), iLen);

	}
}
