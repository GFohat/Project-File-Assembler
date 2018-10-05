#pragma once

#include <atldbcli.h>
#include "ConstDatasourceProps.h" //namespace CONS_DS_PROPS

class CDataSourceInfoHolder
{
public:
	CDataSourceInfoHolder(void);
	virtual ~CDataSourceInfoHolder(void);

public:
	CString GetPropertyValue(const int iPropOrdinal) const;
	CString GetPropertyName(const int iPropOrdinal) const;

	CString GetCurrentCatalog(const CDataSource & ds) const;
	CString GetCurrentServer(const CDataSource & ds) const;

protected:
	HRESULT SetPropertyValues(const CDataSource & ds);
	void ClearPropertyValues(const CComVariant & varClear);
	void ClearPropertyValues(const HRESULT hr);
	CString GetStringFromVariant(const CComVariant & vt) const;
	CString GetStringFromError(const CComVariant & vt) const;
	bool IsMSJetDataSource(void) const { return m_bJetDataSource; };

private:
	CComVariant m_varProps[ CONS_DS_PROPS::PROPERTY_ORDINALS::iPO__LAST ];
	bool m_bJetDataSource;

	void Translate_DBPROP_CATALOGLOCATION		(CComVariant & var);
	void Translate_DBPROP_DSOTHREADMODEL		(CComVariant & var);
	void Translate_DBPROP_GROUPBY				(CComVariant & var);
	void Translate_DBPROP_COLUMNDEFINITION		(CComVariant & var);
	void Translate_DBPROP_CONCATNULLBEHAVIOR	(CComVariant & var);
};
