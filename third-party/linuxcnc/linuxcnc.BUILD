genrule(
    name = "linuxcnc",
    srcs = glob(["*"]),
    outs = glob(["include/*"]),
    cmd = """
    cd src
    ./autogen.sh
    ./configure --with-realtime=uspace --disable-gtk2 --enable-non-distributable=yes
    """
)