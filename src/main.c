/*
 * Copyleft (ɔ) XINGJI Studio 2025
 *
 * 此程序是自由软件：您可以根据自由软件基金会发布的 GNU 通用公共许可证条款重新分发和/或修改它，
 * 许可证版本 3（GPLv3）。
 *
 * 分发此程序是希望它有用，但**没有任何担保**；甚至没有适销性或特定用途适用性的默示担保。
 * 有关详细信息，请参阅 GNU 通用公共许可证。
 *
 * 您应已随此程序收到 GNU GPLv3 的副本。如果没有，请访问 <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>

void disp_splash_screen(GtkApplication *master) {
    GtkWidget *splash_window = gtk_application_window_new(master);
    gtk_window_set_title(GTK_WINDOW(splash_window), "Splash screen");
    gtk_window_set_default_size(GTK_WINDOW(splash_window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(splash_window), GTK_WIN_POS_CENTER);
    gtk_window_set_decorated(GTK_WINDOW(splash_window), false);
    gtk_window_present(GTK_WINDOW(splash_window));
}

static void activate(GtkApplication *app, gpointer user_data) {
    disp_splash_screen(app);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("easy-linux.com", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    const int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}


