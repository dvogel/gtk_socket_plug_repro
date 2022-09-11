use std::ffi::OsString;

use gtk::prelude::*;
use gtk::{Application, Socket, Window};

const APP_ID: &str = "gtk_socket_plug_repro";

fn main() {
    let app = Application::builder().application_id(APP_ID).build();
    app.connect_activate(build_ui);
    app.run();
}

fn build_ui(app: &Application) {
    let sock = Socket::builder()
        .vexpand(true)
        .hexpand(true)
        .visible(true)
        .build();

    sock.connect_plug_added(|sock| {
        eprintln!("plug-added");
        if let Some(win) = sock.plug_window() {
            let win_id = win.downcast::<gdkx11::X11Window>().unwrap().xid();
            std::process::Command::new("xwininfo")
                .arg("-wm")
                .arg("-id")
                .arg(OsString::from(format!("{win_id}")))
                .spawn()
                .expect("xwininfo error")
                .wait_with_output()
                .expect("xwininfo failure");
            println!("x11 winid: {:x}", win_id);
        }
    });
    sock.connect_plug_removed(|_sock| {
        eprintln!("plug-removed");
        false
    });

    let window = Window::builder()
        .application(app)
        .default_width(1600)
        .default_height(1200)
        .decorated(true)
        .deletable(true)
        .hide_titlebar_when_maximized(true)
        .icon_name("umbrello_diagram_sequence")
        .title(APP_ID)
        .child(&sock)
        .build();

    window.show_all();
    window.present();
}
