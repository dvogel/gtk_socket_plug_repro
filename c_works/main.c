#include <gtk/gtk.h>
#include <gtk/gtkx.h>

void
plug_added_callback (
  GtkSocket* self,
  gpointer user_data
) {
    printf("plug-added\n");
}

gboolean
plug_removed_callback(
  GtkSocket* self,
  gpointer user_data
) {
    printf("plug-removed\n");
}

void
sock_realized (
  GtkWidget* self,
  gpointer user_data
) {
    Window sock_id = gtk_socket_get_id(GTK_SOCKET(self));
    printf("sock realized: %d\n", sock_id);
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;

  GtkSocket *sock;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  sock = gtk_socket_new();
  g_signal_connect(sock, "plug-added", G_CALLBACK(plug_added_callback), NULL);
  g_signal_connect(sock, "plug-removed", G_CALLBACK(plug_removed_callback), NULL);
  g_signal_connect(sock, "realize", G_CALLBACK(sock_realized), NULL);

  gtk_container_add(GTK_CONTAINER(window), sock);

  gtk_widget_show_all(GTK_WINDOW(window));
}
int main(int argc, char** argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

