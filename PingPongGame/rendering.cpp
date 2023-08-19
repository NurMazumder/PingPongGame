static void clearScreen(unsigned color) {
    unsigned int* pixel = static_cast<unsigned int*>(render.memory);
    for (int i = 0; i < render.height; i++) {
        for (int x = 0; x < render.width; x++) {
            *pixel++ = color;
        }
    }
}

static void drawRecPixel(int x0, int y0, int x1, int y1, unsigned int color) {
    // Ensure the coordinates are within the valid bounds of the rendering area
    if (x0 < 0) x0 = 0;  // Clamp left edge
    if (y0 < 0) y0 = 0;  // Clamp top edge
    if (x1 > render.width) x1 = render.width;  // Clamp right edge
    if (y1 > render.height) y1 = render.height; // Clamp bottom edge


    // Loop through the specified rectangle area
    for (int y = y0; y < y1; y++) {
        // Calculate the starting pixel in the rendering buffer for the current row
        unsigned int* pixel = static_cast<unsigned int*>(render.memory) + x0 + y * render.width;

        // Fill the row with the specified color
        for (int x = x0; x < x1; x++) {
            *pixel++ = color; // Set the pixel color
        }
    }
}

static void drawRec(float x, float y,float halfX, float halfY, unsigned int color) {
    x *= render.height;
    y *= render.height;
    halfX *= render.height;
    halfY *= render.height;

    x += render.width / 2.f;
    y += render.height / 2.f;

    // change to pixels
    int x0 = x - halfX;
    int x1 = x + halfX;
    int y0 = y - halfY;
    int y1 = y + halfY;

    drawRecPixel(x0, y0, x1, y1, color);

}


static void drawScore(int number, float x, float y, float size, unsigned int color) {
	float halfSize = size * 0.5;


	bool drew = false;

	while (number || !drew) {
		drew = true;
		int digit = number % 10;
		number = number / 10;
		switch (digit) {
		case 0: {
			drawRec(x - size, y, halfSize, 2.5 * size, color);
			drawRec(x + size, y, halfSize, 2.5 * size, color);
			drawRec(x, y + size * 2, halfSize, halfSize, color);
			drawRec(x, y - size * 2, halfSize, halfSize, color);
			x -= size * 4;
		} break;


		case 1: {
			drawRec(x + size, y, halfSize, 2 * size, color);
			x -= size * 2;
		} break;

		case 2: {
			drawRec(x, y + size * 2, 1.5 * size, halfSize, color);
			drawRec(x, y, 1.5 * size, halfSize, color);
			drawRec(x, y - size * 2, 1.5 * size, halfSize, color);
			drawRec(x + size, y + size, halfSize, halfSize, color);
			drawRec(x - size, y - size, halfSize, halfSize, color);
			x -= size * 4;
		} break;

		case 3: {
			drawRec(x - halfSize, y + size * 2, size, halfSize, color);
			drawRec(x - halfSize, y, size, halfSize, color);
			drawRec(x - halfSize, y - size * 2, size, halfSize, color);
			drawRec(x + size, y, halfSize, 2.5 * size, color);
			x -= size * 4;
		} break;

		case 4: {
			drawRec(x + size, y, halfSize, 2.5 * size, color);
			drawRec(x - size, y + size, halfSize, 1.5 * size, color);
			drawRec(x, y, halfSize, halfSize, color);
			x -= size * 4;
		} break;

		case 5: {
			drawRec(x, y + size * 2, 1.5 * size, halfSize, color);
			drawRec(x, y, 1.5 * size, halfSize, color);
			drawRec(x, y - size * 2, 1.5 * size, halfSize, color);
			drawRec(x - size, y + size, halfSize, halfSize, color);
			drawRec(x + size, y - size, halfSize, halfSize, color);
			x -= size * 4;
		} break;

		case 6: {
			drawRec(x + halfSize, y + size * 2, size, halfSize, color);
			drawRec(x + halfSize, y, size, halfSize, color);
			drawRec(x + halfSize, y - size * 2, size, halfSize, color);
			drawRec(x - size, y, halfSize, 2.5 * size, color);
			drawRec(x + size, y - size, halfSize, halfSize, color);
			x -= size * 4;
		} break;

		case 7: {
			drawRec(x + size, y, halfSize, 2.5 * size, color);
			drawRec(x - halfSize, y + size * 2, size, halfSize, color);
			x -= size * 4;
		} break;

		case 8: {
			drawRec(x - size, y, halfSize, 2.5 * size, color);
			drawRec(x + size, y, halfSize, 2.5 * size, color);
			drawRec(x, y + size * 2, halfSize, halfSize, color);
			drawRec(x, y - size * 2, halfSize, halfSize, color);
			drawRec(x, y, halfSize, halfSize, color);
			x -= size * 4;
		} break;

		case 9: {
			drawRec(x - halfSize, y + size * 2, size, halfSize, color);
			drawRec(x - halfSize, y, size, halfSize, color);
			drawRec(x - halfSize, y - size * 2, size, halfSize, color);
			drawRec(x + size, y, halfSize, 2.5 * size, color);
			drawRec(x - size, y + size, halfSize, halfSize, color);
			x -= size * 4;
		} break;
		}
	}
}

const char* letters[][7] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

};

static void drawLetter(const char** letter, float x, float y, float size, float halfSize, unsigned int color) {
	float originalX = x;

	for (int i = 0; i < 7; i++) {
		const char* row = letter[i];
		for (int j = 0; j < 4; j++) { // Assuming each row consists of 4 characters
			if (row[j] == '0') {
				drawRec(x, y, halfSize, halfSize, color);
			}
			x += size;
		}
		y -= size;
		x = originalX;
	}
}

static void displayText(const char* text, float x, float y, float size, unsigned int color) {
	float halfSize = size * .5;

	while (*text) {
		if (*text != ' ') { // Check for space character
			const char** letter = letters[*text - 'A'];
			drawLetter(letter, x, y, size, halfSize, color);
		}
		text++;
		x += size * 6; // Move to the next letter position, including spacing
	}
}


