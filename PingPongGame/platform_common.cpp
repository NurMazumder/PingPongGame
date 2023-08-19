struct Button {
	bool is_down = false;
	bool changed;
};

enum {
	btn_up,
	btn_down,
	btn_left,
	btn_right,
	btn_W,
	btn_S,
	btn_enter,

	btn_count, // last item
};

struct Input
{
	Button btn[btn_count];
};