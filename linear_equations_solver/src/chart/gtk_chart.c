//
// Created by potato_coder on 14.02.23.
//

#include <stdbool.h>
#include "gtk-3.0/gtk/gtk.h"
#include "../../include/chart/gtk_chart.h"

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
    guint width, height;
    GdkRGBA color;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context(widget);

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    double arrow_h = 0.001 * height * 20;
    double arrow_w = 0.001 * height * 10;

    gtk_render_background(context, cr, 0, 0, width, height);
    cairo_set_line_width(cr, 2);
    //стрелочка на y
    cairo_move_to(cr, 0.1 * width, 0.09 * height);
    cairo_line_to(cr, 0.1 * width + arrow_w, 0.1 * height + arrow_h);
    cairo_move_to(cr, 0.1 * width, 0.09 * height);
    cairo_line_to(cr, 0.1 * width - arrow_w, 0.1 * height + arrow_h);
    cairo_line_to(cr, 0.1 * width + arrow_w, 0.1 * height + arrow_h);
    cairo_fill(cr);

    //стрелка на х
    cairo_move_to(cr, 0.91 * width, 0.9 * height);
    cairo_line_to(cr, 0.9 * width - arrow_h, 0.9 * height - arrow_w);
    cairo_move_to(cr, 0.91 * width, 0.9 * height);
    cairo_line_to(cr, 0.9 * width - arrow_h, 0.9 * height - arrow_w);
    cairo_line_to(cr, 0.9 * width - arrow_h, 0.9 * height + arrow_w);
    cairo_fill(cr);

    //сетка
    cairo_move_to(cr, 0.1 * width, 0.1 * height);
    cairo_line_to(cr, 0.1 * width, 0.9 * height);
    cairo_line_to(cr, 0.9 * width, 0.9 * height);
    cairo_stroke(cr);
    cairo_set_line_width(cr, 0.5);
    int64_t step = width / 100;
    for (guint i = (guint) (0.1 * width + step); i < (0.89 * width); i += step) {
        cairo_move_to(cr, i, 0.12 * height);
        cairo_line_to(cr, i, 0.9 * height);
    }
    step = height / 57;
    for (guint i = (guint) (0.9 * height); i > (guint) (0.12 * height); i -= step) {
        cairo_move_to(cr, 0.1 * width, i);
        cairo_line_to(cr, 0.89 * width, i);
    }
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);
    //cairo_arc (cr, width / 2.0, height / 2.0, MIN (width, height) / 2.0, 0, 2 * G_PI);
    gtk_style_context_get_color(context,
                                gtk_style_context_get_state(context),
                                &color);
    gdk_cairo_set_source_rgba(cr, &color);

    cairo_fill(cr);
    double array[5] = {1, 13, 17, 18, 14};
    for (size_t i = 0; i < 5; i++) {
        double y = array[i] * array[i];
        cairo_arc(cr, array[i], y, 3, 0, 2 * G_PI);
        cairo_fill(cr);
    }
    cairo_stroke(cr);
    return FALSE;
}

G_MODULE_EXPORT void on_destroy() {
    gtk_main_quit();
}

void main_win_set_parameteres(GtkWidget *main_window, GError *error) {
    gtk_window_set_title(GTK_WINDOW (main_window), "ChartBuilder");
    gtk_window_set_icon_from_file(GTK_WINDOW (main_window),
                                  "/home/potato_coder/Рабочий стол/MyProjects/CountMathLab1/linear_equations_solver/resources/icons/chart_logo.png",
                                  &error);
    gtk_window_set_default_size(GTK_WINDOW (main_window), 1280, 720);
}

bool win_init(GtkBuilder *builder, GError *error) {
    GtkWidget *window;
    if (!gtk_builder_add_from_file(builder,
                                   "/home/potato_coder/Рабочий стол/MyProjects/CountMathLab1/linear_equations_solver/resources/glade_templates/main.glade",
                                   &error)) {
        g_critical ("Не вышло загрузить файл с UI : %s", error->message);
        g_error_free(error);
    }
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    main_win_set_parameteres(window, error);
    gtk_builder_connect_signals(builder, NULL);
    GtkWidget *area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));;
    gtk_widget_set_size_request(area, 100, 100);
    g_signal_connect (G_OBJECT(area), "draw",
                      G_CALLBACK(draw_callback), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    gtk_widget_destroy(window);
    return true;
}

bool build_gtk_chart(double *points_array) {
    gtk_init(0, NULL);
    GError *error = NULL;
    GtkBuilder *ui_builder;
    ui_builder = gtk_builder_new();
    win_init(ui_builder, error);
    if (error != NULL) {
        g_error_free(error);
    }
    return true;
}