/****************************************************************************
** AiksaurusQT_impl::MenuButton meta object code from reading C++ file 'MenuButton.h'
**
** Created: Fri Jan 4 22:46:42 2002
**      by: The Qt MOC ($Id: moc_MenuButton.cpp,v 1.1 2002/01/12 20:31:23 aiken Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "MenuButton.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *AiksaurusQT_impl::MenuButton::className() const
{
    return "AiksaurusQT_impl::MenuButton";
}

QMetaObject *AiksaurusQT_impl::MenuButton::metaObj = 0;

void AiksaurusQT_impl::MenuButton::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("AiksaurusQT_impl::MenuButton","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString AiksaurusQT_impl::MenuButton::tr(const char* s)
{
    return qApp->translate( "AiksaurusQT_impl::MenuButton", s, 0 );
}

QString AiksaurusQT_impl::MenuButton::tr(const char* s, const char * c)
{
    return qApp->translate( "AiksaurusQT_impl::MenuButton", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* AiksaurusQT_impl::MenuButton::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (AiksaurusQT_impl::MenuButton::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (AiksaurusQT_impl::MenuButton::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    m1_t0 v1_0 = &AiksaurusQT_impl::MenuButton::_downArrowClicked;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &AiksaurusQT_impl::MenuButton::_popupClosing;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    QMetaData *slot_tbl = QMetaObject::new_metadata(2);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(2);
    slot_tbl[0].name = "_downArrowClicked()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "_popupClosing()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"AiksaurusQT_impl::MenuButton", "QWidget",
	slot_tbl, 2,
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
