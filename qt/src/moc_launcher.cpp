/****************************************************************************
** Launcher meta object code from reading C++ file 'launcher.h'
**
** Created: Thu Jan 10 17:08:26 2002
**      by: The Qt MOC ($Id: moc_launcher.cpp,v 1.1 2002/01/12 20:31:23 aiken Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "launcher.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *Launcher::className() const
{
    return "Launcher";
}

QMetaObject *Launcher::metaObj = 0;

void Launcher::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("Launcher","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString Launcher::tr(const char* s)
{
    return qApp->translate( "Launcher", s, 0 );
}

QString Launcher::tr(const char* s, const char * c)
{
    return qApp->translate( "Launcher", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* Launcher::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (Launcher::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (Launcher::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (Launcher::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (Launcher::*m1_t3)(const char*);
    typedef void (QObject::*om1_t3)(const char*);
    m1_t0 v1_0 = &Launcher::_modalClicked;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &Launcher::_modelessClicked;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &Launcher::_dialogCancel;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &Launcher::_dialogReplace;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    QMetaData *slot_tbl = QMetaObject::new_metadata(4);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(4);
    slot_tbl[0].name = "_modalClicked()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "_modelessClicked()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "_dialogCancel()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    slot_tbl[3].name = "_dialogReplace(const char*)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"Launcher", "QWidget",
	slot_tbl, 4,
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
