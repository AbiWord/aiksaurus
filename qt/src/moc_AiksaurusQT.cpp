/****************************************************************************
** AiksaurusQT_impl::Dialog meta object code from reading C++ file 'AiksaurusQT.h'
**
** Created: Thu Jan 10 18:24:22 2002
**      by: The Qt MOC ($Id: moc_AiksaurusQT.cpp,v 1.1 2002/01/12 20:31:23 aiken Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "AiksaurusQT.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *AiksaurusQT_impl::Dialog::className() const
{
    return "AiksaurusQT_impl::Dialog";
}

QMetaObject *AiksaurusQT_impl::Dialog::metaObj = 0;

void AiksaurusQT_impl::Dialog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
	badSuperclassWarning("AiksaurusQT_impl::Dialog","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString AiksaurusQT_impl::Dialog::tr(const char* s)
{
    return qApp->translate( "AiksaurusQT_impl::Dialog", s, 0 );
}

QString AiksaurusQT_impl::Dialog::tr(const char* s, const char * c)
{
    return qApp->translate( "AiksaurusQT_impl::Dialog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* AiksaurusQT_impl::Dialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (AiksaurusQT_impl::Dialog::*m1_t0)(const char*);
    typedef void (QObject::*om1_t0)(const char*);
    typedef void (AiksaurusQT_impl::Dialog::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (AiksaurusQT_impl::Dialog::*m1_t2)(const char*);
    typedef void (QObject::*om1_t2)(const char*);
    typedef void (AiksaurusQT_impl::Dialog::*m1_t3)(int);
    typedef void (QObject::*om1_t3)(int);
    typedef void (AiksaurusQT_impl::Dialog::*m1_t4)(const char*);
    typedef void (QObject::*om1_t4)(const char*);
    m1_t0 v1_0 = &AiksaurusQT_impl::Dialog::_eventReplace;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &AiksaurusQT_impl::Dialog::_eventCancel;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &AiksaurusQT_impl::Dialog::_eventSelectWord;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &AiksaurusQT_impl::Dialog::done;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &AiksaurusQT_impl::Dialog::doSearch;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(5);
    slot_tbl[0].name = "_eventReplace(const char*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "_eventCancel()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "_eventSelectWord(const char*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    slot_tbl[3].name = "done(int)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Protected;
    slot_tbl[4].name = "doSearch(const char*)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    typedef void (AiksaurusQT_impl::Dialog::*m2_t0)(const char*);
    typedef void (QObject::*om2_t0)(const char*);
    typedef void (AiksaurusQT_impl::Dialog::*m2_t1)();
    typedef void (QObject::*om2_t1)();
    m2_t0 v2_0 = &AiksaurusQT_impl::Dialog::replace;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &AiksaurusQT_impl::Dialog::cancel;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "replace(const char*)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "cancel()";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"AiksaurusQT_impl::Dialog", "QDialog",
	slot_tbl, 5,
	signal_tbl, 2,
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

// SIGNAL replace
void AiksaurusQT_impl::Dialog::replace( const char* t0 )
{
    activate_signal( "replace(const char*)", t0 );
}

// SIGNAL cancel
void AiksaurusQT_impl::Dialog::cancel()
{
    activate_signal( "cancel()" );
}
