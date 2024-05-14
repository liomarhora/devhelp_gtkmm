#ifndef DEVHELP_PLUGIN_COMMON_H
#define DEVHELP_PLUGIN_COMMON_H

#include <gtkmm.h>
#include <string>
#include <list>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

#include <webkit2/webkit2.h>
#include <devhelp/dh-profile.h>
#include <devhelp/dh-book-tree.h>
#include <devhelp/dh-link.h>
#include <devhelp/dh-web-view.h>
#include <devhelp/dh-search-bar.h>
#include <devhelp/dh-sidebar.h>
#include <devhelp/devhelp.h>


using namespace Gtk;

class DevhelpPlugin : public Window
{
	
public:
	DevhelpPlugin();
	~DevhelpPlugin();
	
	
	
protected:
	//void on_link_clicked(const TreeModel::Path& path, TreeViewColumn* column);
	void on_link_clicked(DhLink*);

	Glib::SignalProxy<void()> signal_link_selected();

	Glib::RefPtr<TreeSelection> refTreeSelection;
	DhBookTree*		m_book_tree;						/* "Contents" in the sidebar */
	GtkTreeView*	m_book_tree01;						/* "Contents" in the sidebar */
	DhLink* 		m_dhlink;
    GtkWidget*		m_grid;								/* "grid" in the sidebar */
    GtkWidget*		m_sidebar;							/* "DH_Sidebar" in the sidebar */
    GtkWidget*		m_search;							/* "Search" in the sidebar */
    Notebook		m_sb_notebook;						/* "Notebook" that holds contents/search */
    Box 			m_vbox;	
    Box				m_hbox;
    Widget			*m_search_convert;
    TreeView		*m_book_tree_convert;
	DhProfile 		*dh_profile;
	DhSidebar 		*m_sidebarnew2;
	Label 			l_contents, l_search, l_devhelp;
	ScrolledWindow	search_sw, book_tree_sw;
	Gtk::Notebook 	m_sidebar_notebook;
	
	
	/* Webview stuff */
	Gtk::Widget			*m_webview;			/* Webkit that shows documentation */
	WebKitWebView 		*m_webview_main;
	Gtk::Widget			*m_webview_tab;		/* The widget that has webview related stuff */
	Gtk::ToolButton		m_btn_back;			/* the webkit browser back button in the toolbar */
	Gtk::ToolButton		m_btn_forward;		/* the webkit browser forward button in the toolbar */
	Gtk::Toolbar toolbar;
	Gtk::ToolButton btn_zoom_in, btn_zoom_out;
	Gtk::SeparatorToolItem tb_sep;
	Gtk::ScrolledWindow webview_sw;
	
};


#endif /* DEVHELP_PLUGIN_H */
