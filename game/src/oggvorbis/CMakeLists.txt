cmake_minimum_required (VERSION 2.8)
project(OggVorbis)
include_directories(include)
add_library(oggvorbis
	ogg/bitwise.c
	ogg/framing.c
	vorbis/analysis.c
	vorbis/bitrate.c
	vorbis/block.c
	vorbis/codebook.c
	vorbis/envelope.c
	vorbis/floor0.c
	vorbis/floor1.c
	vorbis/info.c
#	vorbis/lookup.c
	vorbis/lpc.c
	vorbis/lsp.c
	vorbis/mapping0.c
	vorbis/mdct.c
	vorbis/psy.c
	vorbis/registry.c
	vorbis/res0.c
	vorbis/sharedbook.c
	vorbis/smallft.c
	vorbis/synthesis.c
	vorbis/vorbisfile.c
	vorbis/window.c
)
