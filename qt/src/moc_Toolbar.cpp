/****************************************************************************
** AiksaurusQT_impl::Toolbar meta object code from reading C++ file 'Toolbar.h'
**
** Created: Thu Jan 10 14:24:47 2002
**      by: The Qt MOC ($Id: moc_Toolbar.cpp,v 1.1 2002/01/12 20:31:23 aiken Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "Toolbar.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *AiksaurusQT_impl::Toolbar::className() const
{
    return "AiksaurusQT_impl::Toolbar";
}

QMetaObject *AiksaurusQT_impl::Toolbar::metaObj = 0;

void AiksaurusQT_impl::Toolbar::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("AiksaurusQT_impl::Toolbar","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString AiksaurusQT_impl::Toolbar::tr(const char* s)
{
    return qApp->translate( "AiksaurusQT_impl::Toolbar", s, 0 );
}

QString AiksaurusQT_impl::Toolbar::tr(const char* s, const char * c)
{
    return qApp->translate( "AiksaurusQT_impl::Toolbar", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* AiksaurusQT_impl::Toolbar::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (AiksaurusQT_impl::Toolbar::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (AiksaurusQT_impl::Toolbar::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (AiksaurusQT_impl::Toolbar::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (AiksaurusQT_impl::Toolbar::*m1_t3)(int);
    typedef void (QObject::*om1_t3)(int);
    typedef void (AiksaurusQT_impl::Toolbar::*m1_t4)(int);
    typedef void (QObject::*om1_t4)(int);
    m1_t0 v1_0 = &AiksaurusQT_impl::Toolbar::_searchClicked;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &AiksaurusQT_impl::Toolbar::_backClicked;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &AiksaurusQT_impl::Toolbar::_forwardClicked;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &AiksaurusQT_impl::Toolbar::_backMenu;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &AiksaurusQT_impl::Toolbar::_forwardMenu;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(5);
    slot_tbl[0].name = "_searchClicked()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "_backClicked()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "_forwardClicked()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    slot_tbl[3].name = "_backMenu(int)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Private;
    slot_tbl[4].name = "_forwardMenu(int)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Private;
    typedef void (AiksaurusQT_impl::Toolbar::*m2_t0)(const char*);
    typedef void (QObject::*om2_t0)(const char*);
    m2_t0 v2_0 = &AiksaurusQT_impl::Toolbar::newSearch;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "newSearch(const char*)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    metaObj = QMetaObject::new_metaobject(
	"AiksaurusQT_impl::Toolbar", "QWidget",
	slot_tbl, 5,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}

// SIGNAL newSearch
void AiksaurusQT_impl::Toolbar::newSearch( const char* t0 )
{
    activate_signal( "newSearch(const char*)", t0 );
}
