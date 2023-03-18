//
// Created by potato_coder on 14.02.23.
//

#include <stdbool.h>
#include "gtk-3.0/gtk/gtk.h"
#include "../../include/chart/gtk_chart.h"

typedef struct point{
    double x;
    double y;
}point;

void x_to_canvas_coord(point point, double k, double can_h, double can_w){

}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
    guint width, height;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context(widget);

    GdkColor color;
    gdk_color_parse ("#37343a", &color); //setting a color - you can also use RGB
    gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    double arrow_h = 0.001 * height * 20;
    double arrow_w = 0.001 * height * 10;

    gtk_render_background(context, cr, 0, 0, width, height);
    cairo_set_line_width(cr, 2);
    //стрелочка на y
    cairo_set_source_rgb(cr, 255, 255, 255);
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
    cairo_set_source_rgba(cr, 255, 255, 255, 0.7);
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

    cairo_fill(cr);
    point array[5];
    array[0].x = 0;
    array[0].y = 0;
    array[1].x = 2;
    array[1].y = 4;
    array[2].x = 4;
    array[2].y = 16;
    array[3].x = 8;
    array[3].y = 64;
    cairo_stroke(cr);
    cairo_set_line_width(cr, 2);
    cairo_set_source_rgba(cr, 0,50,50, 0.5);
    //cairo_arc (cr, width / 2.0, height / 2.0, MIN (width, height) / 2.0, 0, 2 * G_PI);
    for (size_t i = 1; i < 4; i++) {
        if(i>0) {
            double prev_x = array[i-1].x*width/100 + (0.1 * width);
            double prev_y = -(array[i-1].y*height/100) + (0.9*height);
            double x = array[i].x*width/100 + (0.1 * width);
            double y = -(array[i].y*height/100) + (0.9*height);
            cairo_move_to(cr, prev_x, prev_y);//(-(array[i-1] * array[i-1])) + (0.9 * height)
            cairo_line_to(cr, x,y);
            cairo_stroke(cr);
        }
    }
    cairo_set_source_rgba(cr, 255, 255, 255, 0.8);
    for (size_t i = 0; i < 4; i++) {
        double x = array[i].x*width/100 + (0.1 * width);
        double y = -(array[i].y*height/100) + (0.9*height);
        //array[i] + (0.1 * width), (-y)+(0.9*height),
        cairo_arc(cr, x, y,  4, 0, 2 * G_PI);
        cairo_fill(cr);
        cairo_stroke(cr);
    }
    return FALSE;
}

G_MODULE_EXPORT void on_destroy() {
    gtk_main_quit();
}

void main_win_set_parameteres(GtkWidget *main_window, GError *error) {
    gtk_window_set_title(GTK_WINDOW (main_window), "ChartBuilder");
    gtk_window_set_icon_from_file(GTK_WINDOW (main_window),
                                  "/mnt/c/Users/sasha/Download/CountMathLabs/linear_equations_solver/resources/icons/chart_logo.png",
                                  &error);
    gtk_window_set_default_size(GTK_WINDOW (main_window), 1280, 720);
}

bool win_init(GtkBuilder *builder, GError *error) {
    GtkWidget *window;
    if (!gtk_builder_add_from_file(builder,
                                   "/mnt/c/Users/sasha/Download/CountMathLabs/linear_equations_solver/resources/glade_templates/main.glade",
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