/****************************************************************************
** MyCustomWidget meta object code from reading C++ file 'test.h'
**
** Created: Wed Jan 9 03:57:34 2002
**      by: The Qt MOC ($Id: moc_test.cpp,v 1.1 2002/01/12 20:31:23 aiken Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "test.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *MyCustomWidget::className() const
{
    return "MyCustomWidget";
}

QMetaObject *MyCustomWidget::metaObj = 0;

void MyCustomWidget::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("MyCustomWidget","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MyCustomWidget::tr(const char* s)
{
    return qApp->translate( "MyCustomWidget", s, 0 );
}

QString MyCustomWidget::tr(const char* s, const char * c)
{
    return qApp->translate( "MyCustomWidget", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MyCustomWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (MyCustomWidget::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    m1_t0 v1_0 = &MyCustomWidget::_buttonClicked;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "_buttonClicked()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"MyCustomWidget", "QWidget",
	slot_tbl, 1,
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
