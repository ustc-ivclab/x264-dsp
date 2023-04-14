#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
m4_define([VERSION],
          m4_esyscmd([build-aux/git-version-gen .tarball-version]))
AC_INIT([x264],
        m4_defn([VERSION]),
        [https://github.com/Freed-Wu/x264-dsp/issues],
        [x264-]m4_defn([VERSION]),
        [https://github.com/Freed-Wu/x264-dsp])
AC_CONFIG_SRCDIR([x264.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])

AC_ARG_WITH([x264-bit-depth],
            [AS_HELP_STRING([--with-x264-bit-depth@<:@=8|10@:>@],
                            [bit depth, default=8]
                            )
            ],
            [],
            [with_x264_bit_depth=yes]
            )
AS_IF([test "x$with_x264_bit_depth" = "xyes"],
      [with_x264_bit_depth=8],
      []
    )
AS_IF([test "x$with_x264_bit_depth" = "xno"],
      [AC_MSG_ERROR([must define X264_BIT_DEPTH!])],
      []
    )
AS_IF([test "x$with_x264_bit_depth" = x8 -o "x$with_x264_bit_depth" = x10],
      [AC_DEFINE_UNQUOTED([X264_BIT_DEPTH],
                          [$with_x264_bit_depth],
                          [bit depth, can be 8 or 10]
                          )
      ],
      [AC_MSG_ERROR(["$with_x264_bit_depth" is an illegal bit depth!])]
      )

AC_ARG_WITH([x264-chroma-format],
            [AS_HELP_STRING([--with-x264-chroma-format@<:@=0..3@:>@],
                            [chroma format, 400, 420, 422, 444, default=1]
                            )
            ],
            [],
            [with_x264_chroma_format=yes]
            )
AS_IF([test "x$with_x264_chroma_format" = "xyes"],
      [with_x264_chroma_format=1],
      []
    )
AS_IF([test "x$with_x264_chroma_format" = "xno"],
      [AC_MSG_ERROR([must define X264_CHROMA_FORMAT!])],
      []
    )
AS_IF([test "$with_x264_chroma_format" -le 3 -a "$with_x264_chroma_format" -ge 0],
      [AC_DEFINE_UNQUOTED([X264_CHROMA_FORMAT],
                          [$with_x264_chroma_format],
                          [chroma format, 0..3 means 400, 420, 422, 444]
                          )
      ],
      [AC_MSG_ERROR(["$with_x264_chroma_format" is an illegal chroma format!])]
      )

AC_ARG_ENABLE([debug],
              [AS_HELP_STRING([--enable-debug],
                              [enable debug]
                              )
              ],
              [],
              [enable_debug=no]
              )
AS_IF([test "x$enable_debug" = xyes],
      [CFLAGS="$CFLAGS -ggdb -O0 -pedantic"],
      []
    )

AC_ARG_WITH([downsample],
            [AS_HELP_STRING([--with-downsample@<:@=0|1@:>@],
                            [downsample from 720p to 360p, 0, 1 means bilinear, bicubic, default=0]
                            )
            ],
            [],
            [with_downsample=no]
            )
AS_IF([test "x$with_downsample" = "xyes"],
      [with_downsample=0],
      []
)
AS_IF([test "x$with_downsample" != xno],
      AS_IF([test "x$with_downsample" = x0 -o "x$with_downsample" = x1],
            [AC_DEFINE_UNQUOTED([DOWNSAMPLE],
                                [$with_downsample],
                                [downsample from 720p to 360p, 0, 1 means bilinear, bicubic]
                                )
            ],
            [AC_MSG_ERROR(["$with_downsample" is an illegal downsample method!])]
            ),
            []
      )

AC_ARG_WITH([padding],
            [AS_HELP_STRING([--with-padding@<:@=1..3@:>@],
                            [padding method, edge, reflect, symmetric, default=3]
                            )
            ],
            [],
            [with_padding=yes]
            )
AS_IF([test "x$with_padding" = "xyes"],
      [with_padding=3],
      []
    )
AS_IF([test "x$with_padding" = "xno"],
      [AC_MSG_ERROR([must define padding!])],
      []
    )
AS_IF([test "$with_padding" -le 3 -a "$with_padding" -ge 1],
      [AC_DEFINE_UNQUOTED([PADDING],
                          [$with_padding],
                          [padding method, 1..3 means edge, reflect, symmetric]
                          )
      ],
      [AC_MSG_ERROR(["$with_padding" is an illegal padding method!])]
      )

# Checks for programs.
AC_PROG_CC([gcc clang])

# Checks for libraries.
PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile tests/Makefile])
AC_OUTPUT