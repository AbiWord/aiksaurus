/****************************************************************************
** KAikSaurus meta object code from reading C++ file 'Kaiksaur.h'
**
** Created: Thu Jul 19 19:30:26 2001
**      by: The Qt MOC ($Id: moc_Kaiksaur.cpp,v 1.1 2001/08/10 23:27:46 aiken Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "Kaiksaur.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *KAikSaurus::className() const
{
    return "KAikSaurus";
}

QMetaObject *KAikSaurus::metaObj = 0;

void KAikSaurus::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(KMainWindow::className(), "KMainWindow") != 0 )
	badSuperclassWarning("KAikSaurus","KMainWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString KAikSaurus::tr(const char* s)
{
    return qApp->translate( "KAikSaurus", s, 0 );
}

QString KAikSaurus::tr(const char* s, const char * c)
{
    return qApp->translate( "KAikSaurus", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* KAikSaurus::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) KMainWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (KAikSaurus::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (KAikSaurus::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (KAikSaurus::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (KAikSaurus::*m1_t3)(const QString&);
    typedef void (QObject::*om1_t3)(const QString&);
    typedef void (KAikSaurus::*m1_t4)(int);
    typedef void (QObject::*om1_t4)(int);
    typedef void (KAikSaurus::*m1_t5)(QListBoxItem*);
    typedef void (QObject::*om1_t5)(QListBoxItem*);
    typedef void (KAikSaurus::*m1_t6)(QListBoxItem*);
    typedef void (QObject::*om1_t6)(QListBoxItem*);
    m1_t0 v1_0 = &KAikSaurus::goBack;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &KAikSaurus::goForward;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &KAikSaurus::doSearch;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &KAikSaurus::changedFindString;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &KAikSaurus::selectedTab;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &KAikSaurus::listClicked;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &KAikSaurus::listDoubleClicked;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    QMetaData *slot_tbl = QMetaObject::new_metadata(7);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(7);
    slot_tbl[0].name = "goBack()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "goForward()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "doSearch()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    slot_tbl[3].name = "changedFindString(const QString&)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Private;
    slot_tbl[4].name = "selectedTab(int)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Private;
    slot_tbl[5].name = "listClicked(QListBoxItem*)";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Private;
    slot_tbl[6].name = "listDoubleClicked(QListBoxItem*)";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"KAikSaurus", "KMainWindow",
	slot_tbl, 7,
	0, 0,
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
