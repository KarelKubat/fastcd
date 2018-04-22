# FastCD

## What is fastcd

Lazy typers (on Unix systems) unite!

Instead of typing `cd /some/where/to/go`, how much cooler is it
to type `fcd swtg`. Yes, you just type the initials of the directory you want
to go to, and presto. Imagine all the microseconds you'll be saving in the
days to come!

If there are multiple choices, `fastcd` makes sure that you get a list to pick
from:

```shell
$ fcd uls
0,ENTER /usr/local/sbin
1       /usr/local/share
2       /usr/lib/system
```

-- at which point you hit 0 or ENTER for the first choice, 1 for the second,
and so on.

The initials that are provided to `fastcd` are resolved in the following order:

*  Relative to the current directory
*  Relative to your `$HOME`
*  Relative to the root `/`

FastCD even accepts keyboard input while it's still generating the list of
solutions. If you see your destination in the list, you can just hit the right
key without waiting for `fastcd` to dig through your file system.

## What you need to install it

1. Get the sources and `make install`. This compiles `fastcd` and installs it
   into `$HOME/bin`. If you want another location, just use:

   ```shell
   BINDIR=/usr/local/bin make install
   ```

1. Add the following handy function to your `~/.bashrc`:

	```shell
	function fcd() { cd $(fastcd $1) }
	```
	
1.  For even fancier things, try plaing around with `pushd/popd`. Use your
	imagination.

## Dependencies

You will need:

*  A C++ compiler that complies with the 2011 standard (i.e., accepts
   `-std=c++11`).
*  Installed "standard" libraries. Basically, a normal Linux system or MacOSX
   will do.
