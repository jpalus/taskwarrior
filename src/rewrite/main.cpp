////////////////////////////////////////////////////////////////////////////////
#include "Context.h"

int main (int argc, char** argv)
{
  try
  {
    Context c;
    c.initialize ();
    c.commandLine (argc, argv);
    c.run ();

    return 0;
  }

  catch (...)
  {
  }

  return -1;
}

////////////////////////////////////////////////////////////////////////////////
