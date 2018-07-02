# FastCD

## What is fastcd

Lazy typers (on Unix systems) unite!

Instead of typing `cd /some/where/to/go`, how much cooler is it
to type `fcd swtg`. Yes, you just type the initials of the directory you want
to go to, and presto. Imagine all the microseconds you'll be saving in the
days, weeks, years, and decades to come!

If there are multiple choices, `fastcd` makes sure that you get a list to pick
from:

```shell
$ fcd uls
default /usr/local/sbin
      1 /usr/local/share
      2 /usr/lib/system
```

-- at which point you hit 0 or ENTER for the first (default) choice, 1 for the
second, and so on.

The initials that are provided to `fastcd` are resolved in the following order:

*  Relative to the current directory
*  Relative to your `$HOME`
*  Relative to the root `/`

FastCD even accepts keyboard input while it's still generating the list of
solutions. If you see your destination in the list, you can just hit the right
key without waiting for `fastcd` to dig through the rest of your file system.

## What you need to install it

1.  Get the sources and `make install`. Or type `make me a sandwich` if you
    fancy. This compiles `fastcd` and installs it into `$HOME/bin`. If you want
    another location, say `/usr/local/bin/`, then use:

    ```shell
    BINDIR=/usr/local/bin make install
    ```

1.  Add the following handy function to your `~/.bashrc`:

	```shell
	function fcd() { cd $(fastcd "$1") }
	```

    If you'd like to resolve initials to directories without regard to
    casing, which is e.g. convenient on MacOSX, then you can add flag `-i`
    to the invocation:

    ```shell
    function fcd() { cd $(fastcd -i "$1") }
    ```

1.  If you like ANSI coloring (and who doesn't), add colors for the key
	selector (flag `-k`) and/or for the directory of choice (flag
	`-d`). Coloring is stated as optional modifiers `bright`, `underline` etc.
	This is followed by a color like `red`, `yellow`, etc. (You can get a list
	of all prefixes and colors using the flags `-P` and `-C`.)  For example:
	`-k brightred -d underlineblue` will display the keys to press in bright
	red, and the directories the keypresses lead to as underlined blue. The
	shell function then becomes:

	```shell
	function fcd() {
	  cd $(fastcd -k brightred -d underlineblue "$1")
    }
	```

1.  For even fancier things, try playing around with `pushd/popd`. Use your
	imagination. For example:

    ```shell
    function fcd() {
      if [ -z "$1" ]; then
        popd > /dev/null;
      else
        if [ -z "$2" ]; then
          newdir=$(fastcd -k brightred -d underlineblue "$1");
          test "$newdir" != "." && pushd "$newdir" > /dev/null;
        else
          echo 'fcd - fast directory changer' 1>&2;
          echo 'Usage: fcd ulb - takes you to say /usr/local/bin' 1>&2;
          echo '   or: fcd     - takes you to the previous directory' 1>&2;
          return 1;
        fi;
      fi
    }
    ```

Too many flags to remember? Just type `fastcd` or `fastcd -h` to get an
overview.

## Dependencies

You will need:

*  A C++ compiler that complies with the 2011 standard (i.e., accepts
   `-std=c++11`).
*  Installed "standard" libraries. Basically, a normal Linux system or MacOSX
   will do.

## Licensing

FastCD is distributed under GPLV3, see the LICENCE.md file. This means that it's
free and without warranty and you're free to do with it as you like, make
changes, whatnot - but you must

*  Keep the license conditions intact
*  Make any changes that you apply available to others

As a courtesy, I'd love to be informed of any changes that you might make, so
that I may incorporate them into a new release.
