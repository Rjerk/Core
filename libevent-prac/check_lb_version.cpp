#include <event2/event.h>
#include <string.h>

int check_for_old_version(void)
{
    const char* v = event_get_version();
    if (!strncmp(v, "0.", 2)  ||
        !strncmp(v, "1.1", 3) ||
        !strncmp(v, "1.2", 3) ||
        !strncmp(v, "1.3", 3)) {

        printf ("Your version of libevent is very old."
                "If you run into bugs, consider upgrading.\n");
        return -1;
    } else {
        printf ("Running with libevent version %s\n", v);
        return 0;
    }
}

int check_version_match(void)
{
    ev_int32_t v_compile, v_run;
    v_compile = LIBEVENT_VERSION_NUMBER;
    v_run = event_get_version_number();

    if ((v_compile & 0xffff0000) != (v_run & 0xffff0000)) {
        printf ("Running with a libevent version(%s) veri different from the"
                "one we were build with (%s).\n", event_get_version(),
                LIBEVENT_VERSION);
        return -1;
    } else {
        printf ("Running version is %d\n", v_compile);
        printf ("Running version is %d\n", v_run);
    }
    return 0;
}

int main()
{
    check_for_old_version();
    check_version_match();
}
