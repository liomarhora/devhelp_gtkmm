#include "dhp.h"


DevhelpPlugin::DevhelpPlugin() : m_hbox(Gtk::ORIENTATION_HORIZONTAL), m_vbox(Gtk::ORIENTATION_VERTICAL)
{
	set_title("DevHelpPlugin");
	set_default_size(1300,800);
	
	//Init DevHelp Library
	dh_profile = dh_profile_get_default();
	
	m_sidebarnew2 = dh_sidebar_new2(dh_profile);
	
	/* Sidebar */
    m_sidebar = GTK_WIDGET(dh_sidebar_new2 (dh_profile));
    gtk_widget_show (GTK_WIDGET (m_sidebar));    
    
	/*Grid for sidebar*/
	m_grid = gtk_grid_new();
	gtk_grid_attach (GTK_GRID (m_grid), m_sidebar, 0, 0, 1, 1);
	
	/*Convert booktree of gtk to gtkmm */		
	m_book_tree = GTK_TREE_VIEW(dh_book_tree_new(dh_profile));
	m_book_tree_convert = Glib::wrap(m_book_tree);
	
	/*Convert GtkSearch of Gtk to Gtkmm*/
	m_search = GTK_WIDGET(m_grid);
	m_search_convert = Glib::wrap(m_search);
	/* ScrolledWindow for booktree*/
	book_tree_sw.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	book_tree_sw.set_border_width(6);
	book_tree_sw.add(*m_book_tree_convert);
	book_tree_sw.show();
	/* ScrolledWindow for Search*/	
	search_sw.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	search_sw.set_border_width(6);
	search_sw.add(*m_search_convert);
	
	/*Label for page in notebook*/
	l_contents.set_text("Contents");
	l_search.set_text("Search");
	l_devhelp.set_text("Devhelp");
	
	/*notebook for booktree and search*/
	m_sb_notebook.append_page(book_tree_sw, l_contents);
	m_sb_notebook.append_page(search_sw, l_search);
	m_sb_notebook.set_current_page(0);
	
	/*notebook for sidebar notebook*/
	m_sidebar_notebook.append_page(m_sb_notebook, l_devhelp);

	refTreeSelection = m_book_tree_convert->get_selection();
	refTreeSelection->set_mode(Gtk::SelectionMode::SELECTION_SINGLE);
	//refTreeSelection->signal_changed().connect(sigc::mem_fun(*this, &DevhelpPlugin::on_link_clicked));
	m_book_tree_convert->DevhelpPlugin.signal_link_selected().connect( sigc::mem_fun(*this, &DevhelpPlugin::on_link_clicked) );

	/* Init Webkit Library*/
	m_webview_main =  WEBKIT_WEB_VIEW( webkit_web_view_new() ); 
	m_webview = Glib::wrap(GTK_WIDGET(m_webview_main));
	
	webview_sw.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	webview_sw.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	webview_sw.add(*m_webview);
	
	m_btn_back.set_icon_name("go-previous");
	m_btn_forward.set_icon_name("go-next");
	btn_zoom_in.set_icon_name("Zoom _In");
	btn_zoom_out.set_icon_name("Zoom _Out");
	
	m_btn_back.set_tooltip_text(("Go back one page"));
	m_btn_forward.set_tooltip_text(("Go forward one page"));
	btn_zoom_in.set_tooltip_text(("Zoom in"));
	btn_zoom_out.set_tooltip_text(("Zoom out"));
	
	toolbar.insert(m_btn_back, -1);
	toolbar.insert(m_btn_forward, -1);
	toolbar.insert(tb_sep, -1);
	toolbar.insert(btn_zoom_in, -1);
	toolbar.insert(btn_zoom_out, -1);
		
	m_vbox.pack_start(toolbar, false, true, 0);
	m_vbox.pack_start(webview_sw, true, true, 0);
	
	
	m_hbox.pack_start(m_sidebar_notebook, true, true, 0);
	m_hbox.pack_start(m_vbox, true, true, 0);
	
	add(m_hbox);
	show_all_children();
	
}

DevhelpPlugin::~DevhelpPlugin()
{
}


void DevhelpPlugin::on_link_clicked()
{
	DhLink *dhlink = dh_sidebar_get_selected_link(m_sidebarnew2);
	const char *uri;
	
	uri = dh_link_get_uri(dhlink);
	std::cout << *uri << std::endl;
	webkit_web_view_load_uri(m_webview_main, uri);

}




Glib::SignalProxy<void()> DevhelpPlugin::signal_link_selected()
{
  return Glib::SignalProxy<void() >(this, &BookTree_signal_cursor_changed_info);
}



static const Glib::SignalProxyInfo BookTree_signal_cursor_changed_info =
{
  "link-selected",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};
