static libnet_t* l; // libnet descriptor.

void open_output()
{
    char errbuf[LIBNET_ERRBUF_SIZE];

    // initialize libnet with an IPv4 raw socket.
    l = libnet_init(LIBNET_RAW4, NULL, errbuf);
    if (l ==  NULL) {
        err_quit("Can't initialize libnet: %s", errbuf);
    }
}
