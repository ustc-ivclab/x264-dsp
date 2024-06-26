project(
  'x264-dsp',
  ['c'],
)
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)
conf_data = configuration_data()
conf_data.set_quoted(
  'INPUT_FILENAME',
  get_option('input_filename'),
  description: 'input filename',
)
conf_data.set(
  'BIN2C',
  get_option('bin2c'),
  description: 'use bin2c',
)
conf_data.set(
  'DRY_RUN',
  get_option('dry_run'),
  description: 'do not write any file',
)
conf_data.set(
  'HAVE_TIC6X',
  get_option('have_tic6x'),
  description: 'enable TI C6X asm',
)
conf_data.set(
  'DOWNSAMPLE',
  get_option('downsample'),
  description: 'downsample from 720p to 360p, 1, 2 means bilinear, bicubic',
)
conf_data.set(
  'PADDING',
  get_option('padding'),
  description: 'padding method, 1..3 means edge, reflect, symmetric',
)
conf_data.set(
  'SCALE',
  get_option('scale'),
  description: 'SCALE scale, a positive number',
)
conf_data.set(
  'X264_BIT_DEPTH',
  get_option('x264_bit_depth'),
  description: 'bit depth, can be 8 or 10',
)
conf_data.set(
  'X264_CHROMA_FORMAT',
  get_option('x264_chroma_format'),
  description: 'chroma format, 0..3 means 400, 420, 422, 444',
)
conf_data.set(
  'X264_LOG_LEVEL',
  get_option('x264_log_level'),
  description: 'log level, 0..3 means error, warning, info, debug',
)
conf_file = configure_file(output: 'config.h', configuration: conf_data)
files = [
  conf_file.full_path(),
  'downsample.c',
  'input.c',
  'output.c',
  'x264.c',
  'encoder/analyse.c',
  'encoder/cabac.c',
  'encoder/cavlc.c',
  'encoder/encoder.c',
  'encoder/lookahead.c',
  'encoder/macroblock.c',
  'encoder/me.c',
  'encoder/ratecontrol.c',
  'encoder/set.c',
  'encoder/slicetype.c',
  'common/bitstream.c',
  'common/cabac.c',
  'common/common.c',
  'common/dct.c',
  'common/deblock.c',
  'common/frame.c',
  'common/macroblock.c',
  'common/mc.c',
  'common/mvpred.c',
  'common/pixel.c',
  'common/predict.c',
  'common/quant.c',
  'common/set.c',
  'common/vlc.c',
]
depends = []
if get_option('bin2c') and get_option('input_filename') != ''
  bin2c = find_program('bin2c')
  yuv_h = custom_target(
    'yuv.h',
    input: get_option('input_filename'),
    output: 'yuv.h',
    feed: true,
    capture: true,
    command: [bin2c, 'yuv'],
  )
  files += yuv_h
endif
executable(
  'x264',
  files,
  install: true,
  dependencies: m_dep,
)
subdir('tests')
