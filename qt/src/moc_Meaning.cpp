/****************************************************************************
** AiksaurusQT_impl::Meaning meta object code from reading C++ file 'Meaning.h'
**
** Created: Thu Jan 10 14:24:57 2002
**      by: The Qt MOC ($Id: moc_Meaning.cpp,v 1.1 2002/01/12 20:31:23 aiken Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "Meaning.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *AiksaurusQT_impl::Meaning::className() const
{
    return "AiksaurusQT_impl::Meaning";
}

QMetaObject *AiksaurusQT_impl::Meaning::metaObj = 0;

void AiksaurusQT_impl::Meaning::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("AiksaurusQT_impl::Meaning","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString AiksaurusQT_impl::Meaning::tr(const char* s)
{
    return qApp->translate( "AiksaurusQT_impl::Meaning", s, 0 );
}

QString AiksaurusQT_impl::Meaning::tr(const char* s, const char * c)
{
    return qApp->translate( "AiksaurusQT_impl::Meaning", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* AiksaurusQT_impl::Meaning::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (AiksaurusQT_impl::Meaning::*m1_t0)(QListBoxItem*);
    typedef void (QObject::*om1_t0)(QListBoxItem*);
    typedef void (AiksaurusQT_impl::Meaning::*m1_t1)(QListBoxItem*);
    typedef void (QObject::*om1_t1)(QListBoxItem*);
    m1_t0 v1_0 = &AiksaurusQT_impl::Meaning::_itemSelected;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &AiksaurusQT_impl::Meaning::_itemChosen;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    QMetaData *slot_tbl = QMetaObject::new_metadata(2);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(2);
    slot_tbl[0].name = "_itemSelected(QListBoxItem*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "_itemChosen(QListBoxItem*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    typedef void (AiksaurusQT_impl::Meaning::*m2_t0)(QListBoxItem*);
    typedef void (QObject::*om2_t0)(QListBoxItem*);
    typedef void (AiksaurusQT_impl::Meaning::*m2_t1)(QListBoxItem*);
    typedef void (QObject::*om2_t1)(QListBoxItem*);
    m2_t0 v2_0 = &AiksaurusQT_impl::Meaning::itemSelected;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &AiksaurusQT_impl::Meaning::itemChosen;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "itemSelected(QListBoxItem*)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "itemChosen(QListBoxItem*)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"AiksaurusQT_impl::Meaning", "QWidget",
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

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL itemSelected
void AiksaurusQT_impl::Meaning::itemSelected( QListBoxItem* t0 )
{
    // No builtin function for signal parameter type QListBoxItem*
    QConnectionList *clist = receivers("itemSelected(QListBoxItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(QListBoxItem*);
    RT0 r0;
    RT1 r1;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	}
    }
}

// SIGNAL itemChosen
void AiksaurusQT_impl::Meaning::itemChosen( QListBoxItem* t0 )
{
    // No builtin function for signal parameter type QListBoxItem*
    QConnectionList *clist = receivers("itemChosen(QListBoxItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(QListBoxItem*);
    RT0 r0;
    RT1 r1;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	}
    }
}
