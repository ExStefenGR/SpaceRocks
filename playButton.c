
//{{BLOCK(playButton)

//======================================================================
//
//	playButton, 64x32@4, 
//	+ palette 256 entries, not compressed
//	+ 32 tiles Metatiled by 2x1 not compressed
//	Total size: 512 + 1024 = 1536
//
//	Time-stamp: 2021-02-09, 14:32:45
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned char playButtonTiles[1024] __attribute__((aligned(4)))=
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0xEE,0x00,0xF0,0xFE,0xEF,
	0x00,0xEF,0xFF,0xEE,0x00,0xFE,0xFF,0xCC,0x00,0xFE,0xCF,0xCC,0xF0,0xCC,0xCC,0xCC,
	0xFF,0xFF,0xFF,0xFF,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xFF,0xFF,0xFF,0xFF,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xFF,0xFF,0xFF,0xFF,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,

	0xFF,0xFF,0xFF,0xFF,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xFF,0xFF,0xFF,0xFF,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xFF,0xFF,0xFF,0xFF,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xEE,0xFF,0x00,0x00,0xEE,0xEE,0x0F,0x00,
	0xEE,0xEE,0xFE,0x00,0xCC,0xEE,0xEE,0x00,0xCC,0xCC,0xEE,0x00,0xCC,0xCC,0xCC,0x0F,

	0xF0,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,
	0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xFF,0xFF,0xCC,0xCC,0xFF,0xFF,0xFF,0xCC,0xFF,0xCC,0xFF,0xCC,0xFF,0xCC,0xFC,0xCC,
	0xFF,0xCC,0xFC,0xCC,0xFF,0xCC,0xFC,0xCC,0xFF,0xCC,0xFF,0xCC,0xFF,0xFF,0xFF,0xCC,
	0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,
	0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,

	0xCC,0xCC,0xFF,0xCC,0xCC,0xFC,0xFF,0xCC,0xCC,0xFC,0xFF,0xCC,0xCC,0xFF,0xCC,0xCF,
	0xCC,0xFF,0xCC,0xCF,0xCC,0xCF,0xCC,0xFF,0xCC,0xCF,0xCC,0xFF,0xCC,0xCF,0xCC,0xFF,
	0xCC,0xFF,0xCC,0xFC,0xCC,0xFF,0xCC,0xFC,0xCC,0xFF,0xCF,0xFF,0xCC,0xFC,0xCF,0xFF,
	0xCC,0xFC,0xFF,0xFF,0xCC,0xCC,0xFF,0xCF,0xCC,0xCC,0xFF,0xCF,0xCC,0xCC,0xFC,0xCC,
	0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xCC,0xCC,0xCC,0x0F,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,
	0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,

	0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,0xCF,0xCC,0xCC,0xCC,
	0xCF,0xCC,0xCC,0xCC,0x4F,0xCC,0xCC,0xCC,0x4F,0xCC,0xCC,0xCC,0xF0,0xC4,0xCC,0xCC,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xFF,0xFF,0xCC,0xCC,0xFF,0xCC,0xCC,0xCC,0xFF,0xCC,0xCC,0xCC,0xFF,0xCC,0xCC,0xCC,
	0xFF,0xCC,0xCC,0xCC,0xFF,0xCC,0xCC,0xCC,0xFF,0xCC,0xCC,0xCC,0xFF,0xCC,0xCC,0xCC,
	0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,
	0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xFF,0xFF,0xCF,0xFC,0xFF,0xFF,0xCF,

	0xCC,0xCF,0xCC,0xFF,0xCC,0xFF,0xFF,0xFF,0xCC,0xFF,0xFF,0xFF,0xCC,0xFF,0xFF,0xFF,
	0xCC,0xCF,0xCC,0xFF,0xCC,0xCF,0xCC,0xFF,0xCC,0xCF,0xCC,0xFF,0xCC,0xCF,0xCC,0xFF,
	0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,
	0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xFC,
	0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xF4,0xCC,0xCC,0xCC,0xF4,0xCC,0xCC,0x4C,0x0F,

	0xF0,0xC4,0xCC,0xCC,0x00,0x44,0xCC,0xCC,0x00,0x44,0xC4,0xCC,0x00,0x4F,0x44,0xCC,
	0x00,0xF0,0x44,0x44,0x00,0x00,0xFF,0x44,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0xFF,0xFF,0xFF,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0xFF,0xFF,0xFF,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0xFF,0xFF,0xFF,

	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0xFF,0xFF,0xFF,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0xFF,0xFF,0xFF,
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0xFF,0xFF,0xFF,
	0xCC,0xCC,0x44,0x0F,0xCC,0x4C,0x44,0x00,0xCC,0x44,0x44,0x00,0x44,0x44,0xF4,0x00,
	0x44,0x44,0x0F,0x00,0x44,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

const unsigned char playButtonPal[512] __attribute__((aligned(4)))=
{
	0x00,0x00,0x10,0x00,0x00,0x02,0x10,0x02,0x00,0x40,0x10,0x40,0x00,0x42,0x18,0x63,
	0x10,0x42,0x1F,0x00,0xE0,0x03,0xFF,0x03,0x00,0x7C,0x1F,0x7C,0xE0,0x7F,0xFF,0x7F,
	0x00,0x00,0x4A,0x25,0x4A,0x01,0x0F,0x00,0xD6,0x5A,0xD7,0x5A,0xD6,0x5A,0xD6,0x5A,
	0xD6,0x5A,0xD6,0x5A,0xD6,0x5A,0xD6,0x5A,0xD6,0x5A,0xD6,0x5A,0xD6,0x5A,0xD6,0x5A,
	0x84,0x00,0xE7,0x00,0x6B,0x01,0xEF,0x01,0x73,0x02,0xF7,0x02,0x7B,0x03,0xFF,0x03,
	0x00,0x10,0x00,0x1C,0x00,0x2C,0x00,0x3C,0x00,0x4C,0x00,0x5C,0x00,0x6C,0x00,0x7C,
	0x04,0x10,0x07,0x1C,0x0B,0x2C,0x0F,0x3C,0x13,0x4C,0x17,0x5C,0x1B,0x6C,0x1F,0x7C,
	0x80,0x10,0xE0,0x1C,0x60,0x2D,0xE0,0x3D,0x60,0x4E,0xE0,0x5E,0x60,0x6F,0xE0,0x7F,

	0x42,0x08,0x63,0x0C,0xA5,0x14,0xE7,0x1C,0x29,0x25,0x6B,0x2D,0xAD,0x35,0xEF,0x3D,
	0x31,0x46,0x73,0x4E,0xB5,0x56,0xF7,0x5E,0x39,0x67,0x7B,0x6F,0xBD,0x77,0xFF,0x7F,
	0x1F,0x00,0x7F,0x00,0xFF,0x00,0x7F,0x01,0xFF,0x01,0x7F,0x02,0xFF,0x02,0x7F,0x03,
	0xFF,0x03,0xFC,0x03,0xF8,0x03,0xF4,0x03,0xF0,0x03,0xEC,0x03,0xE8,0x03,0xE4,0x03,
	0xE0,0x03,0xE0,0x0F,0xE0,0x1F,0xE0,0x2F,0xE0,0x3F,0xE0,0x4F,0xE0,0x5F,0xE0,0x6F,
	0xE0,0x7F,0x80,0x7F,0x00,0x7F,0x80,0x7E,0x00,0x7E,0x80,0x7D,0x00,0x7D,0x80,0x7C,
	0x00,0x7C,0x03,0x7C,0x07,0x7C,0x0B,0x7C,0x0F,0x7C,0x13,0x7C,0x17,0x7C,0x1B,0x7C,
	0x1F,0x7C,0x1F,0x70,0x1F,0x60,0x1F,0x50,0x1F,0x40,0x1F,0x30,0x1F,0x20,0x1F,0x10,

	0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x21,0x04,0x42,0x08,0x63,0x0C,0x84,0x10,0xA5,0x14,0xC6,0x18,0xE7,0x1C,
	0x08,0x21,0x29,0x25,0x4A,0x29,0x6B,0x2D,0x8C,0x31,0xAD,0x35,0xCE,0x39,0xEF,0x3D,
	0x10,0x42,0x31,0x46,0x52,0x4A,0x73,0x4E,0x94,0x52,0xB5,0x56,0xD6,0x5A,0xF7,0x5E,
	0x18,0x63,0x39,0x67,0x5A,0x6B,0x7B,0x6F,0x9C,0x73,0xBD,0x77,0xDE,0x7B,0xFF,0x7F,
};

//}}BLOCK(playButton)
