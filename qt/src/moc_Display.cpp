/****************************************************************************
** AiksaurusQT_impl::Display meta object code from reading C++ file 'Display.h'
**
** Created: Thu Jan 10 14:24:52 2002
**      by: The Qt MOC ($Id: moc_Display.cpp,v 1.1 2002/01/12 20:31:23 aiken Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "Display.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *AiksaurusQT_impl::Display::className() const
{
    return "AiksaurusQT_impl::Display";
}

QMetaObject *AiksaurusQT_impl::Display::metaObj = 0;

void AiksaurusQT_impl::Display::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QScrollView::className(), "QScrollView") != 0 )
	badSuperclassWarning("AiksaurusQT_impl::Display","QScrollView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString AiksaurusQT_impl::Display::tr(const char* s)
{
    return qApp->translate( "AiksaurusQT_impl::Display", s, 0 );
}

QString AiksaurusQT_impl::Display::tr(const char* s, const char * c)
{
    return qApp->translate( "AiksaurusQT_impl::Display", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* AiksaurusQT_impl::Display::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QScrollView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (AiksaurusQT_impl::Display::*m1_t0)(QListBoxItem*);
    typedef void (QObject::*om1_t0)(QListBoxItem*);
    typedef void (AiksaurusQT_impl::Display::*m1_t1)(QListBoxItem*);
    typedef void (QObject::*om1_t1)(QListBoxItem*);
    m1_t0 v1_0 = &AiksaurusQT_impl::Display::_itemSelected;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &AiksaurusQT_impl::Display::_itemChosen;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    QMetaData *slot_tbl = QMetaObject::new_metadata(2);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(2);
    slot_tbl[0].name = "_itemSelected(QListBoxItem*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "_itemChosen(QListBoxItem*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    typedef void (AiksaurusQT_impl::Display::*m2_t0)(const char*);
    typedef void (QObject::*om2_t0)(const char*);
    typedef void (AiksaurusQT_impl::Display::*m2_t1)(const char*);
    typedef void (QObject::*om2_t1)(const char*);
    m2_t0 v2_0 = &AiksaurusQT_impl::Display::selectWord;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &AiksaurusQT_impl::Display::newSearch;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "selectWord(const char*)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "newSearch(const char*)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"AiksaurusQT_impl::Display", "QScrollView",
	slot_tbl, 2,
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

// SIGNAL selectWord
void AiksaurusQT_impl::Display::selectWord( const char* t0 )
{
    activate_signal( "selectWord(const char*)", t0 );
}

// SIGNAL newSearch
void AiksaurusQT_impl::Display::newSearch( const char* t0 )
{
    activate_signal( "newSearch(const char*)", t0 );
}
