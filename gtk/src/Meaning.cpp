#include "Meaning.h"
#include "Display.h"
#include <cctype>  
using namespace std;

namespace AiksaurusGTK_impl 
{
    
    static void ucwords(string& str) throw()
    {
        bool ws = true;
        for(int i = 0;i < static_cast<int>(str.size());++i)
        {
            if (isspace(str[i]))
                ws = true;
                
            else if (ws)
            {
                str[i] = toupper(str[i]);
                ws = false;
            }
        }
    }

    Meaning::Meaning(const string& title, vector<string>& words, Display& display) 
    throw(bad_alloc)
        : d_title(title), d_words(words), d_display(display), d_lists(4)
    {
        d_masterLayout = gtk_event_box_new();
        
        ucwords(d_title);
        
        gtk_widget_set_name(d_masterLayout, "ybg");

        d_mainLayout = gtk_vbox_new(false, 0);
        gtk_container_add( GTK_CONTAINER(d_masterLayout), d_mainLayout );

        d_labelLayout = gtk_hbox_new(false, 2);
        gtk_box_pack_start( GTK_BOX(d_mainLayout), d_labelLayout, 0, 0, 2);

        d_label = gtk_label_new(d_title.c_str());
        gtk_widget_set_name(d_label, "mst");
        gtk_label_set_justify( GTK_LABEL(d_label), GTK_JUSTIFY_LEFT );
        gtk_box_pack_start( GTK_BOX(d_labelLayout), d_label, 0, 0, 4 );

        d_subLayout = gtk_hbox_new(false, 0);
        gtk_box_pack_start( GTK_BOX(d_mainLayout), d_subLayout, 0, 0, 0 );

        int i;
        for(i = 0;i < 4;++i)
        {
            d_lists[i] = gtk_clist_new(1);
            gtk_clist_set_shadow_type( GTK_CLIST(d_lists[i]), GTK_SHADOW_NONE );
            gtk_container_set_border_width( GTK_CONTAINER(d_lists[i]), 0 );
            gtk_widget_set_name(d_lists[i], "wbg");  // <-- this one!!
            gtk_box_pack_start( GTK_BOX(d_subLayout), d_lists[i], 1, 1, 0 );
            g_signal_connect(
                G_OBJECT(d_lists[i]), "select-row", 
                G_CALLBACK(_wordclick), this
            );
        }

        int n = d_words.size();
        int q = n / 4;
        int r = n % 4;
        int stop1, stop2, stop3;
        
        switch(r)
        {
            case 0:
                stop1 = q;
                stop2 = stop1 + q;
                stop3 = stop2 + q;
                break;    
                
            case 1:
                stop1 = q + 1;
                stop2 = stop1 + q;
                stop3 = stop2 + q;
                break;
                
            case 2:
                stop1 = q + 1;
                stop2 = stop1 + (q + 1);
                stop3 = stop2 + q;
                break;
                
            default: // r = 3
                stop1 = q + 1;
                stop2 = stop1 + (q + 1);
                stop3 = stop2 + (q + 1);
                break;
        }

        for(i = 0;i < stop1;++i)
        {
            const char* str = d_words[i].c_str();
            gtk_clist_append(
                GTK_CLIST(d_lists[0]), const_cast<char**>(&str)
            );
        }

        for(; i < stop2;++i)
        {
            const char* str = d_words[i].c_str();
            gtk_clist_append(
                GTK_CLIST(d_lists[1]), const_cast<char**>(&str)
            );
        }

        for(; i < stop3;++i)
        {
            const char* str = d_words[i].c_str();
            gtk_clist_append(
                GTK_CLIST(d_lists[2]), const_cast<char**>(&str)
            );
        }

        for(; i < static_cast<int>(d_words.size());++i)
        {
            const char* str = d_words[i].c_str();
            gtk_clist_append(
                GTK_CLIST(d_lists[3]), const_cast<char**>(&str)
            );
        }
        
    }

    Meaning::~Meaning() throw()
    {
    
    }

    GtkWidget* Meaning::getLayout() throw()
    {
        return d_masterLayout;
    }


    gint Meaning::_wordclick
    (GtkCList* list, gint row, gint col, GdkEventButton *e, gpointer data)
    throw(std::bad_alloc)
    {
        Meaning *m = static_cast<Meaning*>(data);
        m->d_display._handleSelection(GTK_WIDGET(list));

        char* text;    
        gtk_clist_get_text(list, row, 0, &text);
        m->d_display._handleClick((e->type == GDK_2BUTTON_PRESS), text);

        return 0;
    }


    void Meaning::unselectListsExcept(GtkWidget* list) throw()
    {
        for(int i = 0;i < static_cast<int>(d_lists.size());++i)
        {
            if (d_lists[i] != list)
                gtk_clist_unselect_all(GTK_CLIST(d_lists[i]));
        }
    }

}

