// AdoAccess1.h: interface for the AdoAccess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOACCESS1_H__93FA35AF_0FED_4AE8_97C4_6DE62E923D4F__INCLUDED_)
#define AFX_ADOACCESS1_H__93FA35AF_0FED_4AE8_97C4_6DE62E923D4F__INCLUDED_

#include "stdafx.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AdoAccess  
{
public:
		 _ConnectionPtr   m_pConnection; // Êý¾Ý¿â
//	 _RecordsetPtr    m_pRecordset; // ÃüÁî
	 _CommandPtr      m_pCommand; // ¼ÇÂ¼
      void OnInitADOConn();
      void ExitConnect();
	  void Openace();
	  void Chaxun();
	AdoAccess();
	virtual ~AdoAccess();

};

#endif // !defined(AFX_ADOACCESS1_H__93FA35AF_0FED_4AE8_97C4_6DE62E923D4F__INCLUDED_)
