// drop_all vde plugin
//
// enable to drop all traffic on the vde switch
#include <stdio.h>
#include <stdlib.h>

#include <config.h>
#include <vde.h>
#include <vdecommon.h>
#include <vdeplugin.h>

static int discard(struct dbgcl *tag, void *arg, va_list v);
static int drop(char *arg);

struct plugin vde_plugin_data={
  .name="drop",
  .help="enable to drop traffic on the vde switch",
};

static struct comlist cl[]={
  {"drop","============","discard all packets",NULL,NOARG},
  {"drop/active","0/1","start dropping packets",drop,STRARG},
};

#define D_DROP 0100
static struct dbgcl dl[]= {
  {"drop/packetin","drop incoming packet",D_DROP|D_IN},
};

static int drop(char *arg)
{
  int active=atoi(arg);
  int rv;
  if (active)
    rv=eventadd(discard,"packet",dl);
  else
    rv=eventdel(discard,"packet",dl);
  return rv;
}

static int discard(struct dbgcl *event, void *arg, va_list v)
{
  struct dbgcl *this=arg;
  switch (event->tag) {
    case D_PACKET|D_IN:
      return -1;
  }
  return 0;
}

static void
__attribute__ ((constructor))
init (void)
{
  ADDCL(cl);
  ADDDBGCL(dl);
}

static void
__attribute__ ((destructor))
fini (void)
{
  DELCL(cl);
  DELDBGCL(dl);
}

