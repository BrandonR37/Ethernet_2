
// Ethernet_2Dlg.h: archivo de encabezado
//

#pragma once


// Cuadro de diálogo de CEthernet2Dlg
class CEthernet2Dlg : public CDialogEx
{
// Construcción
public:
	CEthernet2Dlg(CWnd* pParent = nullptr);	// Constructor estándar

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ETHERNET_2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CButton m_ctlConnect;
	CString m_strMessage;
	int m_iPort;
	CListBox m_ctlRecvd;
	CListBox m_ctlSent;
	int m_iType;
	afx_msg void OnRType();
	afx_msg void OnBnClickedRserver();
	afx_msg void OnBnClickedBconnect();
	void OnAccept();
	afx_msg void OnBnClickedBsend();
private:
	//CDialog* m_ListenSocket;
	CDialog*m_sConnectSocket;
	CDialog*m_sListenSocket;
};
